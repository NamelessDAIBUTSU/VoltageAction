// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attack/AttackDef.h"
#include "AttackReceiver.generated.h"

// 攻撃を受信するためのインターフェース
// #MEMO : 受信だけするアクターが存在するかもしれないため用意
UINTERFACE(MinimalAPI)
class UAttackReceiver : public UInterface
{
	GENERATED_BODY()
};

class VOLTAGEACTION_API IAttackReceiver
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EAttackResult ReceiveAttack(const FAttackData& AttackData) = 0;

};
