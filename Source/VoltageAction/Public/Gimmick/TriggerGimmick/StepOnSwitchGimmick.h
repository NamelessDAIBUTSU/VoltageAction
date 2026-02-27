// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/TriggerGimmick/TriggerGimmickActorBase.h"
#include <Components/BoxComponent.h>
#include "StepOnSwitchGimmick.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AStepOnSwitchGimmick : public ATriggerGimmickActorBase
{
	GENERATED_BODY()
	
public:
	AStepOnSwitchGimmick();

protected:
	virtual void BeginPlay() override;

public:
	// Overlapイベント
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// メッシュコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwitchMesh")
	TObjectPtr<UStaticMeshComponent> SwitchMesh;

	// 当たり判定コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwitchCollision")
	TObjectPtr<UBoxComponent> SwitchCollision;
};
