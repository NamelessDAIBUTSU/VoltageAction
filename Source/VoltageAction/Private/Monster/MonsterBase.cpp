// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


