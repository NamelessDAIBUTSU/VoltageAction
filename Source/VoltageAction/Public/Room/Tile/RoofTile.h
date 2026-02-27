// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room/Tile/TileBase.h"
#include "RoofTile.generated.h"

UCLASS()
class VOLTAGEACTION_API ARoofTile : public ATileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoofTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
