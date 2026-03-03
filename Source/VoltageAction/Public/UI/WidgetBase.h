// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

// ジャスト回避デリゲート
DECLARE_MULTICAST_DELEGATE(FOnJustDodgeDelegate);

UCLASS()
class VOLTAGEACTION_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 初期化
	virtual void NativeConstruct() override;

private:
	
};
