// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room/Tile/TileBase.h"
#include "WallTile.generated.h"

UCLASS()
class VOLTAGEACTION_API AWallTile : public ATileBase
{
	GENERATED_BODY()
	
public:	
	AWallTile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
