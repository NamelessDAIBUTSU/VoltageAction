// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

class UHUDCanvasWidget;
class UHealthComponent;

UCLASS()
class VOLTAGEACTION_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();

	void SetHUDCanvasWidget(UHUDCanvasWidget* CanvasWidget);

	// HPバーの初期化
	void InitializePlayerHPBarWidget(UHealthComponent* HPComp);
	// 敵HPバーの初期化
	void InitializeEnemyHPBarWidget(UHealthComponent* HPComp);

private:
	// HUDキャンバス
	UPROPERTY()
	TObjectPtr<UHUDCanvasWidget> HUDCanvasWidget = nullptr;
};
