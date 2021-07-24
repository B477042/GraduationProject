// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "MiniMapMarkerComponent.h"
#include "Math/Color.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "BaseStruct.generated.h"

UCLASS(Abstract, BlueprintType)
class ESCAPEGAME_API ABaseStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnComponenetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mesh")
		UMiniMapMarkerComponent* MiniMapTileMesh;
	/*UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UMaterialInstanceDynamic* TileMaterial;*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBoxComponent* TileTrigger;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FLinearColor Color_Default;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor Color_OnPlayer;
	const FName Name_MainColor = "MainColor";
};

