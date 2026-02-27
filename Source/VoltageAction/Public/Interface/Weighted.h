// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weighted.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UWeighted : public UInterface
{
	GENERATED_BODY()
};

class IWeighted
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual float GetWeight() const = 0;
};
