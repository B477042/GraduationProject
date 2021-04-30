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

void AAStarFinder::StartPathFinder(AAstarNode * Other, EPathTarget Mode)
{
	
		PathFind(Other,Mode);
	
}
void AAStarFinder::SetKeyPoint(AAstarNode* Other)
{
	KeyNode = Other;
}

//Game instance에서 목표가 되는 오브젝트를 우선적으로 불러와서 찾아준다. 
void AAStarFinder::SetGoalPoint(AAstarNode * Other)
{
	GoalNode = Other;
}
//모든 노드의 PathFind 연산값을 지워준다
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
				if (!it.IsValid())continue;
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

			//정렬용 임시 보관소
		//	TArray<TWeakObjectPtr<AAstarNode>>tempList;
		//	tempList.Init(nullptr, 4);
			
		
		
			//fcount 순으로 정렬
			for (int k = 0; k < PopedNode->NearNodes.Num();++k)
			{
				for (int j = k+1 ; j < PopedNode->NearNodes.Num()-1; ++j)
				{
					//비교전 유효성 검사
					if (!PopedNode->NearNodes[k].IsValid() || !PopedNode->NearNodes[j].IsValid())continue;
					if (PopedNode->NearNodes[k]->GetF() > PopedNode->NearNodes[j]->GetF())
						PopedNode->NearNodes.Swap(k, j);
				}

			}

		 
			//주변 노드들을 FCount가 작은 순으로 넣어야 된다. ->연산자 오퍼레이터가 잘 안 된다 그냥 패스
			//정렬된 순서대로 넣는다
			for (auto it : PopedNode->NearNodes)
			{
				
				//유효하지 않다면 넘어간다
				if (!it.IsValid())continue;

				//방문했던 노드면 다시 안 넣어도 된다
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisiteNodes.Enqueue(it.Get());

				////정렬 코드
				//for (int i = 0; i < tempList; i++)
				//{


				//}

			}

			

			//TLinkedList<TSoftObjectPtr<AAstarNode>>  LLSort;
			//for (auto it : PopedNode->NearNodes)
			//{
			//	

			//	// 리스트에 연결 시킬 때 값대로 들어가게 
			//	

			//}





			////tempList.Sort();
			//for (auto it : tempList)
			//	ToVisiteNodes.Enqueue(it);


		}
	}

	//골 노드를 찾았다면 경로들을 활성화 시켜준다
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

		//꺼낸 노드가Key와 위치가 같다면 -> 안먹힌다면 같은 객체를 가리키는지 검사
		if (PopedNode->GetActorLocation() == Key->GetActorLocation())
		{
			//GoalNode를 설정해주고 ToVisiteNode를 비워준다
			EGLOG(Error, TEXT("Key Find! : %s"), *PopedNode->GetName());
			KeyNode = PopedNode.Get();
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
				if (!it.IsValid())continue;
				//방문했던 노드면 넘어간다.
				if (it->IsVisitedNode())continue;

				it->CalcFCount(Start->GetActorLocation(), Key->GetActorLocation());
				//인근노드들 Count계산 끝나면 필요 없겠지
				;
				////만약 지금 탐색중인 인근 노드가 Goal과 같다면 for문을 나간다
				//if (it == Goal)break;
			}

			//꺼낸 노드의 주변 노드들의 이전 노드를 꺼낸 노드로 설정해준다. 
			PopedNode->SetNearNodesPrevAsMe();





			//fcount 순으로 정렬
			for (int k = 0; k < PopedNode->NearNodes.Num(); ++k)
			{
				for (int j = k + 1; j < PopedNode->NearNodes.Num() - 1; ++j)
				{
					//비교전 유효성 검사
					if (!PopedNode->NearNodes[k].IsValid() || !PopedNode->NearNodes[j].IsValid())continue;
					if (PopedNode->NearNodes[k]->GetF() > PopedNode->NearNodes[j]->GetF())
						PopedNode->NearNodes.Swap(k, j);
				}

			}



			//정렬용 임시 보관소
		//	TArray<TWeakObjectPtr<AAstarNode>>tempList;
		//	tempList.Init(nullptr, 4);
			//주변 노드들을 FCount가 작은 순으로 넣어야 된다. ->연산자 오퍼레이터가 잘 안 된다 그냥 패스
			for (auto it : PopedNode->NearNodes)
			{
				//유효하지 않다면 넘어간다
				if (!it.IsValid())continue;
				//방문했던 노드면 다시 안 넣어도 된다
				if (it->IsVisitedNode())continue;
				//PopedNode->VisitNode();
				EGLOG(Warning, TEXT("Enqueue : %s"), *it->GetName());
				ToVisiteNodes.Enqueue(it.Get());

				////정렬 코드
				//for (int i = 0; i < tempList; i++)
				//{


				//}

			}


			////tempList.Sort();
			//for (auto it : tempList)
			//	ToVisiteNodes.Enqueue(it);


		}
	}

	//골 노드를 찾았다면 경로들을 활성화 시켜준다
	if (KeyNode.IsValid())
		ShowPath(EPathTarget::Key);
}




