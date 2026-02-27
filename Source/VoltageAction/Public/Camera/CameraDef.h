// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// カメラチャンネル
UENUM(BlueprintType)
enum class ECameraChannel : uint8
{
    God			UMETA(DisplayName = "神カメラ"),
    Room1       UMETA(DisplayName = "部屋1"),
	Room2       UMETA(DisplayName = "部屋2"),
	Room3       UMETA(DisplayName = "部屋3"),
	Room4       UMETA(DisplayName = "部屋4"),
	FinalRoom   UMETA(DisplayName = "最終部屋"),
};