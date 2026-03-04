// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "HUDCanvasWidget.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API UHUDCanvasWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	void InitializeWidget();

public:
	// 配置用キャンバス
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> MainCanvas = nullptr;

public: /* 子ウィジェット */
	// プレイヤーHPゲージ
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPlayerHPBarWidget> WBP_PlayerHPBar = nullptr;

	// エネミーHPゲージ
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEnemyHPBarWidget> WBP_EnemyHPBar = nullptr;
};
