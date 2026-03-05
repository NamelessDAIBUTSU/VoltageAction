// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "Voltage/VoltageDef.h"
#include "VoltageGaugeWidget.generated.h"

// ゲージ更新デリゲート用構造体
USTRUCT()
struct FGaugeUpdateData
{
	GENERATED_BODY()

public:
	// コンストラクタ
	FGaugeUpdateData() = default;
	FGaugeUpdateData(float CurrentVal, float MaxVal, float ChangedVal)
		: CurrentValue(CurrentVal), MaxValue(MaxVal), ChangedValue(ChangedVal) {
	}
	FGaugeUpdateData(float CurrentVal, float MaxVal, float ChangedVal, EVoltageRank Rank)
		: CurrentValue(CurrentVal), MaxValue(MaxVal), ChangedValue(ChangedVal), VoltageRank(Rank) {
	}

public:
	float CurrentValue = 0.f;
	float MaxValue = 0.f;
	float ChangedValue = 0.f;
	EVoltageRank VoltageRank = EVoltageRank::Rank1;
};

class UHealthComponent;

UCLASS()
class VOLTAGEACTION_API UVoltageGaugeWidget : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	// 初期化
	virtual void NativeConstruct() override;

public:
	// 初期化
	void Initialize(UHealthComponent* HPComp);

private:
	// バインドするボルテージ更新
	void OnUpdateVoltageGauge(const FGaugeUpdateData& UpdateData);
	// ボルテージゲージの更新
	void UpdateVoltageGaugeImpl(const FGaugeUpdateData& UpdateData);

	// イベントのバインド
	void BindEvent(UHealthComponent* HPComp);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* VoltageGauge;

	// 分母テキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DenominatorText;
	// 分子テキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumeratorText;

	// ボルテージランクテキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* VoltageRankText;
};
