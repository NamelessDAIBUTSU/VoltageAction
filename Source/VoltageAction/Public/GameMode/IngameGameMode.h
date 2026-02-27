// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IngameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AIngameGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AIngameGameMode();

public:
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	// 部屋マネージャー
	TObjectPtr<class URoomManager> RoomManager;
};
