// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "AICtrl_Grunt.h"
#include "CharacterAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "EGPlayerCharacter.h"

const float AGruntCharacter::MaxHP = 200.0f;
const float AGruntCharacter::MinWalkingSpeed = 0.0f;
const float AGruntCharacter::MaxWalkingSpeed = 200.0f;
const float AGruntCharacter::MaxRunningSpeed = 700.0f;


AGruntCharacter::AGruntCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set AI Controller
	AIControllerClass = AAICtrl_Grunt::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//Set Attack Range To 100cm
	AttackRange = 100.0f;
	AttackExtent = FVector(100.0f,50.0f,50.0f);
	ATK = 40.0f;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Body(TEXT("SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Skins/Tier_2/Domed/Meshes/Howitzer_Domed.Howitzer_Domed'"));
	if (SM_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Body.Object);

		GetMesh()->SetRelativeLocation(FVector( 0.000000f, 0.000000f,-122.000000f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	GetCapsuleComponent()->SetCapsuleHalfHeight(122.208832f);
	GetCapsuleComponent()->SetCapsuleRadius(63.929523f);


	static ConstructorHelpers::FClassFinder <UAnimInstance>CA_Anim(TEXT("/Game/MyFolder/AnimationBlueprint/GruntAnim.GruntAnim_C"));
	if (CA_Anim.Succeeded())
	{
		
		GetMesh()->SetAnimClass(CA_Anim.Class);
		EGLOG(Warning, TEXT("Anim!!!!"));
	}
	else
		EGLOG(Warning, TEXT("Faile"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	Stat = CreateDefaultSubobject<UStatComponent_Enemy>(TEXT("STAT"));
	if (Stat == nullptr)EGLOG(Warning, TEXT("Enemy's Stat is null"));
}

void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Check Direction of This Actor. Will Draw a line that point to Front 2m
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector()*200.0f,FColor ::Red, true);
}

void AGruntCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->LoadDBfromOwner(MaxHP, MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);

	Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
	if (Anim == nullptr)
	{
		EGLOG(Warning, TEXT("Anim is null"));
	}
	//Anim->AttackEvent_Delegate.AddDynamic(&AGruntCharacter::Attack);
}

float AGruntCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}

void AGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Anim == nullptr)
	{
		EGLOG(Warning, TEXT("Anim is Null"));
		return;
	}
	
	//FVector DPoint = GetActorLocation()+GetMesh()->GetForwardVector()*500.0f;
	//DrawDebugLine(GetWorld(), GetActorLocation(), DPoint, FColor::Cyan, false);
}

void AGruntCharacter::Attack()
{
	EGLOG(Warning, TEXT("Attack! Grunt"));

	
	Anim->PlayAttackMontage();



	/*
	*	Scan Enemy By Attack Range -> Using Sweep by cube
	*	and Take Damage At Scanned Actors
	*	Player Only Can be Damaged
	*/

	//2020 02 12 중단점 16:05
	//Attack에서 잘못 짰다
	//이하 코드는 AnimNotify에서 실행되야할 것들이다. 
	//이 코드를 그 쪽으로 옮긴다.

	////Model 1 Not Access To Stat Component Way
	//FHitResult HitResult;
	//FVector EndPoint = GetActorLocation() + GetActorForwardVector()*AttackRange;
	//FCollisionQueryParams Params(NAME_None, false, this);

	////ECC_EngineTraceChannel2 = 'Player' Trace
	//bool bResult = GetWorld()->SweepSingleByObjectType(HitResult, GetActorLocation(), EndPoint,
	//		FQuat::Identity,ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeBox(AttackExtent),Params);

	////if hit
	//if (bResult)
	//{
	//	auto Player = Cast<AEGPlayerCharacter>(HitResult.GetActor());
	//	if (Player == nullptr)
	//	{
	//		EGLOG(Warning, TEXT("Casting Error"));
	//		return;
	//	}

	//	FDamageEvent DamageEvent;
	//	Player->TakeDamage(ATK,DamageEvent, GetController(),this);
	//	
	//}

}
