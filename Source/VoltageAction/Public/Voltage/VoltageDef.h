// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 各種アクションによるボルテージ増量
#define JustDodgeVoltage 10.f
#define ParryVoltage 30.f

#define Rank1VoltageThreshold 50.f
#define Rank2VoltageThreshold 100.f
#define Rank3VoltageThreshold 200.f


UENUM()
enum class EVoltageRank : uint8
{
	Rank0      UMETA(DisplayName = "Rank0"),
	Rank1      UMETA(DisplayName = "Rank1"),
	Rank2      UMETA(DisplayName = "Rank2"),
	Rank3      UMETA(DisplayName = "Rank3"),
};