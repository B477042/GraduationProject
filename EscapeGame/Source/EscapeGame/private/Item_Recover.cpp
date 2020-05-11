// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Recover.h"
#include "EGPlayerCharacter.h"

const FName AItem_Recover::Tag = TEXT("Recover");

AItem_Recover::AItem_Recover()
{
	amount_Recovery = 40;
	loadAsset();
	//Tag = TEXT("Recover");
}

void AItem_Recover::BePickedUp(ACharacter * OtherActor)
{
	Super::BePickedUp(OtherActor);


}

void AItem_Recover::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Body->OnComponentBeginOverlap.AddDynamic(this, &AItem_Recover::OnPlayerOverlap);

	//EGLOG(Warning, TEXT("I am Item. my tag is :%s"),*Tag.ToString());
	//Body->collision
}

void AItem_Recover::UseMe(ACharacter*UserActor)
{
	EGLOG(Warning, TEXT("Use Called"));
	auto player = Cast<AEGPlayerCharacter>(UserActor);
	if (!player)
	{
		EGLOG(Warning, TEXT("Not Player Actor "));
		return;
	}
	player->HealHP(amount_Recovery);
}

FName AItem_Recover::GetTag()
{
	return Tag;
}

void AItem_Recover::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//겹친 player 캐스팅
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!player)
	{
		EGLOG(Warning, TEXT("Not Player Actor "));
		return;
	}
	//게임에서 표시되지 않고 overlap이벤트도 꺼준다
	Body->SetCollisionProfileName(FName("No collision"));
	SetActorHiddenInGame(true);
	Body->SetGenerateOverlapEvents(false);

	//회복 아이템은 한번에 1개에서 3개 획득
	int amount = FMath::RandRange(1.0f, 4.0f);

	if (player->GetInventory()->AddItem(this,amount))
	{
		EGLOG(Warning, TEXT("Succeess. Add : %d"),amount);
	}
	


	//여기서 아이템을 player에게 넘겨준다


}

void AItem_Recover::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("StaticMesh'/Game/MyFolder/Download_Object/Sci-fi_battery.Sci-fi_battery'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(  SM_BODY.Object);
		Body->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
		Body->SetWorldRotation(FRotator(0.0f, 0.0f, 90.0f));
		Body->SetCollisionProfileName(FName("OnTrapTrigger"));
		//Body->bGenerateOverlapEvents = true;

	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>U_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Healing.P_Healing'"));
	if (U_EFFECT.Succeeded())
	{
		Effect->SetTemplate(U_EFFECT.Object);
		Effect->bAutoActivate = false;
	}

	
	
}
