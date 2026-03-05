// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VoltageDef.h"
#include "VoltageParamTable.generated.h"

// ボルテージランク毎のパラメータ
USTRUCT(BlueprintType)
struct FVoltageRankParam
{
	GENERATED_BODY()

public:
	// このランクに上がるまでに必要なボルテージ量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	float MaxVoltageInRank;

	// 1秒で減少する値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	float DecreaseVoltagePerSec;
};

// ボルテージパラメータテーブル
UCLASS()
class VOLTAGEACTION_API UVoltageParamTable : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 被ダメージによるボルテージ減少量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	float TakeDamageLostVoltage;

	// ジャスト回避によるボルテージ増加量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	float JustDodgeGainVoltage;

	// ボルテージランク毎のパラメータ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	TMap<EVoltageRank, FVoltageRankParam> VoltageRankParams;

	// 最高ランクの維持時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voltage")
	float MaxRankMaintainSec;
};
