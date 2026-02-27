// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"
#include <Components/TimelineComponent.h>
#include "SingleDoorGimmick.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API ASingleDoorGimmick : public AReactionGimmickActorBase
{
	GENERATED_BODY()
	
public:
	ASingleDoorGimmick();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public: /* AReactionGimmickActorBase */
	// ギミック起動
	virtual void ActivateGimmick() override;
	// ギミック停止
	virtual void DeactivateGimmick() override;

public:
	// タイムライン更新処理
	UFUNCTION()
	void OnTimelineUpdate(float Value);

public:
	// ドアのメッシュコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SingleDoorGimmick")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SingleDoorGimmick")
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

private: /* タイムライン用 */
	UPROPERTY()
	TObjectPtr<UTimelineComponent> OpenTimeline;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> OpenCurve;

	FVector ClosedLocation;
	FVector OpenedLocation;
};
