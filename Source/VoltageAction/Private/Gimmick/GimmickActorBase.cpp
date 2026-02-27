// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/GimmickActorBase.h"

// Sets default values
AGimmickActorBase::AGimmickActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AGimmickActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGimmickActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

