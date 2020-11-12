// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EGGameState.h"
#include "EGSaveGame.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Stat = CreateDefaultSubobject<UStatComponent_Enemy>(TEXT("STAT"));
	//if(Stat==nullptr)EGLOG(Warning,TEXT("Enemy's Stat is null"));
	
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
	
	//Add this Object to GameState.
	auto GameState = Cast<AEGGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		
		GameState->A_Enemies.Add(this);
	}
	
	
}

void AEnemyCharacter::BeginDestroy()
{
	Super::BeginDestroy();


}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}



float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

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
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEnemyCharacter::Turn);
	EGLOG(Warning, TEXT("Turn Synced"));
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
		EGLOG(Error, TEXT("%s Can't find Data"), *GetName());
		return;
	}

	SetActorLocationAndRotation(LoadData->Location, LoadData->Rotation);




}

