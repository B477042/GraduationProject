// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_DrJoe.h"

ANPC_DrJoe::ANPC_DrJoe()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT(""));
	if (SM_MESH.Succeeded())
	{

	}

	static ConstructorHelpers::FObjectFinder<UAnimInstance>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/BP_Tutorial/BP_AnimDoctor.BP_AnimDoctor'"));
	if (ANIM.Succeeded())
	{
		Anim = ANIM.Object;
	}
}

void ANPC_DrJoe::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC_DrJoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
