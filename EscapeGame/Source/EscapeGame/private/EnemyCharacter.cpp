// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EGGameState.h"
#include "EGSaveGame.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiniMapMarkerComponent.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//마커 초기값 설정
	MiniMapMarkerComponent = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MiniMapMarker"));
	MiniMapMarkerComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Marker(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_Marker_Enemy.MI_Marker_Enemy'"));
	if (MI_Marker.Succeeded())
	{
		MiniMapMarkerComponent->SetMaterial(0, MI_Marker.Object);
	}
	MiniMapMarkerComponent->SetRelativeLocation(FVector(0, 0, POS_Minimap.Z));
	MiniMapMarkerComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	MiniMapMarkerComponent->SetMobility(EComponentMobility::Movable);

	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCharacter"));

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 240.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::World);
	HPBarWidget->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>UI_HUD(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_DisplayHP.UI_DisplayHP_C'"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(300.0f, 50.0f));
		//HPBarWidget->
		//HPBarWidget->
	
	}
	HPBarWidget->SetHiddenInGame(false);
	

//	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	
	//Control 관련 설정
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate.Yaw = 360;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HPBar = Cast<UProgressBar>(HPBarWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("HPBar")));
	if (!HPBar)
	{
		EGLOG(Warning, TEXT(" HPBar Failed"));
		return;
	}
	HPBar->SetPercent(1.0f);

	
	auto AIController = Cast<AEnemyAIController>(GetController());
	if (!AIController)
	{
		EGLOG(Error, TEXT("Controller Casting Error"));
		return;
	}
	
	OnTakeDamaged.BindLambda([this,AIController](AActor* OtherActor)->void {
		auto Retval = AIController->GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetPlayer);
		if (!Retval)
		{
			AIController->GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, OtherActor);
		}
		});
	
	////Add this Object to GameState.
	//auto GameState = Cast<AEGGameState>(GetWorld()->GetGameState());
	//if (GameState)
	//{
	//	
	//	GameState->A_Enemies.Add(this);
	//}
	//
	//
}

void AEnemyCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	if (OnTakeDamaged.IsBound())
	{
		OnTakeDamaged.Unbind();
	}
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}



float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//EGLOG(Error, TEXT("Damage Causer %s"), *DamageCauser->GetName());
	if(OnTakeDamaged.IsBound())
	OnTakeDamaged.Execute(DamageCauser);
	//Stat->TakeDamage(DamageAmount);

	return FinalDamage;
}



// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEnemyCharacter::Turn);
	//EGLOG(Warning, TEXT("Turn Synced"));
}

void AEnemyCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}


void AEnemyCharacter::Dead()
{
	Destroy();
}

void AEnemyCharacter::SaveGame(UEGSaveGame * SaveInstance)
{
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("SaveInstance is nullptr"));
		return;
	}
	//자식 클래스에서 Save Game을 사용할 경우, 이미 등록된 데이터를 불러와서 추가로 편집하는 작업으로 한다.
	FEnemyData SaveData;
	SaveData.Location = GetActorLocation();
	SaveData.Rotation = GetActorRotation();
	
	SaveInstance->D_Enemies.Add(GetName(), SaveData);
	
}

 void AEnemyCharacter::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}

	auto LoadData = LoadInstance->D_Enemies.Find(GetName());
	if (!LoadData)
	{
		EGLOG(Log, TEXT("%s Can't find Data"), *GetName());
		Destroy();
		return;
	}

	SetActorLocationAndRotation(LoadData->Location, LoadData->Rotation);


}

