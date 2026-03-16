// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StartComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API UBTTask_StartComboAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	// コンボ攻撃終了時にSucceededを返すためのコールバック
	UFUNCTION()
	void OnComboAttackEnd(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> CachedBTComp = nullptr;
};
