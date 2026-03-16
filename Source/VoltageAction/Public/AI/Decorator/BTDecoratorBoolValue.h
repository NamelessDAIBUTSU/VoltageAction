// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTDecoratorBoolValue.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API UBTDecoratorBoolValue : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecoratorBoolValue();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BoolKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool Value;
};
