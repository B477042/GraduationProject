// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacterBase.h"
#include "EnemyCharacter.generated.h"


class UWidgetComponent;
class UProgressBar;
class UAIPerceptionStimuliSourceComponent;
DECLARE_DELEGATE_OneParam(FOnTakeDamaged, AActor*);


UCLASS()
class ESCAPEGAME_API AEnemyCharacter : public AGameCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	
	UFUNCTION(BlueprintCallable)
	virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	
	UFUNCTION(BlueprintCallable)
	virtual	void LoadGame(const class UEGSaveGame* LoadInstance);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	UFUNCTION(BlueprintCallable)
		void Dead();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Turn(float NewAxisValue);

	
	virtual void Attack() PURE_VIRTUAL(AEnemyCharacter::Attack,);

	//virtual void Attack() {}

	//Execute when Take Damage. 
	//Bind to Controller.
	//Execute : Check BB value TargetActor. if nullptr point that actor
	FOnTakeDamaged OnTakeDamaged;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HPBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProgressBar* HPBar;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "MiniMap", meta = (AllowPrivateAccess = true))
	class UMiniMapMarkerComponent* MiniMapMarkerComponent;
	/*
	https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAIPerceptionComponent/index.html
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

};
