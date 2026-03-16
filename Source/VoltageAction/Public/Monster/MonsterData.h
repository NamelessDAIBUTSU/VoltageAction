// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterData.generated.h"

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

UCLASS()
class VOLTAGEACTION_API UMonsterData : public UDataAsset
{
	GENERATED_BODY()

public:
	// モンスター名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FName Name;
	// コスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	int32 Cost;
	// 売却額
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	int32 SellPrice;

	// 体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 HP;
	// 移動速度(cm/s)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float MoveSpeed;
	// 移動タイプ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	EMoveType MoveType;

	// 攻撃力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	int32 AttackPower;
	// 攻撃クールタイム
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float AttackCooldown;
	// 攻撃タイプ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	EAttackType AttackType;
	// 攻撃距離タイプ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	EAttackRangeType AttackRangeType;

	// 物理防御力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defense")
	int32 PhysicalDefense;
	// 魔法防御力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defense")
	int32 MagicDefense;

	// 収穫に必要な育て回数
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grow")
	int32 NeedGrowCount;
};

