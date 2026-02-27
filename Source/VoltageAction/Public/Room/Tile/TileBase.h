// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room/RoomDef.h"
#include <Components/BoxComponent.h>
#include "TileBase.generated.h"

UCLASS()
class VOLTAGEACTION_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

public:
	// マテリアルの設定
	void SetTileMaterial(UMaterialInterface* Material);

private:
	// メッシュからコリジョンを設定
	void SetupCollisionFromMesh();

protected:
	// 壁タイルのメッシュコンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	// 当たり判定用のコリジョンコンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComp;
};
