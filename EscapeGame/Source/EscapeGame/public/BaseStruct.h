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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mesh")
		UMiniMapMarkerComponent* MiniMapTileMesh;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UMaterialInstanceDynamic* TileMaterial;
	
	
		FLinearColor Color_Default;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor Color_OnPlayer;
	const FName Name_MainColor = "MainColor";
};
