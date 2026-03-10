// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackDataAsset.h"
#include "ComboDataAsset.generated.h"

/// <summary>
/// コンボ攻撃に関するデータアセット
/// </summary>
UCLASS()
class VOLTAGEACTION_API UComboDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// コンボ攻撃の各段階の攻撃データ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	TArray<TObjectPtr<UAttackDataAsset>> ComboAttacks;
};
