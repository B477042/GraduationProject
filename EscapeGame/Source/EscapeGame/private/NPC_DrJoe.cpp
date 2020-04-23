// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_DrJoe.h"
#include "Pawn_Camera.h"

ANPC_DrJoe::ANPC_DrJoe()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_MESH(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_eric_rigged_001_ue4/rp_eric_rigged_001_ue4.rp_eric_rigged_001_ue4'"));
	if (SM_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_MESH.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/BP_Tutorial/BP_AnimDoctor.BP_AnimDoctor_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIM.Class);
	}

	TalkingCount = 0;
	OtherPlayer = nullptr;
	name = "Dr.Joe";

}

void ANPC_DrJoe::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC_DrJoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//말 하고 싶어하는 플레이어가 없다면 찾습니다
	if (OtherPlayer == nullptr)
	{
		WannaTalkTo();
	}

}

void ANPC_DrJoe::WannaTalkTo()
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
			//카메라 폰을 찾아낸다
			auto resultChara = Cast<APawn_Camera>(OverlapResult.Actor);
			if (resultChara == nullptr)continue;
			//플레이어가 조종하는게 맞다면 말을 건다
			if (resultChara->GetController()->IsPlayerController())
			{
				OtherPlayer = resultChara;
				resultChara->StartListenTo(this);
				TalkTo();
				return;
			}


		}
	}

	TalkTo();
}

void ANPC_DrJoe::TalkTo()
{

	//만약 말을 걸어야될 대상이 없다면 리턴한다
	if (OtherPlayer == nullptr)return;

	auto tempPlayer = Cast<APawn_Camera>(OtherPlayer);
	if (tempPlayer == nullptr)return;

	tempPlayer->ListenTalk(this, FText::FromString("SyncTest"));
	
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
}

void ANPC_DrJoe::OnNextClicked()
{
}

void ANPC_DrJoe::OnPrevClicked()
{
}
