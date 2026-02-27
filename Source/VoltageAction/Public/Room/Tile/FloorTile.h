// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room/Tile/TileBase.h"
#include "FloorTile.generated.h"

UCLASS()
class VOLTAGEACTION_API AFloorTile : public ATileBase
{
	GENERATED_BODY()
	
public:	
	AFloorTile();

protected:
	// BPエディタ上で確認できるように、グリッド線のメッシュコンポーネントを配置する関数をOnConstructで作成
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
