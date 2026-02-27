// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableGimmick.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UActivatableGimmick : public UInterface
{
	GENERATED_BODY()
};

class IActivatableGimmick
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void ActivateGimmick(AActor* ExecutedActor) = 0;
};
