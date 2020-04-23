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

	//�� �ϰ� �;��ϴ� �÷��̾ ���ٸ� ã���ϴ�
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

	


	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);


	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);



	if (bResult)
	{

		for (auto OverlapResult : OverlapResults)
		{
			//ī�޶� ���� ã�Ƴ���
			auto resultChara = Cast<APawn_Camera>(OverlapResult.Actor);
			if (resultChara == nullptr)continue;
			//�÷��̾ �����ϴ°� �´ٸ� ���� �Ǵ�
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

	//���� ���� �ɾ�ߵ� ����� ���ٸ� �����Ѵ�
	if (OtherPlayer == nullptr)return;

	auto tempPlayer = Cast<APawn_Camera>(OtherPlayer);
	if (tempPlayer == nullptr)return;

	tempPlayer->ListenTalk(this, FText::FromString("SyncTest"));
	
	/*
	////switch (TalkingCount)
	////{
	////case 0:

	////	�츮�� ���� ������ 5���̳� �ƴٳ�.�� �ܰ��� ����� �츮�� ���������� �ʾ�
	////	
	////	break;
	/////*case 1:

	////		diagram = "�� ���п� ��Ʈ�ѷ��� �ϼ� �Ǿ��ٳ�.\n�ܰ��ε��� ����ϴ� �κ� �߿� �ϳ��� ������ �� �����ɼ�";
	////		
	////		break;
	////case 2:

	////		diagram = "�� HMD�� ���� ��Ʈ�� ������ �ͼ� �ɾ��ְԳ�.\n��� �����ϴ����� HMD�� �޽����� �����ٰ�";

	////		break;
	////case 3:
	////		diagram = "���� �ٸ� �κ���� �̸� �׽�Ʋ �ؼ� ���� ������ �������״�\n���� �ؼ� ����� �κ��� �븮�� ���� �ȴٳ�";

	////		break;
	////case 4:

	////		diagram = "�츮�� ������ �κ��� �� �ѱ� ���̶� �����ϰ� ����������Ѵ�.\n�� ���� �� �ϳİ�? ";

	////		break;
	////case 5:

	////		diagram = "���� �����ϴ� �ͺ��� ������ �Ƽ� �δ°� �� ������� ���Ƽ�";

	////		break;
	////case 6:

	////		diagram = "�ƹ�ư ���� Ż���ؾߵ�. �� ���� �������� �ϴ� �� �����ϱ�";

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
