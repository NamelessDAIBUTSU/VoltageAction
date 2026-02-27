// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerDef.generated.h"

// アストラルに保存する軌道情報
USTRUCT(BlueprintType)
struct FAstralOrbitData
{
	GENERATED_BODY()

public:
	// 前回からの経過時間
	float DeltaSec;
	// 目標トランスフォーム
	FTransform TargetTransform;
};