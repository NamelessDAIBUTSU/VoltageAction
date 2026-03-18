// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackDataAsset.generated.h"

/// <summary>
/// 1アニメーションの攻撃に関するデータアセット
/// </summary>
UCLASS()
class VOLTAGEACTION_API UAttackDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 再生する攻撃モンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common")
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;

	// パリィ可能な攻撃か
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	bool bCanParry = false;

	// 獲得できるボルテージ量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float GainVoltage = 0.f;

	// 武器の基礎ダメージへの倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common")
	float DamageMultiplier = 1.f;

	// 基礎耐久値ダメージへの倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float PoiseDamageMultiplier = 1.f;

	// 基礎ブレイクダメージへの倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float BreakDamageMultiplier = 1.f;
};
