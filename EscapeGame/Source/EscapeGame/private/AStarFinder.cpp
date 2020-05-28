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
	if (ToVisiteNodes.IsEmpty())
	{
		ToVisiteNodes.Enqueue(Start);

	}
	TWeakObjectPtr<AAstarNode> PopedNode;
	//�湮�ؾߵ� ��尡 ����� ������
	while (ToVisiteNodes.IsEmpty())
	{
		
		//Queue���� �ϳ��� ������
		ToVisiteNodes.Dequeue(PopedNode);
		
	//�αٳ����� �ֺ� ������ �ִٸ�
		if (PopedNode->NearNodes.GetData() != nullptr)
			//�α� ������ ���� ����Ѵ�
		{
			for (auto it : PopedNode->NearNodes)
			{
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
			
			//PopedNode->SortNearNodes();

			for (auto it : PopedNode->NearNodes)
			{
				ToVisiteNodes.Enqueue(it.Get());
			}

		}

		//����� �湮�� ��ģ��
		PopedNode->VisitNode();

		//���� ��尡 Goal�� ��ġ�� ���ٸ� -> �ȸ����ٸ� ���� ��ü�� ����Ű���� �˻�
		if (PopedNode->GetActorLocation() == Goal->GetActorLocation())
		{
			//GoalNode�� �������ְ� ToVisiteNode�� ����ش�
			GoalNode = PopedNode.Get();
			ToVisiteNodes.Empty();
		}

		
	}

	//�� ��带 ã�Ҵٸ� ��ε��� Ȱ��ȭ �����ش�
	if(GoalNode.IsValid())
	ShowPath();
}

void UAstarFinder::ShowPath()
{
	TWeakObjectPtr<AAstarNode> temp = GoalNode;
	
	//ó�� ���������� �´ٸ� 
	while (temp.IsValid())
	{
		/*
			��带 ��η� �������ְ�
			Ȱ��ȭ ��Ų ��, deref�� �ϸ鼭 ���� ���� �ٽ� ��ũ���ش�.
		
		*/

		temp->SetToPath();
		temp->Activate();
		temp = temp.Get()->GetPrevNode();
		
	}
}

void UAstarFinder::SetStartPoint(AAstarNode * Other)
{
	
	
	
}

void UAstarFinder::ResetResult()
{

}

void UAstarFinder::AddNode(AAstarNode * Other)
{
	AllNodes.Add(Other);
	EGLOG(Warning, TEXT("Add : %s"), *AllNodes.Top()->GetName());
	EGLOG(Warning, TEXT("Capacity : %d"), AllNodes.Num());
	for (auto it : AllNodes)
		if (it.IsValid())
			EGLOG(Warning, TEXT("in node : %s"), *it->GetName());
}

void UAstarFinder::ClearNodes()
{
	AllNodes.Empty();
}



