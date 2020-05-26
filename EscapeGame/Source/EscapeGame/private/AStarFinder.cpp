// Fill out your copyright notice in the Description page of Project Settings.


#include "AstarFinder.h"

// Sets default values
AAstarFinder::AAstarFinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAstarFinder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAstarFinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAstarFinder::AStar(AAStarNode * Start, AAStarNode *Goal)
{
	if (ToVisiteNodes.IsEmpty())
	{
		ToVisiteNodes.Enqueue(Start);

	}
	TWeakObjectPtr<AAStarNode> PopedNode;
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

void AAstarFinder::ShowPath()
{
	TWeakObjectPtr<AAStarNode> temp = GoalNode;
	
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



