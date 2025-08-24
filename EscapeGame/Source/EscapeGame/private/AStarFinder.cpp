// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/AStarFinder.h"

#include "Kismet/KismetMathLibrary.h"
#include "UnrealCore/EGGameInstance.h"

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
 


}

void AAStarFinder::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	auto GameInstance = Cast<UEGGameInstance>(World->GetGameInstance());
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
	if (!Start)
	{
		EGLOG(Error, TEXT("Start is nullptr"));
		return;
	}


//	EGLOG(Error, TEXT("AStar Lunched At :%s"),*Start->GetName());
	ToVisitNodes.Empty();
	//	EGLOG(Error, TEXT("AStar Start"));
		ToVisitNodes.Enqueue(Start);
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
	if (!Other)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}

	
		PathFind(Other,Mode);
	
}
void AAStarFinder::SetKeyPoint(AAstarNode* Other)
{
	if (!Other)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}

	KeyNode = Other;
}

//Game instance���� ��ǥ�� �Ǵ� ������Ʈ�� �켱������ �ҷ��ͼ� ã���ش�. 
void AAStarFinder::SetGoalPoint(AAstarNode * Other)
{
	if (!Other)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}

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
	if (!Other)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}

	AllNodes.Add(Other);
	EGLOG(Warning, TEXT("Add : %s"), *AllNodes.Top()->GetName());
	EGLOG(Warning, TEXT("Capacity : %d"), AllNodes.Num());
	for (auto it : AllNodes)
		if (it.IsValid())
			EGLOG(Warning, TEXT("in node : %s"), *it->GetName());
	if(GoalNode.IsValid())
	EGLOG(Warning, TEXT("GoalNode is : %s"), *GoalNode->GetName());

	EGLOG(Warning, TEXT("ToVisitNodes : %d "), ToVisitNodes.IsEmpty());
}

void AAStarFinder::ClearNodes()
{
	AllNodes.Empty();
}

void AAStarFinder::GoalFind(AAstarNode * Start, AAstarNode * Goal)
{

	if (!Start)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}
	if (!Goal)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Goal Finder"));
	TWeakObjectPtr<AAstarNode> PopedNode;
	int i = 0;


	//�湮�ؾߵ� ��尡 ����� ������
	while (!ToVisitNodes.IsEmpty())
	{
		//EGLOG(Warning, TEXT("%d Try"), i);
		i++;

		//Queue���� �ϳ��� ������
		ToVisitNodes.Dequeue(PopedNode);

		if (!PopedNode.IsValid())
		{
			EGLOG(Error, TEXT("PopedNode is invalid"));
			return;
		}

		//EGLOG(Warning, TEXT("Current Node : %s"), *PopedNode->GetName());
		//����� �湮�� ��ģ��
		PopedNode->VisitNode();

		//���� ��尡 Goal�� ��ġ�� ���ٸ� 
		if (PopedNode->GetActorLocation() == Goal->GetActorLocation())
		{
			//GoalNode�� �������ְ� ToVisiteNode�� ����ش�
		//	EGLOG(Error, TEXT("Goal Find! : %s"), *PopedNode->GetName());
			GoalNode = PopedNode.Get();
			ToVisitNodes.Empty();
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
			//	EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisitNodes.Enqueue(it.Get());


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
	if (!Start)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}
	if (!Key)
	{
		EGLOG(Error, TEXT("Nullptr"));
		return;
	}


	TWeakObjectPtr<AAstarNode> PopedNode;
	int i = 0;
	//EGLOG(Error, TEXT("======================="));
	//EGLOG(Error, TEXT("Key Node : %s"), *KeyNode->GetName());
	//EGLOG(Error, TEXT("Gate Node : %s"), *GoalNode->GetName());
	//EGLOG(Error, TEXT("======================="));
	//�湮�ؾߵ� ��尡 ����� ������
	while (!ToVisitNodes.IsEmpty())
	{
	//	EGLOG(Warning, TEXT("%d Try"), i);
		i++;
		//Queue���� �ϳ��� ������
		ToVisitNodes.Dequeue(PopedNode);
	//	EGLOG(Warning, TEXT("Current Node : %s"), *PopedNode->GetName());
	// 
		if (!PopedNode.IsValid())
		{
			EGLOG(Error, TEXT("PopedNode is invalid"));
			return;
		}
		//����� �湮�� ��ģ��
		PopedNode->VisitNode();

		//���� ��尡Key�� ��ġ�� ���ٸ� 
		if (PopedNode->GetActorLocation() == Key->GetActorLocation())
		{
			//GoalNode�� �������ְ� ToVisiteNode�� ����ش�
	//		EGLOG(Error, TEXT("Key Find! : %s"), *PopedNode->GetName());
			KeyNode = PopedNode.Get();
			ToVisitNodes.Empty();
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
	//			EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisitNodes.Enqueue(it.Get());


			}



		}
	}

	//�� ��带 ã�Ҵٸ� ��ε��� Ȱ��ȭ �����ش�
	if (KeyNode.IsValid())
		ShowPath(EPathTarget::Key);
}




