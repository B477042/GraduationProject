// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerBullet.h"

AGunnerBullet::AGunnerBullet()
{

}

void AGunnerBullet::BeginPlay()
{
}

void AGunnerBullet::BeginDestroy()
{
}

void AGunnerBullet::PostInitializeComponents()
{
}

void AGunnerBullet::initComponents()
{
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HITCOLLISION"));
	
	
	VFX_Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFXTRAIL"));

}
