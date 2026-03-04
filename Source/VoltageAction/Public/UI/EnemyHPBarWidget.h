// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "EnemyHPBarWidget.generated.h"

class UHealthComponent;
struct FHPBarUpdateData;

UCLASS()
class VOLTAGEACTION_API UEnemyHPBarWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	void Initialize(UHealthComponent* HPComp);

private:
	// イベントのバインド
	void BindEvent(UHealthComponent* HPComp);

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
