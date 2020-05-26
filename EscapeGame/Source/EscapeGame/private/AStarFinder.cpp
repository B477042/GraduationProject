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
	//방문해야될 노드가 비워질 때까지
	while (ToVisiteNodes.IsEmpty())
	{
		
		//Queue에서 하나를 꺼낸다
		ToVisiteNodes.Dequeue(PopedNode);
		
	//인근노드들의 주변 노드들이 있다면
		if (PopedNode->NearNodes.GetData() != nullptr)
			//인근 노드들의 값을 계산한다
		{
			for (auto it : PopedNode->NearNodes)
			{
				//방문했던 노드면 넘어간다.
				if (it->IsVisitedNode())continue;

				it->CalcFCount(Start->GetActorLocation(), Goal->GetActorLocation());
				//인근노드들 Count계산 끝나면 필요 없겠지
				;
				////만약 지금 탐색중인 인근 노드가 Goal과 같다면 for문을 나간다
				//if (it == Goal)break;
			}

			//꺼낸 노드의 주변 노드들의 이전 노드를 꺼낸 노드로 설정해준다. 
			PopedNode->SetNearNodesPrevAsMe();

			//주변 노드들을 FCount가 작은 순으로 넣어야 된다. ->연산자 오퍼레이터가 잘 안 된다 그냥 패스
			
			//PopedNode->SortNearNodes();

			for (auto it : PopedNode->NearNodes)
			{
				ToVisiteNodes.Enqueue(it.Get());
			}

		}

		//노드의 방문을 마친다
		PopedNode->VisitNode();

		//꺼낸 노드가 Goal과 위치가 같다면 -> 안먹힌다면 같은 객체를 가리키는지 검사
		if (PopedNode->GetActorLocation() == Goal->GetActorLocation())
		{
			//GoalNode를 설정해주고 ToVisiteNode를 비워준다
			GoalNode = PopedNode.Get();
			ToVisiteNodes.Empty();
		}

		
	}

	//골 노드를 찾았다면 경로들을 활성화 시켜준다
	if(GoalNode.IsValid())
	ShowPath();
}

void AAstarFinder::ShowPath()
{
	TWeakObjectPtr<AAStarNode> temp = GoalNode;
	
	//처음 시작점으로 온다면 
	while (temp.IsValid())
	{
		/*
			노드를 경로로 설정해주고
			활성화 시킨 후, deref를 하면서 이전 노드로 다시 링크해준다.
		
		*/

		temp->SetToPath();
		temp->Activate();
		temp = temp.Get()->GetPrevNode();
		
	}
}



