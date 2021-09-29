// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "StatComponent_Enemy.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PaperSpriteComponent.h"
#include "EnemyCharacter.generated.h"


DECLARE_DELEGATE_OneParam(FOnTakeDamaged, AActor*);


UCLASS()
class ESCAPEGAME_API AEnemyCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	//Save Game 단계에서Enemy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
	UFUNCTION(BlueprintCallable)
	virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	//Load Game 단계에서 Enemmy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
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

	//Pure Virtual Discard 
	//virtual void Attack() PURE_VIRTUAL(AEnemyCharacter::Attack,);

	virtual void Attack() {}

	//Execute when Take Damage. 
	//Bind to Controller.
	//Execute : Check BB value TargetActor. if nullptr point that actor
	FOnTakeDamaged OnTakeDamaged;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* HPBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar*HPBar;
	/*미니맵에 표시되는 Marker용 */
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "MiniMap", meta = (AllowPrivateAccess = true))
	class UMiniMapMarkerComponent* MiniMapMarkerComponent;
	/*
	https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAIPerceptionComponent/index.html
	자손 클래스에서 값 처리를 시킬 것
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

};
