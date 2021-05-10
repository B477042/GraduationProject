// Fill out your copyright notice in the Description page of Project Settings.


#include "AstarFinder.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "EGGameInstance.h"
// Sets default values
AAStarFinder::AAStarFinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAStarFinder::BeginPlay()
{
	Super::BeginPlay();
	EGLOG(Error, TEXT("Ganag nam style"));



}

void AAStarFinder::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	if (GameInstance->SetAStarFinder(this))
		EGLOG(Warning, TEXT("Regist astar finder"));

}

//// Called every frame
//void AAStarFinder::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//AAStarFinder * AAStarFinder::GetInstance()
//{
//	{
//		if (GEngine)
//		{
//			AAStarFinder* instance = Cast<AAStarFinder>(GEngine->GameSingleton);
//			
//			return instance;
//		}
//	
//		return nullptr;
//	}
//}

void AAStarFinder::PathFind(AAstarNode * Start,EPathTarget Mode)
{
	EGLOG(Error, TEXT("AStar Lunched At :%s"),*Start->GetName());
	ToVisiteNodes.Empty();
		EGLOG(Error, TEXT("AStar Start"));
		ToVisiteNodes.Enqueue(Start);
		switch (Mode)
		{
		case EPathTarget::Key:
			KeyFind(Start, KeyNode.Get());
			break;
		case EPathTarget::Gate:
			GoalFind(Start, GoalNode.Get());
			break;
		default:
			break;
		}


	

		
	


}

void AAStarFinder::ShowPath(EPathTarget Mode)
{
	TWeakObjectPtr<AAstarNode> temp;
	switch (Mode)
	{
	case EPathTarget::Key:
		temp=KeyNode;
		break;
	case EPathTarget::Gate:
		temp = GoalNode;
		break;
	default:
		break;
	}
	
	if (!temp.IsValid())EGLOG(Error, TEXT("Goal node is null"));
	//ó�� ���������� �´ٸ� 
	while (temp.IsValid())
	{
		/*
			��带 ��η� �������ְ�
			Ȱ��ȭ ��Ų ��, deref�� �ϸ鼭 ���� ���� �ٽ� ��ũ���ش�.
		
		*/

		temp->SetToPath();
		temp->Activate();
		if (!temp->GetPrevNode().IsValid())break;
		temp = temp->GetPrevNode();
		
	}
}

void AAStarFinder::StartPathFinder(AAstarNode * Other, EPathTarget Mode)
{
	
		PathFind(Other,Mode);
	
}
void AAStarFinder::SetKeyPoint(AAstarNode* Other)
{
	KeyNode = Other;
}

//Game instance���� ��ǥ�� �Ǵ� ������Ʈ�� �켱������ �ҷ��ͼ� ã���ش�. 
void AAStarFinder::SetGoalPoint(AAstarNode * Other)
{
	GoalNode = Other;
}
//��� ����� PathFind ���갪�� �����ش�
void AAStarFinder::ResetResult()
{
	for (auto it : AllNodes)
	{
		it->ResetAStarValue();
		it->Deactivate();
	}

}

void AAStarFinder::AddNode(AAstarNode * Other)
{
	AllNodes.Add(Other);
	EGLOG(Warning, TEXT("Add : %s"), *AllNodes.Top()->GetName());
	EGLOG(Warning, TEXT("Capacity : %d"), AllNodes.Num());
	for (auto it : AllNodes)
		if (it.IsValid())
			EGLOG(Warning, TEXT("in node : %s"), *it->GetName());
	if(GoalNode.IsValid())
	EGLOG(Warning, TEXT("GoalNode is : %s"), *GoalNode->GetName());

	EGLOG(Warning, TEXT("ToVisiteNodes : %d "), ToVisiteNodes.IsEmpty());
}

void AAStarFinder::ClearNodes()
{
	AllNodes.Empty();
}

