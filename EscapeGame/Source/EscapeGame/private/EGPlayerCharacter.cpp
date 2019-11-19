// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerCharacter.h"
#include"Engine/SceneCapture2D.h"
#include "EGPlayerController.h"
#include"GameSetting/public/EGCharacterSetting.h"
//#include "GameWidget.h"


// Sets default values
AEGPlayerCharacter::AEGPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitComponents();
	LoadAssets();
	SetupSpringArm();
	EGLOG(Warning, TEXT("Character Constroucter"));
	
}

// Called when the game starts or when spawned
void AEGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	EGLOG(Warning, TEXT("Character Begin Play"));
	
}

// Called every frame
void AEGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	//GetController()
	
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
	EGLOG(Warning, TEXT("Player input component"));
}

void AEGPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Player Post init compons"));
}

const UCharacterStatComponent * AEGPlayerCharacter::GetStatComponent()
{
	return Stat;
}




void AEGPlayerCharacter::InitComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	MiniMapArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("MINMAPARM"));
	MapRenderer = CreateDefaultSubobject<UMiniMapRenderComponent>(TEXT("MAPRENDERER"));
	Stat = CreateDefaultSubobject <UCharacterStatComponent>(TEXT("STAT"));


	//MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MINIMAPSPRINGARM"));
	////MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MINIMAPCAPTURE"));
	//MiniMapCapture = CreateDefaultSubobject<ASceneCapture2D>(TEXT("MINIMAPCAPTURE"));

	//Components Tree
	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	MiniMapArm->SetupAttachment(GetCapsuleComponent());
	MapRenderer->SetupAttachment(MiniMapArm);
	 

	//MiniMapSpringArm->SetupAttachment(GetCapsuleComponent());
	//MiniMapCapture->SetupAttachment(MiniMapSpringArm);
	


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
	//static ConstructorHelpers::FClassFinder<UBlueprint>ANI_CHARACTR(TEXT("/Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang_C"));
	/*
	Material'/Game/MyFolder/MiniMap/MiniMapRender_Mat.MiniMapRender_Mat'
		TextureRenderTarget2D'/Game/MyFolder/MiniMap/MiniMapRender.MiniMapRender'
		Blueprint'/Game/MyFolder/MiniMap/MiniMapCam.MiniMapCam'
		StaticMesh'/Game/MyFolder/SkeletalMeshs/SM_Gold_Door.SM_Gold_Door'
		WidgetBlueprint'/Game/MyFolder/UI/UI_HUD.UI_HUD'
		AnimBlueprint'/Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang'*/
	

	//static ConstructorHelpers::FClassFinder<ASceneCapture2D>T_CAPTURE(TEXT("/Game/MyFolder/MiniMap/MiniMapCam.MiniMapCam_C"));
	//if (T_CAPTURE.Succeeded())
	//{
	//	MiniMapCapture = Cast<ASceneCapture2D>(T_CAPTURE.Class);
	//	
	//	SetupMiniMap();
	//}
	//else
	//	EGLOG(Error, TEXT("FUCKKKKKKKKKKKK"));
	
	
}
//�̴ϸ� ĸ�Ŀ� ���������� �������ش�
//void AEGPlayerCharacter::SetupMiniMap()
//{
//	/*auto characterSetting = GetDefault<UEGCharacterSetting>();
//	if (characterSetting->TargetTexture.IsValidIndex(0) )
//	{
//		MiniMapCapture->TextureTarget  = characterSetting->TargetTexture.GetData()->GetAssetPathName();
//	}*/
//	/*static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>T_CAPTURE(TEXT("/Game/MyFolder/MiniMap/MiniMapRender.MiniMapRender"));
//	if (T_CAPTURE.Succeeded())
//	{
//		
//		MiniMapCapture->TextureTarget =T_CAPTURE.Object;
//	}*/
//	//MiniMapSpringArm->TargetArmLength = 0.0f;
//	//MiniMapSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 330.0f));
//	//MiniMapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f,0.0f));
//	//
//	//
//	////MiniMapCapture->TextureTarget=MiniMapRender;
//	//MiniMapCapture->bCaptureEveryFrame = false;
//
//	//MiniMapSpringArm->actor
//
//	//MiniMapSpringArm->bUsePawnControlRotation = false;
//	//MiniMapSpringArm->bInheritPitch = false;
//	//MiniMapSpringArm->bInheritRoll =false;
//	//MiniMapSpringArm->bInheritYaw = false;
//	//MiniMapSpringArm->bDoCollisionTest = false;
//	//bUseControllerRotationYaw = false;
//
//}


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

	////ArmLengthTo = 420.0f;

	MiniMapArm->bUsePawnControlRotation = false;
	MiniMapArm->bInheritPitch = false;
	MiniMapArm->bInheritRoll = false;
	MiniMapArm->bInheritYaw = false;

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

