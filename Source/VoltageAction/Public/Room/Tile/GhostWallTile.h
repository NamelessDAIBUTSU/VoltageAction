// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room/Tile/WallTile.h"
#include "GhostWallTile.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AGhostWallTile : public AWallTile
{
	GENERATED_BODY()
	
public:
	AGhostWallTile();

protected:
	virtual void BeginPlay() override;
};
