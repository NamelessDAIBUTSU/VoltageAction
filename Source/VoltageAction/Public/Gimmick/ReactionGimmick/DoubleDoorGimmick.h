// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"
#include "DoubleDoorGimmick.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API ADoubleDoorGimmick : public AReactionGimmickActorBase
{
	GENERATED_BODY()
	
public:
	ADoubleDoorGimmick();

public: /* AReactionGimmickActorBase */
	// ギミック起動
	virtual void ActivateGimmick() override;

public:
	// ドアのメッシュコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoubleDoorGimmick")
	TObjectPtr<UStaticMeshComponent> LeftDoorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoubleDoorGimmick")
	TObjectPtr<UStaticMeshComponent> RightDoorMesh;
};
