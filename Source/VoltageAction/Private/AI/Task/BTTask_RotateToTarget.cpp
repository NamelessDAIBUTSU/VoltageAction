// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_RotateToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Enemy/EnemyBase.h>
#include "AIController.h"

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyBase* Owner = Cast<AEnemyBase>(AIController->GetPawn());
	if (Owner == nullptr)
		return EBTNodeResult::Failed;

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	if(TargetActor == nullptr)
		return EBTNodeResult::Failed;

	// Yaw方向だけプレイヤーに向かせる
	FRotator Rotation = (TargetActor->GetActorLocation() - Owner->GetActorLocation()).Rotation();
	const FRotator& OwnerRotation = Owner->GetActorRotation();
	Rotation.Pitch = OwnerRotation.Pitch;
	Rotation.Roll = OwnerRotation.Roll;
	Owner->SetActorRotation(Rotation);

	return EBTNodeResult::Succeeded;
}
