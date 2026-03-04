// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/HUDCanvasWidget.h"
#include "UI/PlayerHPBarWidget.h"
#include "UI/EnemyHPBarWidget.h"
#include "UI/VoltageGaugeWidget.h"

void UUIManager::Initialize()
{
	
}

void UUIManager::SetHUDCanvasWidget(UHUDCanvasWidget* CanvasWidget)
{
	HUDCanvasWidget = CanvasWidget;
}

void UUIManager::InitializePlayerHPBarWidget(UHealthComponent* HPComp)
{
	if (IsValid(HUDCanvasWidget) && IsValid(HUDCanvasWidget->WBP_PlayerHPBar))
	{
		HUDCanvasWidget->WBP_PlayerHPBar->Initialize(HPComp);
	}
}

void UUIManager::InitializeEnemyHPBarWidget(UHealthComponent* HPComp)
{
	if (IsValid(HUDCanvasWidget) && IsValid(HUDCanvasWidget->WBP_EnemyHPBar))
	{
		HUDCanvasWidget->WBP_EnemyHPBar->Initialize(HPComp);
	}
}

// ボルテージゲージの初期化
void UUIManager::InitializeVoltageGaugeWidget(UHealthComponent* HPComp)
{
	if (IsValid(HUDCanvasWidget) && IsValid(HUDCanvasWidget->WBP_VoltageGauge))
	{
		HUDCanvasWidget->WBP_VoltageGauge->Initialize(HPComp);
	}
}
