// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Service/UpdateTargetActorService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"

void UUpdateTargetActorService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* EnemyController = OwnerComp.GetAIOwner();
	if (EnemyController == nullptr)
		return;

	UBlackboardComponent* BBComp = EnemyController->GetBlackboardComponent();
	if (BBComp)
	{
		BBComp->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(EnemyController->GetWorld(), 0));
	}
}
