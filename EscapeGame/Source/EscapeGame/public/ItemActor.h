// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"

#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class ESCAPEGAME_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Character에게 주워졌다
	virtual void BePickedUp(ACharacter* OtherActor);
	virtual void PostInitializeComponents()override;
	//자식들에서 tag를 반드시 정의해줘야 된다. 
	 virtual  FName GetTag()PURE_VIRTUAL(AItemActor::GetTag,return TEXT("Default") ;);
	//Use This Item
	virtual void UseMe(ACharacter* UserActor) PURE_VIRTUAL(AItemActor::UseMe, ;);
protected:
	/*UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
*/

	


protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UParticleSystemComponent* Effect;
	/*UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UBoxComponent* BoxCollision;*/
	//이 아이템을 가지고 있는 엑터
	UPROPERTY(VisibleAnywhere)
		ACharacter* OwnerActor;

	/*UPROPERTY(VisibleAnywhere)*/
		

};
