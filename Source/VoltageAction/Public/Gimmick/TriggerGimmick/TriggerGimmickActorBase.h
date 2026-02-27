// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/GimmickActorBase.h"
#include "TriggerGimmickActorBase.generated.h"

class AReactionGimmickActorBase;

/**
 * 
 */
UCLASS(Abstract)
class VOLTAGEACTION_API ATriggerGimmickActorBase : public AGimmickActorBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditInstanceOnly)
	TArray<AReactionGimmickActorBase*> TargetGimmicksInstance;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<TWeakObjectPtr<AReactionGimmickActorBase>> TargetGimmicks;

};
