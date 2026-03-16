// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/PlayerAttackComponent.h"
#include <Attack/ComboDataAsset.h>
#include <Player/PlayerCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/WeaponComponent.h>

// Sets default values for this component's properties
UPlayerAttackComponent::UPlayerAttackComponent()
{
}


// Called when the game starts
void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// 攻撃モンタージュ終了時のイベントをバインド
	OnMontageEndDelegate.BindUObject(this, &ThisClass::OnAttackMontageEnded);
}

// 攻撃モンタージュ正常終了時イベント
void UPlayerAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner == nullptr)
		return;

	if (GetCurrentAttackData() == nullptr)
		return;

	// 他モンタージュによる中断
	if (bInterrupted)
	{
		// 攻撃以外のモンタージュによる中断
		if (Owner->IsAttackState() == false)
		{
			// コンボ情報をリセット
			CurrentAttackIndexInCombo = INDEX_NONE;
		}
	}
	// 攻撃モンタージュ正常終了
	else
	{
		// プレイヤー状態を通常に戻す
		Owner->SetPlayerState(EPlayerState::Idle);

		// コンボ情報をリセット
		CurrentAttackIndexInCombo = INDEX_NONE;
	}
}

// 攻撃アクション発生時
void UPlayerAttackComponent::TryAttack(UComboDataAsset* NextComboData)
{
	if (NextComboData == nullptr || NextComboData->ComboAttacks.IsEmpty())
		return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter == nullptr)
		return;

	// 攻撃不可状態であれば抜ける
	if (PlayerCharacter->CanAttackState() == false)
		return;

	// 次の攻撃がコンボの初撃になるか
	const bool bIsFirstAttackInCombo = CheckIsNextAttackFirst(NextComboData);

	// コンボの初撃の場合、Idle状態ではないなら抜ける
	if (PlayerCharacter->GetPlayerState() != EPlayerState::Idle && bIsFirstAttackInCombo)
		return;

	// 次の攻撃のために情報設定
	SetupNextAttack(NextComboData);

	// コンボの初撃の場合、再生中のモンタージュを停止
	if (bIsFirstAttackInCombo)
	{
		if (UAnimInstance* Anim = PlayerCharacter->GetMesh()->GetAnimInstance())
		{
			Anim->Montage_Stop(0.f, Anim->GetCurrentActiveMontage());
		}
	}

	if (UAnimMontage* AttackMontage = NextComboData->ComboAttacks[CurrentAttackIndexInCombo]->AttackMontage)
	{
		// 攻撃モンタージュ再生
		PlayerCharacter->PlayAnimMontage(AttackMontage);

		// 攻撃ステートに移行
		PlayerCharacter->SetPlayerState(EPlayerState::Attack);

		// モンタージュ終了時のイベントを設定
		if (UAnimInstance* AnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, AttackMontage);
		}
	}
}