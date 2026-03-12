// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/AttackComponent.h"
#include <Interface/AttackReceiver.h>
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
	
	OnMontageEndDelegate.BindUObject(this, &ThisClass::OnAttackMontageEnded);
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

// 現在のコンボデータ
UComboDataAsset* UAttackComponent::GetCurrentComboData() const 
{
	return CurrentComboData.Get(); 
}
void UAttackComponent::SetCurrentAttackData(UComboDataAsset* NewComboData) 
{
	CurrentComboData = NewComboData; 
}

// 攻撃アクション発生時
void UAttackComponent::TryAttack(UComboDataAsset* NextComboData)
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
	bool bIsFirstAttackInCombo = CurrentComboData != NextComboData || IsFinalAttackInCurrentCombo();

	// コンボの初撃の場合、Idle状態ではないなら抜ける
	if (PlayerCharacter->GetPlayerState() != EPlayerState::Idle && bIsFirstAttackInCombo)
		return;

	// コンボ継続
	if (bIsFirstAttackInCombo == false)
	{
		CurrentComboIndex++;
	}
	// 別コンボデータの場合、コンボ情報をリセット
	// #MEMO : 同じコンボでも一周したら上書きされるけど問題なし
	else
	{
		CurrentComboData = NextComboData;
		CurrentComboIndex = 0;
	}

	// コンボの初撃の場合、再生中のモンタージュを停止
	if (bIsFirstAttackInCombo)
	{
		if (UAnimInstance* Anim = PlayerCharacter->GetMesh()->GetAnimInstance())
		{
			Anim->Montage_Stop(0.f, Anim->GetCurrentActiveMontage());
		}
	}

	if (UAnimMontage* AttackMontage = NextComboData->ComboAttacks[CurrentComboIndex]->AttackMontage)
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

// 現在のコンボ攻撃データ
UAttackDataAsset* UAttackComponent::GetCurrentAttackData() const
{
	if (CurrentComboData.IsValid() == false)
		return nullptr;

	if (CurrentComboData->ComboAttacks.IsValidIndex(CurrentComboIndex) == false)
		return nullptr;

	return CurrentComboData->ComboAttacks[CurrentComboIndex];
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

// 攻撃モンタージュ正常終了時イベント
void UAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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
			CurrentComboIndex = INDEX_NONE;
		}
	}
	// 攻撃モンタージュ正常終了
	else
	{
		// プレイヤー状態を通常に戻す
		Owner->SetPlayerState(EPlayerState::Idle);

		// コンボ情報をリセット
		CurrentComboIndex = INDEX_NONE;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Montage End!! bInterrupted(%hs)"), bInterrupted ? "True" : "False");
}

// 現在コンボの最終攻撃か
bool UAttackComponent::IsFinalAttackInCurrentCombo()
{
	if (GetCurrentComboData() == nullptr)
		return false;

	return CurrentComboIndex == GetCurrentComboData()->ComboAttacks.Num() - 1;
}
