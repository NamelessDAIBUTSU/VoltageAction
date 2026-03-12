// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "WarriorMonster.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AWarriorMonster : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	AWarriorMonster();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
