// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerCharacter.h"
#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"
//#include "GameWidget.h"


// Sets default values
AEGPlayerCharacter::AEGPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitComponents();
	LoadAssets();
	SetupSpringArm();
	

	
}

// Called when the game starts or when spawned
void AEGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	
	
	//MiniMapCapture->CaptureScene();
//	GetController()->
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

}


void AEGPlayerCharacter::InitComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	//MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MINIMAPSPRINGARM"));
	//MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MINIMAPCAPTURE"));

	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	//MiniMapSpringArm->SetupAttachment(GetCapsuleComponent());
	//MiniMapCapture->SetupAttachment(MiniMapSpringArm);


	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	

	//MiniMapSpringArm->TargetArmLength = 0.0f;
	//MiniMapSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 330.0f));
	//MiniMapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f,0.0f));
	//
	//
	////MiniMapCapture->TextureTarget=MiniMapRender;
	//MiniMapCapture->bCaptureEveryFrame = false;
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
	//static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>T_CAPTURE(TEXT("/Game/MyFolder/MiniMap/MiniMapRender.MiniMapRender"));
	//if (T_CAPTURE.Succeeded())
	//{
	//	
	//	MiniMapCapture->TextureTarget =T_CAPTURE.Object;
	//}
	
	
}


void AEGPlayerCharacter::SetupSpringArm()
{
	//캐릭터와 거리
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

	////ArmLengthTo = 420.0f;
	//MiniMapSpringArm->bUsePawnControlRotation = false;
	//MiniMapSpringArm->bInheritPitch = false;
	//MiniMapSpringArm->bInheritRoll =false;
	//MiniMapSpringArm->bInheritYaw = false;
	//MiniMapSpringArm->bDoCollisionTest = false;
	//bUseControllerRotationYaw = false;
}



void AEGPlayerCharacter::UpDown(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AEGPlayerCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AEGPlayerCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AEGPlayerCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

