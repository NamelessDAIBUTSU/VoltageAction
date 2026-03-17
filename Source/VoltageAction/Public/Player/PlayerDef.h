// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerDef.generated.h"

// プレイヤーのステート
UENUM()
enum class EPlayerState
{
	Idle		UMETA(DisplayName = "通常"),

	PreParry	UMETA(DisplayName = "パリィ発動前"),
	Parring		UMETA(DisplayName = "パリィ中"),
	Parry_End	UMETA(DisplayName = "パリィ終了"),
	PostParry	UMETA(DisplayName = "パリィ発動後"),

	Attack		UMETA(DisplayName = "攻撃"),
	PostAttack	UMETA(DisplayName = "攻撃後"),

	Hit			UMETA(DisplayName = "ヒット"),
	Dodge		UMETA(DisplayName = "回避"),
	Dead		UMETA(DisplayName = "死亡"),
};