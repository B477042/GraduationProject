// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter_Gunner.h"
#include "EnemyAIController_Gunner.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "EGPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimInstance_Gunner.h"
#include "Sound/SoundCue.h"
#include "Perception/AISenseConfig.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"

#include "Weapon.h"

AEnemyCharacter_Gunner::AEnemyCharacter_Gunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController_Gunner::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	
	SFX_Foot_L = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Foot_L"));
	SFX_Foot_R = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Foot_R"));
	StatComponent = CreateDefaultSubobject<UStatComponent_Gunner>(TEXT("StatComponent"));
	

	
	SFX_Foot_L->SetupAttachment(GetMesh());
	SFX_Foot_R->SetupAttachment (GetMesh());
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	float X = 0.0f, Y = 0.0f, Z = 0.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_BODY(TEXT("SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));
	if (SM_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_BODY.Object);
		GetMesh()->SetRelativeLocation(FVector(X = 0.000000, Y = 0.000000, Z = -90.000000));
		GetMesh()->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 270.000f, Roll = 0.000000f));
	}



	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance_Gunner>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/Anim_Gunner.Anim_Gunner_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}



	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_FOOTr(TEXT("SoundCue'/Game/MyFolder/Sound/SE/Foot_right_Cue.Foot_right_Cue'"));
	if (SFX_FOOTr.Succeeded())
	{
		SFX_Foot_L->Sound = SFX_FOOTr.Object;
	
		SFX_Foot_L->bAutoActivate = false;
	
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_FOOTl(TEXT("SoundCue'/Game/MyFolder/Sound/SE/Foot_left_Cue.Foot_left_Cue'"));
	if (SFX_FOOTl.Succeeded())
	{
		
		SFX_Foot_R->Sound = SFX_FOOTl.Object;
		
		SFX_Foot_R->bAutoActivate = false;
	}

	//WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));


	//bCanFire = true;
	//Cooltime = 0.0f;


	//Point_Muzzle = FVector::ZeroVector;

	
	Path_UsingThisWeapon = nullptr;

	//setupPerception();
}
void  AEnemyCharacter_Gunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	//if (bCanFire)
	//{
	//	//EGLOG(Error, TEXT("Cooltime error"));
	//	return;
	//}


	//Cooltime += DeltaTime;
	//if (Cooltime >= 0.1f)
	//{
	//	bCanFire = true;
	//
	//	Cooltime = 0.0f;

	//	//EGLOG(Warning, TEXT("Can fire"));	
	////tick 중단
	//	SetActorTickEnabled(false);
	//}


}


void AEnemyCharacter_Gunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	


//	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this,&AEnemyCharacter_Gunner::PerceptionUpdated);

}

void AEnemyCharacter_Gunner::BeginPlay()
{
	Super::BeginPlay();
	//if(WeaponMesh)
	//WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));
	//EGLOG(Error, TEXT("Chara Begin"));

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::SaveGame);


	Anim = Cast<UAnimInstance_Gunner>(GetMesh()->GetAnimInstance());
	if (!Anim)EGLOG(Error, TEXT("********Anim Cast Failed********"));

	StatComponent->HPChangedDelegate.AddLambda([this]()->void {
		HPBar = Cast<UProgressBar>(HPBarWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("HPBar")));
		if (!HPBar)
		{
			EGLOG(Warning, TEXT(" HPBar Failed"));
			return;
		}
		HPBar->SetPercent(StatComponent->GetHPRatio());
		});

	StatComponent->HPZeroDelegate.AddLambda([this]()->void {
		//Anim Dead 설정
		//AIController 중단
		
		/*if (Anim->IsAnyMontagePlaying())
		{
			Anim->StopAllMontages(0.0f);
			Anim->StopSlotAnimation();
		}*/

		Anim->SetDead(true);
		auto AICon = Cast<AEnemyAIController_Gunner>(GetController());
		if (AICon)
		{
			AICon->StopAI();
		}


		});

	//Async Materials of mesh
	LoadGunnerMaterialAsset();
	//Async Load Weapon
	LoadWeapon();

	//EGLOG(Log, TEXT("%s"),* BodyMaterials[0].ToString());
	



}

