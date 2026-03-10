// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/AttackComponent.h"
#include <Interface/AttackReceiver.h>
#include <Attack/ComboDataAsset.h>
#include <Player/PlayerCharacter.h>
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 攻撃モンタージュ終了時イベントのバインド
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		if (UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance())
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackMontageEnded);
		}
	}
}

// 攻撃ヒット時
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
	AttackData.DamagedActor = DamagedActor;
	AttackData.Damage = CurrentAttackData->DamageMultiplier;
	AttackData.Knockback = 0.f;

	// 受信のみのアクターが存在するかもしれないため、インターフェースで攻撃受信を行う
	if (IAttackReceiver* AttackReceiver = Cast<IAttackReceiver>(DamagedActor))
	{
		// 攻撃を受ける側で攻撃受信し、成否結果を取得
		EAttackResult Result = AttackReceiver->ReceiveAttack(AttackData);

		// 攻撃イベント実行
		ExecAttack(Result, AttackData);
	}
}

// 攻撃アクション発生時
void UAttackComponent::TryAttack(UComboDataAsset* AttackData)
{
	if (AttackData == nullptr || AttackData->ComboAttacks.IsEmpty())
		return;

	// #TODO : 自身の状態によって攻撃が可能ではない場合、ここではじく
	{

	}

	// コンボデータが継続ではない場合、現在のコンボデータをリセットする
	if (GetCurrentComboData() != AttackData)
	{
		SetCurrentComboData(AttackData);
	}

	// コンボ継続かどうか
	bool bIsComboAttack = false;

	// コンボ攻撃可能な場合、コンボ継続
	if (bCanCombo && IsFinalAttackInCurrentCombo() == false)
	{
		CurrentComboIndex++;

		bIsComboAttack = true;
	}
	// コンボの最初に戻る
	else
	{
		CurrentComboIndex = 0;
	}

	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		// コンボ継続ではない場合、現在のモンタージュを停止
		if (bIsComboAttack == false)
		{
			if (UAnimInstance* Anim = Owner->GetMesh()->GetAnimInstance())
			{
				Anim->Montage_Stop(0.f, Anim->GetCurrentActiveMontage());
			}
		}

		// 攻撃モンタージュを再生
		UAnimMontage* AttackMontage = AttackData->ComboAttacks[CurrentComboIndex]->AttackMontage;
		if (IsValid(AttackMontage))
		{
			Owner->PlayAnimMontage(AttackMontage);

			bIsAttacking = true;
		}
	}
}

// 現在のコンボデータの設定
void UAttackComponent::SetCurrentComboData(UComboDataAsset* ComboData)
{
	CurrentComboData = ComboData;
	CurrentComboIndex = 0;
	bCanCombo = false;
}

// 現在の攻撃データを取得
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

// 攻撃モンタージュ終了時イベント
// #MEMO : モンタージュが中断ではなく、正常に終了したときのみ処理
void UAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner == nullptr)
		return;

	// 攻撃中ではない場合イベントを発火しない
	if (bIsAttacking == false)
		return;

	// 攻撃コンポーネント取得
	if (GetCurrentAttackData() == nullptr)
		return;

	// モンタージュの連続再生による中断であれば、リセットしない
	if (bInterrupted)
		return;


	UE_LOG(LogTemp, Log, TEXT("Montage End!!"), CurrentComboIndex);

	CurrentComboIndex = 0;

	// 攻撃中フラグをリセット
	bIsAttacking = false;

	// コンボ継続フラグをリセット
	SetCanCombo(false);
}

// 現在コンボの最終攻撃か
bool UAttackComponent::IsFinalAttackInCurrentCombo()
{
	if (IsAttacking() == false)
		return false;
	if (GetCurrentComboData() == nullptr)
		return false;

	return CurrentComboIndex == GetCurrentComboData()->ComboAttacks.Num() - 1;
}
