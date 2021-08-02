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
	void SetTileOpacity(const float NewValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
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
	//Material Instance Dynamic
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UMaterialInstanceDynamic* MID_Tile;

	//Color From Material Instance
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FLinearColor Color_Default;
	//Color When Player On this Block
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor Color_OnPlayer;
	const FName Name_MainColor = "MainColor";
	const FName Name_Opacity = "Opacity";
};

