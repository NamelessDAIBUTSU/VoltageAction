// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDef.generated.h"

// 攻撃タイプ
UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Physical UMETA(DisplayName = "Physical"), // 物理攻撃
	Magical UMETA(DisplayName = "Magical"),   // 魔法攻撃
};

// 攻撃距離タイプ
UENUM(BlueprintType)
enum class EAttackRangeType : uint8
{
	Melee UMETA(DisplayName = "Melee"),   // 近接攻撃
	Ranged UMETA(DisplayName = "Ranged"), // 遠距離攻撃
};

// 移動タイプ
UENUM(BlueprintType)
enum class EMoveType : uint8
{
	// 徘徊
	Wander UMETA(DisplayName = "Wander"),
	// 砲台
	Turret UMETA(DisplayName = "Turret"),
};

// 敵のステート
UENUM()
enum class EEnemyState
{
	Idle		UMETA(DisplayName = "通常"),
	Attack		UMETA(DisplayName = "攻撃"),
	Hit			UMETA(DisplayName = "ヒット"),
	Dead		UMETA(DisplayName = "死亡"),
};
