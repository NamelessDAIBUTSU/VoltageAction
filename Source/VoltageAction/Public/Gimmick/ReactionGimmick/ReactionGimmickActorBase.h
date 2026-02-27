// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/GimmickActorBase.h"
#include "ReactionGimmickActorBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class VOLTAGEACTION_API AReactionGimmickActorBase : public AGimmickActorBase
{
	GENERATED_BODY()
	
public:
	AReactionGimmickActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// シーケンサーからギミック軌道するためのコールバック
	UFUNCTION(BluePrintCallable)
	void OnSequenceActivate();

public:
	// ギミック起動
	virtual void ActivateGimmick() {};
	// ギミック停止
	virtual void DeactivateGimmick() {};
};
