// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackReceiver.generated.h"

// 受信した攻撃データ
USTRUCT()
struct FAttackData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Damage = 0.f;

	UPROPERTY()
	float Knockback = 0.f;

	// 攻撃をしてきたキャラクター
	UPROPERTY()
	TWeakObjectPtr<AActor> Instigator = nullptr;
};

// 攻撃結果
UENUM()
enum class EAttackResult : uint8
{
	Hit			UMETA(DisplayName = "ヒット"),
	Guard		UMETA(DisplayName = "ガード"),
	Parry		UMETA(DisplayName = "パリィ"),
	JustDodge	UMETA(DisplayName = "ジャスト回避"),
	None		UMETA(DisplayName = "エラー値")
};

// 攻撃を受信するためのインターフェース
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
