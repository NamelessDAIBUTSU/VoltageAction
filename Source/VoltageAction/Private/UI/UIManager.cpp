// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/HUDCanvasWidget.h"
#include "UI/PlayerHPBarWidget.h"

void UUIManager::Initialize()
{
	
}

void UUIManager::SetHUDCanvasWidget(UHUDCanvasWidget* CanvasWidget)
{
	HUDCanvasWidget = CanvasWidget;
}

void UUIManager::InitializeHPBarWidget(UHealthComponent* HPComp)
{
	if (IsValid(HUDCanvasWidget) && IsValid(HUDCanvasWidget->WBP_PlayerHPBar))
	{
		HUDCanvasWidget->WBP_PlayerHPBar->Initialize(HPComp);
	}
}
