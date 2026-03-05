// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EVoltageRank : uint8
{
	Rank1      UMETA(DisplayName = "Rank1"),
	Rank2      UMETA(DisplayName = "Rank2"),
	Rank3      UMETA(DisplayName = "Rank3"),
	MaxRank    UMETA(DisplayName = "MaxRank"),

	Max,
};

ENUM_RANGE_BY_COUNT(EVoltageRank, EVoltageRank::Max);