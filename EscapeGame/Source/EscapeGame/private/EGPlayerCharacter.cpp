// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerCharacter.h"
#include "Engine/SceneCapture2D.h"
#include "EGPlayerController.h"
#include"Components/InputComponent.h"
#include "GameSetting/public/EGCharacterSetting.h"
#include "..\public\EGPlayerCharacter.h"
//#include "DT_DataStruct.h"
//#include "GameWidget.h"

//const float AEGPlayerCharacter::MaxHP = 100.0f;
const float AEGPlayerCharacter::MaxWalkingSpeed = 600.0f;
const float AEGPlayerCharacter::MinWalkingSpeed = 0.0f;
const float AEGPlayerCharacter::MaxRunningSpeed = 1200.0f;


// Sets default values
AEGPlayerCharacter::AEGPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitComponents();
	LoadAssets();
	SetupSpringArm();
	//object type을 PlayerCharacter로 해준다
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	//EGLOG(Warning, TEXT("Character Constroucter"));

	
	
}

// Called when the game starts or when spawned
void AEGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//EGLOG(Warning, TEXT("Character Begin Play"));

	auto Con = Cast<AEGPlayerController>(Controller);
	if (Con == nullptr)
	{
		EGLOG(Warning, TEXT("Fail to Casting Controller"));
		return;
	}
	//Stat->LoadDataTable(Con->GetDT_Player());
	
}

// Called every frame
void AEGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

}

// Called to bind functionality to input
void AEGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//axis input
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AEGPlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AEGPlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AEGPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEGPlayerCharacter::Turn);
	
	//Action Input
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this, &AEGPlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ComboAttack"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::ComboAttack);
	PlayerInputComponent->BindAction(TEXT("ChargeAttack"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::ChargeAttack);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::StartRunning);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AEGPlayerCharacter::StopRunning);
	EGLOG(Warning, TEXT("Player input component"));
}

void AEGPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Player Post init compons"));
	//Anim load
	Anim = Cast<UAnim_Player>(GetMesh()->GetAnimInstance());
	if (Anim != nullptr)
	{
	
		//Anim->montage_
		Anim->OnMontageEnded.AddDynamic(this, &AEGPlayerCharacter::OnAttackMontageEnded);


		Anim->OnComboAttackCheckDelegate.AddLambda([this]()->void {
			if (Stat->CheckCanComboAttack())
			{
				//AnimNotify_CanComboAttack 에서 호출될 함수다
				Stat->SetComboStartState();
				Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
				//Anim->Montage->Play();
			}
		});
	}
	
	

	Stat->SetSpeedLimits( MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);
	
}


float AEGPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->TakeDamage(DamageAmount);

	return FinalDamage;
}


void AEGPlayerCharacter::HealHP(float addHP)
{
	Stat->HealHP(addHP);
}

UStatComponent_Player* AEGPlayerCharacter::GetStatComponent()
{
	return Stat;
}

void AEGPlayerCharacter::ChargeAttack()
{
	//Charge Attack은 시동이 걸린 상태에서만 실행될 것이다
	if(Stat->IsAttacking())
		EGLOG(Warning, TEXT("Charge Attack"));
}

void AEGPlayerCharacter::ComboAttack()
{
	if (GetCharacterMovement()->IsFalling())
	{
		AirAttack();
		return;
	}
	
	//시동동작
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
		//EGLOG(Warning, TEXT("Current Comobo : %d"), Stat->GetCurrentCombo());
		Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
		Anim->PlayAttackMontage();//시동이니 ComboAttack1이 재생된다
		//Stat->OnAttacking(true);
		
	}
	//이미 공격중인 상태
	else
	{
		//combo Attack input이 걸렸는지 확인한다.
		//input이 안 걸렸다면 걸어준다
		if (!Stat->CheckCanComboAttack())
		{
			
			Stat->SetComboAttackInput(true);//다음 몽타쥬가 재생될 수 있게 해준다
			Stat->SetChargeAttackInput(false);//대신 차지 공격은 불가능하다
		}
	}
	
}

void AEGPlayerCharacter::AirAttack()
{
	//한가지 동작만 반복될 것이다
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
		Anim->PlayAirAttackMontage();
	}
	

}

