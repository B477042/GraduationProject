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
	//방문해야될 노드가 비워질 때까지
	while (!ToVisiteNodes.IsEmpty())
	{
		EGLOG(Warning, TEXT("%d Try"), i);
		i++;
		//Queue에서 하나를 꺼낸다
		ToVisiteNodes.Dequeue(PopedNode);
		EGLOG(Warning, TEXT("Current Node : %s"), *PopedNode->GetName());
		//노드의 방문을 마친다
		PopedNode->VisitNode();

		//꺼낸 노드가 Goal과 위치가 같다면 -> 안먹힌다면 같은 객체를 가리키는지 검사
		if (PopedNode->GetActorLocation() == Goal->GetActorLocation())
		{
			//GoalNode를 설정해주고 ToVisiteNode를 비워준다
			EGLOG(Error, TEXT("Goal Find! : %s"), *PopedNode->GetName());
			GoalNode = PopedNode.Get();
			ToVisiteNodes.Empty();
			break;
		}

	//인근노드들의 주변 노드들이 있다면
		if (PopedNode->NearNodes.GetData() != nullptr)
			//인근 노드들의 값을 계산한다
		{
			for (auto it : PopedNode->NearNodes)
			{
				//유효하지 않다면 넘어간다
				if(!it.IsValid())continue;
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
			for (auto it : PopedNode->NearNodes)
			{
				//유효하지 않다면 넘어간다
				if (!it.IsValid())continue;
				//방문했던 노드면 다시 안 넣어도 된다
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"),*it->GetName());
				ToVisiteNodes.Enqueue(it.Get());
				
			}
		
			
		}

	

		
	}

	//골 노드를 찾았다면 경로들을 활성화 시켜준다
	if(GoalNode.IsValid())
	ShowPath();
}

void UAstarFinder::ShowPath()
{

	TWeakObjectPtr<AAstarNode> temp = GoalNode;
	if (!temp.IsValid())EGLOG(Error, TEXT("Goal node is null"));
	//처음 시작점으로 온다면 
	while (temp.IsValid())
	{
		/*
			노드를 경로로 설정해주고
			활성화 시킨 후, deref를 하면서 이전 노드로 다시 링크해준다.
		
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
//Game instance에서 목표가 되는 오브젝트를 우선적으로 불러와서 찾아준다. 
void UAstarFinder::SetGoalPoint(AAstarNode * Other)
{
	GoalNode = Other;
}
//모든 노드의 AStar 연산값을 지워준다
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



