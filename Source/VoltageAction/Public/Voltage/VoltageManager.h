// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VoltageDef.h"
#include "UI/VoltageGaugeWidget.h"
#include "VoltageParamTable.h"
#include <Attack/AttackDef.h>
#include "VoltageManager.generated.h"

struct FGaugeUpdateData;

// ボルテージ変更時のデリゲート
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoltageChangedDelegate, const FGaugeUpdateData&);
// ボルテージランク最大に達したときのデリゲート
DECLARE_MULTICAST_DELEGATE(FOnVoltageMaxRankDelegate);

UCLASS()
class VOLTAGEACTION_API UVoltageManager : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UVoltageManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override {}

public: /* FTickableGameObject */
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;

public:
	// ボルテージ値 → ボルテージランク変換処理
	EVoltageRank ConvertVoltageToRank(float Voltage);

	// 現在のボルテージ値
	float GetCurrentVoltage() const { return CurrentVoltage; }
	void SetCurrentVoltage(float Voltage) { CurrentVoltage = Voltage; }

	// 最大のボルテージ値
	float GetMaxVoltage() const { return MaxVoltage; }

	// ボルテージの増減処理
	void ChangeVoltage(float ChangedVoltage);

	// 現在のボルテージランクを取得
	EVoltageRank GetCurrentVoltageRank() const { return CurrentRank; }
	void SetCurrentVoltageRank(EVoltageRank Rank) { CurrentRank = Rank; }

	// 現在最高ランクか
	bool IsMaxRank() const { return CurrentRank == EVoltageRank::MaxRank; }

public: /* コールバック */
	// ジャスト回避によるボルテージ増加
	void OnJustDodge();
	// 被ダメージによるボルテージ減少
	void OnTakeDamage(const FAttackData& AttackData);
	// パリィ成功によるボルテージ増加
	void OnParrySuccess();

private:
	// 最高ランクの維持状態の処理
	bool UpdateMaxRankMaintain(float DeltaTime);

	// 毎フレームのボルテージ減少処理
	void UpdateLostVoltage(float DeltaTime);

	// 最大ランクの維持を開始
	void StartMaxRankMaintain();

public: /* デリゲート */
	// ボルテージ変更時のデリゲート
	FOnVoltageChangedDelegate OnVoltageChangedDelegate;
	// ボルテージランク最大に達したときのデリゲート
	FOnVoltageMaxRankDelegate OnVoltageMaxRankDelegate;

private:
	// ボルテージパラメータテーブル
	TObjectPtr<UVoltageParamTable> VoltageParamTable;

	// 現在のボルテージ値
	float CurrentVoltage = 0.f;
	// 最大のボルテージ値
	float MaxVoltage = 100.f;

	// 現在のボルテージランク
	EVoltageRank CurrentRank = EVoltageRank::Rank1;

	// 最高ランクの経過時間
	float ElapsedMaxRankMaintainSec = 0.f;
};
