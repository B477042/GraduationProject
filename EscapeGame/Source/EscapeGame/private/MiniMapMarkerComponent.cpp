// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapMarkerComponent.h"

UMiniMapMarkerComponent::UMiniMapMarkerComponent()
{
	CastShadow = false;
	SetComponentTickEnabled(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if(SM_Plane.Succeeded())
	{
		SetStaticMesh(SM_Plane.Object);
		//Static Mesh Parameter Settings
		auto Mesh = GetStaticMesh();
		
		
		
	}

	SetMobility(EComponentMobility::Movable);
	
}