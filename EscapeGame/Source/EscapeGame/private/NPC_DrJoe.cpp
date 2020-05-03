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
	
	
}

void ANPC_DrJoe::OnNextClicked()
{
}

void ANPC_DrJoe::OnPrevClicked()
{
}
