// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyBossCharacter.h"

AEnermyBossCharacter::AEnermyBossCharacter()
{
	AIControllerClass = AEnermyBossCharacter::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	initComponents();
	loadAsset();
}

void AEnermyBossCharacter::initComponents()
{

}

void AEnermyBossCharacter::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_BODY(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));
	if (SM_BODY.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(SM_BODY.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


}
