// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "PlayerHPBarWidget.generated.h"

USTRUCT()
struct FHPBarUpdateData
{
	GENERATED_BODY()

public:
	float CurrentHP;
	float MaxHP;
	float ChangedValue;
};

UCLASS()
class VOLTAGEACTION_API UPlayerHPBarWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	// イベントのバインド
	void BindEvent(class UHealthComponent* HPComp);

private:
	// HPバーの更新
	void UpdateHPBar(const FHPBarUpdateData& UpdateData);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	// 分母テキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DenominatorText;
	// 分子テキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumeratorText;
};
