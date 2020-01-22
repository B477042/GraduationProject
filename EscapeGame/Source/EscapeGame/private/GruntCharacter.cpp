// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "EnemyAIController.h"
#include "CharacterAnimInstance.h"


AGruntCharacter::AGruntCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	


	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Body(TEXT("SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Skins/Tier_2/Domed/Meshes/Howitzer_Domed.Howitzer_Domed'"));
	if (SM_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Body.Object);

		GetMesh()->SetRelativeLocation(FVector( 0.000000f, 0.000000f,-122.000000f));
		
	}
	GetCapsuleComponent()->SetCapsuleHalfHeight(122.208832f);
	GetCapsuleComponent()->SetCapsuleRadius(63.929523f);


	static ConstructorHelpers::FClassFinder <UAnimInstance>CA_Anim(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/GruntAnim.GruntAnim_C'"));
	if (CA_Anim.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimClass(CA_Anim.Class);
	}
}

void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGruntCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
