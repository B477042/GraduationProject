// Fill out your copyright notice in the Description page of Project Settings.


#include "AstarFinder.h"
#include "Engine/Engine.h"
// Sets default values
UAstarFinder::UAstarFinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
//void UAstarFinder::BeginPlay()
//{
//	Super::BeginPlay();
//	EGLOG(Error, TEXT("Ganag nam style"));
//}
//
//void UAstarFinder::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//	
//}
//
//// Called every frame
//void UAstarFinder::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

UAstarFinder * UAstarFinder::GetInstance()
{
	{
		if (GEngine)
		{
			UAstarFinder* instance = Cast<UAstarFinder>(GEngine->GameSingleton);
			
			return instance;
		}
	
		return nullptr;
	}
}

void UAstarFinder::AStar(AAstarNode * Start, AAstarNode *Goal)
{
	EGLOG(Error, TEXT("AStar Lunched At :%s"),*Start->GetName());
	ToVisiteNodes.Empty();
		EGLOG(Error, TEXT("AStar Start"));
		ToVisiteNodes.Enqueue(Start);

	
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

		//���� ��尡 Goal�� ��ġ�� ���ٸ� -> �ȸ����ٸ� ���� ��ü�� ����Ű���� �˻�
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
				if(!it.IsValid())continue;
				//�湮�ߴ� ���� �Ѿ��.
				if (it->IsVisitedNode())continue;

				it->CalcFCount(Start->GetActorLocation(), Goal->GetActorLocation());
				//�αٳ��� Count��� ������ �ʿ� ������
				;
				////���� ���� Ž������ �α� ��尡 Goal�� ���ٸ� for���� ������
				//if (it == Goal)break;
			}

			//���� ����� �ֺ� ������ ���� ��带 ���� ���� �������ش�. 
			PopedNode->SetNearNodesPrevAsMe();

			//�ֺ� ������ FCount�� ���� ������ �־�� �ȴ�. ->������ ���۷����Ͱ� �� �� �ȴ� �׳� �н�
			for (auto it : PopedNode->NearNodes)
			{
				//��ȿ���� �ʴٸ� �Ѿ��
				if (!it.IsValid())continue;
				//�湮�ߴ� ���� �ٽ� �� �־ �ȴ�
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"),*it->GetName());
				ToVisiteNodes.Enqueue(it.Get());
				
			}
		
			
		}

	

		
	}

	//�� ��带 ã�Ҵٸ� ��ε��� Ȱ��ȭ �����ش�
	if(GoalNode.IsValid())
	ShowPath();
}

void UAstarFinder::ShowPath()
{

	TWeakObjectPtr<AAstarNode> temp = GoalNode;
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

void UAstarFinder::SetStartPoint(AAstarNode * Other)
{
	
		AStar(Other, GoalNode.Get());
	
}
//Game instance���� ��ǥ�� �Ǵ� ������Ʈ�� �켱������ �ҷ��ͼ� ã���ش�. 
void UAstarFinder::SetGoalPoint(AAstarNode * Other)
{
	GoalNode = Other;
}
//��� ����� AStar ���갪�� �����ش�
void UAstarFinder::ResetResult()
{
	for (auto it : AllNodes)
	{
		it->ResetAStarValue();
		it->Deactivate();
	}

}

void UAstarFinder::AddNode(AAstarNode * Other)
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

void UAstarFinder::ClearNodes()
{
	AllNodes.Empty();
}