void AEnemyCharacter_Gunner::BeginDestroy()
{
	Super::BeginDestroy();

}



void AEnemyCharacter_Gunner::SaveGame(UEGSaveGame * SaveInstance)
{
	Super::SaveGame(SaveInstance);
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("Save Instance is nullptr"));
		return;
	}

	auto SaveData = SaveInstance->D_Enemies.Find(GetName());
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Can't find %s's Data"), *GetName());
		return;
	}
	//Hp저장
	StatComponent->SaveGame(SaveData);
	

}

void AEnemyCharacter_Gunner::LoadGame(const UEGSaveGame * LoadInstance)
{
	Super::LoadGame(LoadInstance);
	
	if (!GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Dead actor"));
		return;
	}

	auto LoadData = LoadInstance->D_Enemies.Find(GetName());
	if (!LoadData)
	{
		EGLOG(Log, TEXT("%s Can't find Data"), *GetName());
		return;
	}
	StatComponent->LoadGame(LoadData);
	EGLOG(Error, TEXT("Find %s's Data"), *GetName());
}


//void AEnemyCharacter_Gunner::PlaySFXGun()
//{
//	bool bTemp = UKismetMathLibrary::RandomBool();
//
//	if (bTemp)
//		SFX_Fire1->Play();
//	else
//		SFX_Fire2->Play();
//}

void AEnemyCharacter_Gunner::LoadGunnerMaterialAsset()
{
	UEGGameInstance* const GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance Error"));
		return;
	}



	//Mix materials
	idx_Body = FMath::RandRange(0,BodyMaterials.Num()-1);
	idx_Decal = FMath::RandRange(0, DecalMaterials.Num()-1);
	idx_Visor = FMath::RandRange(0, VisorMaterials.Num()-1);


	ToLoad.Add(BodyMaterials[idx_Body]);
	ToLoad.Add(VisorMaterials[idx_Visor]);
	ToLoad.Add(DecalMaterials[idx_Decal]);

	for (int i = 0; i < 3; ++i)
	{
		EGLOG(Error, TEXT("%s" ), *ToLoad[i].ToString());
	}

	//Load Body Material
	 GameInstance->StreamableManager.RequestAsyncLoad(ToLoad,
		FStreamableDelegate::CreateUObject(this, &AEnemyCharacter_Gunner::LoadMaterial));
	 
}

void AEnemyCharacter_Gunner::LoadMaterial()
{
	EGLOG(Error, TEXT(" Loaded!"));
	if (ToLoad.Num() <= 0)
	{
		EGLOG(Error, TEXT("Nothing Loaded!"));
		return;
	}
	TSoftObjectPtr<UMaterial>BodyMaterialAsset(ToLoad[idx_MBody]);
	UMaterial* BodyMaterial = BodyMaterialAsset.Get();
	if (BodyMaterial)
	{
		GetMesh()->SetMaterial(idx_MBody, BodyMaterial);
		UE_LOG(LogTemp, Log, TEXT("Body Loaded"));
	}

	TSoftObjectPtr<UMaterialInstance>VisorMaterialAsset(ToLoad[idx_MVisor]);
	UMaterialInstance* VisorMaterial = VisorMaterialAsset.Get();
	if (VisorMaterial)
	{
		GetMesh()->SetMaterial(idx_MVisor, VisorMaterial);
		UE_LOG(LogTemp, Log, TEXT("Visor Loaded"));
	}
	TSoftObjectPtr<UMaterial>DecalMaterialAsset(ToLoad[idx_MDecal]);
	UMaterial* DecalMaterial = DecalMaterialAsset.Get();
	if (DecalMaterial)
	{
		GetMesh()->SetMaterial(idx_MDecal,DecalMaterial);
		UE_LOG(LogTemp, Log, TEXT("Decal Loaded"));
	}

	ToLoad.Empty();
}

