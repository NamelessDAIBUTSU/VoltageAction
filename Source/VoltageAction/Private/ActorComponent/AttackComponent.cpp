// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/AttackComponent.h"
#include <Attack/ComboDataAsset.h>
#include <Player/PlayerCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/WeaponComponent.h>

UAttackComponent::UAttackComponent()
{
}


void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

// 攻撃処理
// #MEMO : 攻撃用コリジョンのオーバーラップ時に呼ぶ
void UAttackComponent::HandleAttackHit(AActor* DamagedActor)
{
	if (DamagedActor == nullptr)
		return;

	AActor* AttackerActor = GetOwner();
	if (AttackerActor == nullptr)
		return;

	// 現在の攻撃データを取得
	UAttackDataAsset* CurrentAttackData = GetCurrentAttackData();
	if (CurrentAttackData == nullptr)
		return;

	// 送信する攻撃情報を作成
	FAttackData AttackData;
	{
		AttackData.DamagedActor = DamagedActor;
		// 敵とプレイヤーの処理統一のため、ダメージは専用のインターフェースから取得
		if (IDamageGetter* DamageGetter = Cast<IDamageGetter>(AttackerActor))
		{
			AttackData.Damage = DamageGetter->GetFinalDamage();
		}
	}

	// 受ける側の戦闘仲介コンポーネントを取得
	if (UCombatComponent* CombatComp = DamagedActor->FindComponentByClass<UCombatComponent>())
	{
		// 攻撃を受信し、成否結果を取得
		EAttackResult Result = CombatComp->ReceiveAttack(AttackData);

		// 攻撃イベント実行
		ExecAttack(Result, AttackData);
	}
}

// 攻撃イベント実行
void UAttackComponent::ExecAttack(EAttackResult AttackResult, const FAttackData& AttackData)
{
	AActor* AttackerActor = GetOwner();
	if (AttackerActor == nullptr)
		return;

	switch (AttackResult)
	{
		// ヒット：ダメージイベントを発火
	case EAttackResult::Hit:
	{
		UGameplayStatics::ApplyDamage(AttackData.DamagedActor.Get(), AttackData.Damage, AttackerActor->GetInstigatorController(), AttackerActor, UDamageType::StaticClass());
		break;
	}
	// ガード（された）：
	case EAttackResult::Guard:
		break;
		// パリィ（された）：
	case EAttackResult::Parry:
		break;
		// ジャスト回避（された）：
	case EAttackResult::JustDodge:
		break;
	default:
		break;
	}
}

// 現在のコンボデータ
UComboDataAsset* UAttackComponent::GetCurrentComboData() const 
{
	return CurrentComboData.Get(); 
}
void UAttackComponent::SetCurrentAttackData(UComboDataAsset* NewComboData) 
{
	CurrentComboData = NewComboData; 
}


// 現在のコンボ攻撃データ
UAttackDataAsset* UAttackComponent::GetCurrentAttackData() const
{
	if (CurrentComboData.IsValid() == false)
		return nullptr;

	if (CurrentComboData->ComboAttacks.IsValidIndex(CurrentAttackIndexInCombo) == false)
		return nullptr;

	return CurrentComboData->ComboAttacks[CurrentAttackIndexInCombo];
}

// 現在コンボデータ内の最終攻撃か
bool UAttackComponent::IsFinalAttackInCurrentCombo()
{
	if (GetCurrentComboData() == nullptr)
		return false;

	return CurrentAttackIndexInCombo == GetCurrentComboData()->ComboAttacks.Num() - 1;
}

// 次回攻撃がコンボ攻撃の初撃か
bool UAttackComponent::CheckIsNextAttackFirst(UComboDataAsset* NextComboData)
{
	// コンボデータが変更 or 現在が最終攻撃だった場合、次回攻撃が初撃
	return CurrentComboData != NextComboData || IsFinalAttackInCurrentCombo();
}

// 次の攻撃のために情報を設定
void UAttackComponent::SetupNextAttack(UComboDataAsset* NextComboData)
{
	if (CheckIsNextAttackFirst(NextComboData) == false)
	{
		CurrentAttackIndexInCombo++;
	}
	// 別コンボデータの場合、コンボ情報をリセット
	// #MEMO : 同じコンボでも一周したら上書きされるけど問題なし
	else
	{
		CurrentComboData = NextComboData;
		CurrentAttackIndexInCombo = 0;
	}
}
