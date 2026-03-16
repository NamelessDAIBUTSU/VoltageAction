// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "WarriorEnemy.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AWarriorEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AWarriorEnemy();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
