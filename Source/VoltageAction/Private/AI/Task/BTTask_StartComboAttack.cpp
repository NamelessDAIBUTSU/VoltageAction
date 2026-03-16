// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_StartComboAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Enemy/EnemyBase.h>
#include <Attack/ComboDataAsset.h>
#include <ActorComponent/EnemyAttackComponent.h>

EBTNodeResult::Type UBTTask_StartComboAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;
	AEnemyBase* Owner = Cast<AEnemyBase>(AIController->GetPawn());
	if (Owner == nullptr)
		return EBTNodeResult::Failed;
	USkeletalMeshComponent* Mesh = Owner->GetMesh();
	if (Mesh == nullptr)
		return EBTNodeResult::Failed;
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	if (UEnemyAttackComponent* EAttackComp = Owner->FindComponentByClass<UEnemyAttackComponent>())
	{
		// BBから再生するコンボ攻撃データのインデックスを取得
		int ComboDataIndex = BBComp->GetValueAsInt("ComboDataIndex");

		// コンボ攻撃を開始
		EAttackComp->StartComboAttack(ComboDataIndex);

		// コンボ攻撃終了時にタスクを完了させるイベントをバインド
		EAttackComp->OnComboAttackEndDelegate.AddUObject(this, &ThisClass::OnComboAttackEnd);
	}

	CachedBTComp = &OwnerComp;

	return EBTNodeResult::InProgress;
}

// コンボ攻撃終了時にSucceededを返すためのイベント
void UBTTask_StartComboAttack::OnComboAttackEnd()
{
	if (CachedBTComp.IsValid())
	{
		FinishLatentTask(*CachedBTComp.Get(), EBTNodeResult::Succeeded);
	}
}