void AAStarFinder::GoalFind(AAstarNode * Start, AAstarNode * Goal)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Goal Finder"));
	TWeakObjectPtr<AAstarNode> PopedNode;
	int i = 0;


	//�湮�ؾߵ� ��尡 ����� ������
	while (!ToVisiteNodes.IsEmpty())
	{
		EGLOG(Warning, TEXT("%d Try"), i);
		i++;

		//Queue���� �ϳ��� ������
		ToVisiteNodes.Dequeue(PopedNode);
		EGLOG(Warning, TEXT("Current Node : %s"), *PopedNode->GetName());
		//����� �湮�� ��ģ��
		PopedNode->VisitNode();

		//���� ��尡 Goal�� ��ġ�� ���ٸ� 
		if (PopedNode->GetActorLocation() == Goal->GetActorLocation())
		{
			//GoalNode�� �������ְ� ToVisiteNode�� ����ش�
			EGLOG(Error, TEXT("Goal Find! : %s"), *PopedNode->GetName());
			GoalNode = PopedNode.Get();
			ToVisiteNodes.Empty();
			break;
		}

		//�αٳ����� �ֺ� ������ �ִٸ�
		if (PopedNode->NearNodes.GetData() != nullptr)
			//�α� ������ ���� ����Ѵ�
		{
			for (auto it : PopedNode->NearNodes)
			{
				//��ȿ���� �ʴٸ� �Ѿ��
				if (!it.IsValid())continue;
				//�湮�ߴ� ���� �Ѿ��.
				if (it->IsVisitedNode())continue;

				it->CalcFCount(Start->GetActorLocation(), Goal->GetActorLocation());
				
			
			}

			//���� ����� �ֺ� ������ ���� ��带 ���� ���� �������ش�. 
			PopedNode->SetNearNodesPrevAsMe();
					
		
			//fcount ������ ����
			for (int k = 0; k < PopedNode->NearNodes.Num();++k)
			{
				for (int j = k+1 ; j < PopedNode->NearNodes.Num()-1; ++j)
				{
					//���� ��ȿ�� �˻�
					if (!PopedNode->NearNodes[k].IsValid() || !PopedNode->NearNodes[j].IsValid())continue;
					if (PopedNode->NearNodes[k]->GetF() > PopedNode->NearNodes[j]->GetF())
						PopedNode->NearNodes.Swap(k, j);
				}

			}

		 
			
			//���ĵ� ������� �ִ´�
			for (auto it : PopedNode->NearNodes)
			{
				
				//��ȿ���� �ʴٸ� �Ѿ��
				if (!it.IsValid())continue;

				//�湮�ߴ� ���� �ٽ� �� �־ �ȴ�
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisiteNodes.Enqueue(it.Get());


			}

		

		}
	}

	//�� ��带 ã�Ҵٸ� ��ε��� Ȱ��ȭ �����ش�
	if (GoalNode.IsValid())
		ShowPath(EPathTarget::Gate);
}

void AAStarFinder::KeyFind(AAstarNode * Start, AAstarNode * Key)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Key Finder"));
	
	TWeakObjectPtr<AAstarNode> PopedNode;
	int i = 0;
	EGLOG(Error, TEXT("======================="));
	EGLOG(Error, TEXT("Key Node : %s"), *KeyNode->GetName());
	EGLOG(Error, TEXT("Gate Node : %s"), *GoalNode->GetName());
	EGLOG(Error, TEXT("======================="));
	//�湮�ؾߵ� ��尡 ����� ������
	while (!ToVisiteNodes.IsEmpty())
	{
		EGLOG(Warning, TEXT("%d Try"), i);
		i++;
		//Queue���� �ϳ��� ������
		ToVisiteNodes.Dequeue(PopedNode);
		EGLOG(Warning, TEXT("Current Node : %s"), *PopedNode->GetName());
		//����� �湮�� ��ģ��
		PopedNode->VisitNode();

		//���� ��尡Key�� ��ġ�� ���ٸ� 
		if (PopedNode->GetActorLocation() == Key->GetActorLocation())
		{
			//GoalNode�� �������ְ� ToVisiteNode�� ����ش�
			EGLOG(Error, TEXT("Key Find! : %s"), *PopedNode->GetName());
			KeyNode = PopedNode.Get();
			ToVisiteNodes.Empty();
			break;
		}

		//�αٳ����� �ֺ� ������ �ִٸ�
		if (PopedNode->NearNodes.GetData() != nullptr)
			//�α� ������ ���� ����Ѵ�
		{
			for (auto it : PopedNode->NearNodes)
			{
				//��ȿ���� �ʴٸ� �Ѿ��
				if (!it.IsValid())continue;
				//�湮�ߴ� ���� �Ѿ��.
				if (it->IsVisitedNode())continue;

				it->CalcFCount(Start->GetActorLocation(), Key->GetActorLocation());
			
				
			}

			//���� ����� �ֺ� ������ ���� ��带 ���� ���� �������ش�. 
			PopedNode->SetNearNodesPrevAsMe();


			//fcount ������ ����
			for (int k = 0; k < PopedNode->NearNodes.Num(); ++k)
			{
				for (int j = k + 1; j < PopedNode->NearNodes.Num() - 1; ++j)
				{
					//���� ��ȿ�� �˻�
					if (!PopedNode->NearNodes[k].IsValid() || !PopedNode->NearNodes[j].IsValid())continue;
					if (PopedNode->NearNodes[k]->GetF() > PopedNode->NearNodes[j]->GetF())
						PopedNode->NearNodes.Swap(k, j);
				}

			}


			//�ֺ� ������ FCount�� ���� ������ �־�� �ȴ�.
			for (auto it : PopedNode->NearNodes)
			{
				//��ȿ���� �ʴٸ� �Ѿ��
				if (!it.IsValid())continue;
				//�湮�ߴ� ���� �ٽ� �� �־ �ȴ�
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisiteNodes.Enqueue(it.Get());


			}



		}
	}

	//�� ��带 ã�Ҵٸ� ��ε��� Ȱ��ȭ �����ش�
	if (KeyNode.IsValid())
		ShowPath(EPathTarget::Key);
}




