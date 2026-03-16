// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/EnemyAttackComponent.h"
#include <Attack/ComboDataAsset.h>
#include <Kismet/GameplayStatics.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/WeaponComponent.h>
#include <Monster/MonsterBase.h>

UEnemyAttackComponent::UEnemyAttackComponent()
{
}

void UEnemyAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// 攻撃終了時のイベントをバインド
	OnMontageEndDelegate.BindUObject(this, &UEnemyAttackComponent::OnAttackMontageEnded);
	// コンボ攻撃終了時のイベントをバインド
	OnComboAttackEndDelegate.BindUObject(this, &UEnemyAttackComponent::OnFinalAttackMontageEnd);
}

// コンボ攻撃の開始
void UEnemyAttackComponent::StartComboAttack(int ComboDataIndex)
{
	if (ComboDataList.IsValidIndex(ComboDataIndex) == false)
		return;

	// 再生するコンボデータを取得
	UComboDataAsset* PlayComboData = ComboDataList[ComboDataIndex];
	if (PlayComboData == nullptr)
		return;

	// 現在のコンボデータを設定
	CurrentComboData = PlayComboData;
	CurrentAttackIndexInCombo = INDEX_NONE;

	// 攻撃を開始
	TryAttack(CurrentComboData.Get());
}

// 攻撃を試す
void UEnemyAttackComponent::TryAttack(UComboDataAsset* NextComboData)
{
	if (NextComboData == nullptr || NextComboData->ComboAttacks.IsEmpty())
		return;

	AMonsterBase* Enemy = Cast<AMonsterBase>(GetOwner());
	if (Enemy == nullptr)
		return;

	// 次の攻撃がコンボの初撃になるか
	const bool bIsFirstAttackInCombo = CheckIsNextAttackFirst(NextComboData);

	// 次の攻撃のために情報設定
	SetupNextAttack(NextComboData);

	if (UAnimMontage* AttackMontage = NextComboData->ComboAttacks[CurrentAttackIndexInCombo]->AttackMontage)
	{
		// 攻撃モンタージュ再生
		Enemy->PlayAnimMontage(AttackMontage);

		// 攻撃ステートに移行
		Enemy->SetEnemyState(EEnemyState::Attack);

		// イベント関連
		if (UAnimInstance* AnimInstance = Enemy->GetMesh()->GetAnimInstance())
		{
			// モンタージュ終了時のイベントをバインド
			AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, AttackMontage);

			// コンボ内の最終攻撃の場合、最終攻撃終了時のイベントをバインド
			if (IsFinalAttackInCurrentCombo())
			{
				AnimInstance->Montage_SetEndDelegate(OnComboAttackEndDelegate, AttackMontage);
			}
		}
	}
}

// 攻撃モンタージュ終了時のコールバック
void UEnemyAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AMonsterBase* Enemy = Cast<AMonsterBase>(GetOwner());
	if (Enemy == nullptr)
		return;

	// スタンなど外因による中断なら、コンボ情報をリセット
	if (bInterrupted)
	{
		// コンボ情報をリセット
		CurrentAttackIndexInCombo = INDEX_NONE;
	}
	else
	{
		// 次の攻撃がある場合、続けて再生する
		TryAttack(CurrentComboData.Get());
	}
}

// 最終攻撃モンタージュ終了時のコールバック
void UEnemyAttackComponent::OnFinalAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	// コンボ情報をリセット
	CurrentAttackIndexInCombo = INDEX_NONE;
}