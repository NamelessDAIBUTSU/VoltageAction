// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include <ActorComponent/StaggerComponent.h>
#include "BTTask_SetStaggerType.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API UBTTask_SetStaggerType : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	EStaggerType NewType;
};
