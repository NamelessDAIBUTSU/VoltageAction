// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_DamageGetter.generated.h"

// 継承したアクターから受けたダメージを取得するためのインターフェース
UINTERFACE(MinimalAPI)
class UDamageGetter : public UInterface
{
	GENERATED_BODY()
};

class VOLTAGEACTION_API IDamageGetter
{
	GENERATED_BODY()

public:
	virtual float GetFinalDamage() = 0;
};
