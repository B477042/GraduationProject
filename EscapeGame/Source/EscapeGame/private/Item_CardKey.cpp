// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_CardKey.h"
#include "EGPlayerCharacter.h"
#include "Engine.h"
const FName AItem_CardKey::Tag = TEXT("CardKey");

AItem_CardKey::AItem_CardKey()
{
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	DetectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	loadAssets();

	DetectCollision->SetupAttachment(RootComponent);
	DetectCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	DetectCollision->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	

}

FName AItem_CardKey::GetTag()
{
	return Tag;
}
//문 여는데 사용되니까 아무것도 안 해도 될거 같다
void AItem_CardKey::UseMe(ACharacter * UserActor)
{
	


}

void AItem_CardKey::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	DetectCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem_CardKey::OnPlayerOverlap);
}

//OtherActor가 OwnerActor가 된다
void AItem_CardKey::BePickedUp(ACharacter * OtherActor)
{
	Super::BePickedUp(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Get Card Key"));

	Effect->Deactivate();
	SetActorHiddenInGame(true);
	Sound->Play();
}

void AItem_CardKey::loadAssets()
{
	//StaticMesh'/Game/StarterBundle/ModularScifiProps/Meshes/SM_AccessCard.SM_AccessCard'
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("StaticMesh'/Game/StarterBundle/ModularScifiProps/Meshes/SM_AccessCard.SM_AccessCard'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(SM_BODY.Object);

		//Body->SetCollisionProfileName(TEXT("OnTrapTrigger"));
		
	}

	//반짝이면서 위치를 나타낼 컴포넌트
	static ConstructorHelpers::FObjectFinder<UParticleSystem>U_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Buff.P_Buff'"));
	if (U_EFFECT.Succeeded())
	{
		Effect->SetTemplate(U_EFFECT.Object);
		Effect->bAutoActivate = true;
		Effect->bAllowRecycling = true;
		Effect->SetupAttachment(Body);

		Effect->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase>SB_SOUND(TEXT("SoundWave'/Game/MyFolder/Sound/PickUpBoxSFX.PickUpBoxSFX'"));
	if (SB_SOUND.Succeeded())
	{
		//SB_SOUND.Object->set;
		Sound->SetSound(SB_SOUND.Object);
		Sound->bAutoActivate = false;
		Sound->SetupAttachment(RootComponent);
		//Sound->SoundWavePlaybackTimes(0);
	}

	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_ATTENUATION(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'"));
	if (SA_ATTENUATION.Succeeded())
	{
		Sound->AttenuationSettings = SA_ATTENUATION.Object;
	}


}

void AItem_CardKey::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (player == nullptr)
	{
		EGLOG(Error, TEXT("Casting Failed"));
		return;
	}
	BePickedUp(player);
	player->GetInventory()->AddItem(this, 1);
	DetectCollision->SetCollisionProfileName(TEXT("NoCollision"));

}
