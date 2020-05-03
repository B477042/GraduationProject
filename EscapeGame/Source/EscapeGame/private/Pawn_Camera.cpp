// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Camera.h"
#include "NPCCharacter.h"
#include "DialogueWidget.h"
#include "Tutorial_Controller.h"

// Sets default values
APawn_Camera::APawn_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	BoxCollision= CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxCollision;
	//BoxCollision->SetupAttachment(RootComponent);
	Cam->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	BoxCollision -> SetCollisionProfileName(TEXT("PlayerCharacter"));
	//BoxCollision->SetGenerateOverlapEvents(true);

	
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_DIALOGUE(TEXT("DataTable'/Game/MyFolder/DataTable/Dialogue.Dialogue'"));
	if (DT_DIALOGUE.Succeeded())
	{
		dialogueTable = DT_DIALOGUE.Object;
	}
}

// Called when the game starts or when spawned
void APawn_Camera::BeginPlay()
{
	Super::BeginPlay();
	float X, Y, Z, Roll, Yaw, Pitch;
	SetActorLocationAndRotation(FVector(X = -10.000000, Y = 230.000000, Z = 40.000000), FRotator(Pitch = 0.000000, Yaw = -90.000114, Roll = 0.000000));
	/*auto tempCon = Cast<ATutorial_Controller>(GetController());
	if (tempCon != nullptr)
		MyController = tempCon;*/
}

// Called every frame
void APawn_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APawn_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawn_Camera::ListenTalk(TWeakObjectPtr<ACharacter> Talker, FText Diagram)
{
	auto tempController = Cast<ATutorial_Controller>(Controller);
	if (tempController == nullptr)
	{
		EGLOG(Warning, TEXT("Temp Controller failed"));
		return;
	}


	auto widget = Cast<UDialogueWidget>(tempController->UIWidgetInstance);
	if (widget == nullptr)
	{
		EGLOG(Warning, TEXT("Temp widget failed"));
		return;
	}
	EGLOG(Warning,*Diagram.ToString() );
	widget->RecieveDiagram(Diagram);

}

void APawn_Camera::StartListenTo(TWeakObjectPtr<ACharacter>Talker)
{
	auto tempTalker = Cast<ANPCCharacter>(Talker);
	//Casting Test
	if (tempTalker==nullptr)
	{
		EGLOG(Warning, TEXT("Temp Talker failed"));
		return;
	}
	//player의 컨트롤러를 casting한다
	auto tempController = Cast<ATutorial_Controller>(Controller);
	if (tempController==nullptr)
	{ 
		EGLOG(Warning, TEXT("Temp Controller failed"));
		return;
	}

	
	auto widget = Cast<UDialogueWidget>(tempController->UIWidgetInstance);
	if (widget == nullptr)
	{
		EGLOG(Warning, TEXT("Temp widget failed"));
		return;
	}
	//Widget에 이름을 적어준다
	widget->SetTalker(tempTalker, FText::FromString(tempTalker->GetName()));
	
	EGLOG(Error, TEXT("I Told U!!!!!"));
}

void APawn_Camera::OnNextClicked()
{
}

void APawn_Camera::OnPrevClicked()
{
}

void APawn_Camera::findTalkers()
{
	auto Center = GetActorLocation();

	auto World = GetWorld();
	if (World == nullptr)return;
	// Scan 8m
	float DetectRadius = 800.0f;




	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);


	//PlayerCharacter를 Overlap 반응으로 찾아낸다. 모양은 DetectRadius만한 구
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);



	if (bResult)
	{

		for (auto OverlapResult : OverlapResults)
		{
			


		}
	}


}



/*
	////switch (TalkingCount)
	////{
	////case 0:

	////	우리가 여기 갖힌지 5일이나 됐다네.이 외계인 놈들은 우리를 감시하지도 않아
	////
	////	break;
	/////*case 1:

	////		diagram = "그 덕분에 컨트롤러가 완성 되었다네.\n외계인들이 사용하는 로봇 중에 하나를 조종할 수 있을걸세";
	////
	////		break;
	////case 2:

	////		diagram = "이 HMD를 쓰고 노트북 앞으로 와서 앉아주게나.\n어떻게 조종하는지는 HMD로 메시지를 적어줄게";

	////		break;
	////case 3:
	////		diagram = "내가 다른 로봇들로 미리 테스틀 해서 얻은 정보도 보내줄테니\n참고 해서 여기로 로봇을 대리고 오면 된다네";

	////		break;
	////case 4:

	////		diagram = "우리가 조종할 로봇은 딱 한기 뿐이라 신중하게 움직여줘야한다.\n왜 내가 안 하냐고? ";

	////		break;
	////case 5:

	////		diagram = "직접 조종하는 것보다 옆에서 훈수 두는게 더 재밌을거 같아서";

	////		break;
	////case 6:

	////		diagram = "아무튼 빨리 탈출해야돼. 곧 달을 떠날려고 하는 것 같으니까";

	////		break;
	////default:
	////	break;
	////}
	////
	*/