// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_DrJoe.h"


ANPC_DrJoe::ANPC_DrJoe()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_MESH(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_eric_rigged_001_ue4/rp_eric_rigged_001_ue4.rp_eric_rigged_001_ue4'"));
	if (SM_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_MESH.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(97.564583f);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/BP_Tutorial/BP_AnimDoctor.BP_AnimDoctor_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}
	Name = "Dr.Joe";

	EventCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EVENTCOLLISION"));
	EventCollision->SetupAttachment(GetMesh());

	EventCollision->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	EventCollision->SetGenerateOverlapEvents(true);
	EventCollision->SetSphereRadius(800.0f);



}

void ANPC_DrJoe::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC_DrJoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC_DrJoe::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EventCollision->OnComponentBeginOverlap.AddDynamic(this,&ANPC_DrJoe::OnPlayerOverlap );
}

void ANPC_DrJoe::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}
