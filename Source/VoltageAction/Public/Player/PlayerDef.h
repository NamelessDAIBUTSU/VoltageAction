// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerDef.generated.h"

UENUM()
enum class EPlayerState
{
	Idle		UMETA(DisplayName = "通常"),
	Parry		UMETA(DisplayName = "パリィ"),
	Parried		UMETA(DisplayName = "パリィ語の入力待機"),
	Attack		UMETA(DisplayName = "攻撃"),
	Attacked	UMETA(DisplayName = "攻撃後の入力待機"),
	Hit			UMETA(DisplayName = "ヒット"),
	Dodge		UMETA(DisplayName = "回避"),
	Dead		UMETA(DisplayName = "死亡"),
};