void AEGPlayerCharacter::StartRunning()
{
	EGLOG(Warning, TEXT("Run Key Preesed"));

	//if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	//Stat->SetRunning();//달릴 상태로 만들어 준다
	//
	
}

void AEGPlayerCharacter::StopRunning()
{
	EGLOG(Warning, TEXT("Run Key Released"));
	/*if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	Stat->SetWalking();*/
}

void AEGPlayerCharacter::Roll()
{
}








void AEGPlayerCharacter::InitComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	MiniMapArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("MINMAPARM"));
	MapRenderer = CreateDefaultSubobject<UMiniMapRenderComponent>(TEXT("MAPRENDERER"));
	Stat = CreateDefaultSubobject <UStatComponent_Player>(TEXT("STAT"));
	


	//Components Tree
	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	MiniMapArm->SetupAttachment(GetCapsuleComponent());
	MapRenderer->SetupAttachment(MiniMapArm);
	 



	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	MiniMapArm->TargetArmLength = 0.0f;
	MiniMapArm->SetRelativeLocation(FVector(0.0f, 0.0f, 320.0f));
	MiniMapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f,0.0f));

	
	
	SetupSpringArm();
}

void AEGPlayerCharacter::LoadAssets()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_CHARACTER(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangSunrise.KwangSunrise"));
	if (SM_CHARACTER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_CHARACTER.Object);
	}



	///Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


	static ConstructorHelpers::FClassFinder<UAnimInstance>ANI_CHARACTER(TEXT("/Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang_C"));
	if (ANI_CHARACTER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANI_CHARACTER.Class);
	}
}


void AEGPlayerCharacter::SetupSpringArm()
{
	//ĳ���Ϳ� �Ÿ�
	ArmLengthTo = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	////ArmLengthTo = 420.0f;

	MiniMapArm->bUsePawnControlRotation = false;
	MiniMapArm->bInheritPitch = false;
	MiniMapArm->bInheritRoll = false;
	MiniMapArm->bInheritYaw = false;

}


//이것 하나하나가 input event다.
//이것들을 활용해서 움직임을 개선해야 된다
void AEGPlayerCharacter::UpDown( float  NewAxisValue)
{
 
	if (NewAxisValue == 0.0f)return;
		//굳이 안 움직여도 확인할 수 있다.
		/*if (GetCharacterMovement()->IsMovingOnGround())
			EGLOG(Warning, TEXT("I'm moving on ground"));

		if (GetCharacterMovement()->IsFalling())
		EGLOG(Warning, TEXT("I'm falling"));
		*/

		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		
	

}

void AEGPlayerCharacter::LeftRight( float NewAxisValue)
{
	
	if (NewAxisValue == 0.0f)return;
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	//EGLOG(Warning, TEXT("Left or Right Pressed"));
	
}

void AEGPlayerCharacter::LookUp(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	/*if (GetVelocity() == FVector::ZeroVector)
	{
		auto CurrentControllerPitch = GetControlRotation().Pitch;
		if (CurrentControllerPitch + NewAxisValue >= 30.0f)
			NewAxisValue = -CurrentControllerPitch + 30.0f;
		else if(CurrentControllerPitch + NewAxisValue <= -30.0f)
			NewAxisValue = -CurrentControllerPitch - 30.0f;
	}*/
	/*if (GetCharacterMovement()->IsWalking())
		EGLOG(Warning, TEXT("Walk!"));*/
	AddControllerPitchInput(NewAxisValue);
	
}

void AEGPlayerCharacter::Turn( float  NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	AddControllerYawInput(NewAxisValue);
}

void AEGPlayerCharacter::Jump()
{
	if(!Stat->IsAttacking())
	Super::Jump();
	
}

void AEGPlayerCharacter::KeyInputTest()
{
	//playerinputcomponent
	
		
}

void AEGPlayerCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	//if (!Stat->IsAttacking())return;
	//EGLOG(Warning, TEXT("PlayEnded"));
	ComboAttackEnd();
}

void AEGPlayerCharacter::ComboAttackStart()
{
	if (Stat == nullptr)return;
	Stat->SetComboStartState();
}


void AEGPlayerCharacter::ComboAttackEnd()
{
	if (Stat == nullptr)return;
	Stat->SetComboEndState();
}