void AEnemyCharacter_Gunner::LoadWeapon()
{
	UEGGameInstance* const GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance Error"));
		return;
	}

	//For Test, Load Assert Rifle
	Path_UsingThisWeapon = &Path_Weapons[0];

	GameInstance->StreamableManager.RequestAsyncLoad(*Path_UsingThisWeapon  ,
		FStreamableDelegate::CreateUObject(this, &AEnemyCharacter_Gunner::SpawnAndAttachGun));

}

void AEnemyCharacter_Gunner::SpawnAndAttachGun()
{
	if (Weapon.IsValid())
	{
		EGLOG(Error, TEXT("Can't attach more weapons"));
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	


	UWorld* const World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("Invalided World"));
		return;
	}
	TSubclassOf<AWeapon>WeaponClass = Path_UsingThisWeapon->TryLoadClass<AWeapon>();

	if (!WeaponClass)
	{
		EGLOG(Error, TEXT("Class Failed"));
		return;
	}

	Weapon = World->SpawnActor<AWeapon>(WeaponClass, SpawnParameters);
	if (!Weapon.IsValid())
	{
		EGLOG(Error, TEXT("Casting after creating is Failed"));
		return;
	}

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));


}

//void AEnemyCharacter_Gunner::setupPerception()
//{
//	//UAISenseConfig AISenseConfig;
////	FAISenseID
//	//AIPerceptionComponent->ConfigureSense
//
//	//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html
//	//UAISenseConfig_Sight Document
//	//UAISenseConfig_Sight senseConfig_Sight;
////	AiConfigSight->SightRadius = 1500.0f;
////	AiConfigSight->LoseSightRadius = 3100.0f;
////	AiConfigSight->PeripheralVisionAngleDegrees = 90.0f;
////	AiConfigSight->DetectionByAffiliation.bDetectEnemies = false;
////	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
//
////	AIPerceptionComponent->ConfigureSense(*AiConfigSight);
////	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
//
//	
//
//
//}

void AEnemyCharacter_Gunner::Attack()
{

	

	/*
	*	Find Target Form Black Board
	*/

	auto const AIController = Cast<AEnemyAIController_Gunner>(Controller);
	if (!AIController)
	{
		EGLOG(Warning, TEXT("Controller Casting Failed"));
			return;
	}

	FVector TargetLocation;
	bool bResult = AIController->GetTargetPlayerLocation(TargetLocation);
	if (!bResult)
	{
		return;
	}

	//If Weapon can fire = true
	bool bWeaponAvailable = Weapon->Attack(TargetLocation);

	if (bWeaponAvailable)
	{
		//애니메이션 재생
		Anim->PlayFire(StatComponent->GetState());
		//EGLOG(Log, TEXT("Fire"));
	}
	
	
	
}
void AEnemyCharacter_Gunner::Reload()
{
	Anim->PlayReload(StatComponent->GetState());


}
void AEnemyCharacter_Gunner::SetADS()
{
	StatComponent->SetState(EGunnerState::E_ADS);
	Anim->SetIronsights(true);

}
void AEnemyCharacter_Gunner::ReleaseADS()
{
	StatComponent->SetState(EGunnerState::E_Idle);
	Anim->SetIronsights(false);
}

float AEnemyCharacter_Gunner::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatComponent->TakeDamage(FinalDamage);

	//죽었다면 causer가 player인지 검사하고 경험치를 준다
	if (StatComponent->GetHPRatio() <= 0.0f)
	{
		auto player = Cast<AEGPlayerCharacter>(DamageCauser);
		if (player)
		{
			player->GetStatComponent()->GainExp(StatComponent->GetDropExp());
		}
		StatComponent->SetDamageable(false);
	}


	return FinalDamage;
}

void AEnemyCharacter_Gunner::PlaySFXFoot(bool bResult)
{
	if (bResult)
		SFX_Foot_R->Play();
	else
		SFX_Foot_L->Play();
}

