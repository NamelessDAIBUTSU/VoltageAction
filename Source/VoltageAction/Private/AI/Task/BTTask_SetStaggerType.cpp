// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_SetStaggerType.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetStaggerType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	BBComp->SetValueAsEnum("StaggerType", static_cast<uint8>(NewType));

	return EBTNodeResult::Succeeded;
}
