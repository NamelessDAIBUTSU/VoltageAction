// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_SetRandomComboIndex.h"
#include <Monster/MonsterBase.h>
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <ActorComponent/EnemyAttackComponent.h>

EBTNodeResult::Type UBTTask_SetRandomComboIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;
	AMonsterBase* Owner = Cast<AMonsterBase>(AIController->GetPawn());
	if (Owner == nullptr)
		return EBTNodeResult::Failed;
	UEnemyAttackComponent* EAttackComp = Owner->FindComponentByClass<UEnemyAttackComponent>();
	if (EAttackComp == nullptr)
		return EBTNodeResult::Failed;
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	// コンボデータインデックスのレンジを取得
	const int ComboDataListSize = EAttackComp->GetComboDataListSize();
	if (ComboDataListSize == 0)
		return EBTNodeResult::Failed;

	// ランダムにインデックスを取得
	const float RandNum = FMath::FRandRange(0.f, ComboDataListSize);

	// インデックスをBBに設定
	BBComp->SetValueAsInt("ComboDataIndex", RandNum);

	return EBTNodeResult::Succeeded;
}