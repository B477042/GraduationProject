// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include"Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture2D.h"
#include "MiniMapRender.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UMiniMapRender : public USceneCaptureComponent2D
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMiniMapRender();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:
	
	
	

		
};
