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

	// コンボデータが継続ではない場合、現在のコンボデータをリセットする
	if (GetCurrentComboData() != AttackData)
	{
		SetCurrentComboData(AttackData);
	}

	// コンボ継続かどうか
	bool bIsComboAttack = false;

	// コンボ継続可能 かつ コンボの最終攻撃でない場合は、次の攻撃に進む
	if (bCanNextCombo && CurrentComboIndex < AttackData->ComboAttacks.Num() - 1)
	{
		CurrentComboIndex++;

		bIsComboAttack = true;

		// ログ出力
		UE_LOG(LogTemp, Log, TEXT("Combo Continued! Current Combo Index: %d"), CurrentComboIndex);
	}
	else
	{
		// コンボが開始していない場合は、最初の攻撃から始める
		CurrentComboIndex = 0;
		bCanNextCombo = true;

		UE_LOG(LogTemp, Log, TEXT("Combo Start!!"), CurrentComboIndex);
	}

	// 再生するモンタージュの取得
	UAnimMontage* AttackMontage = AttackData->ComboAttacks[CurrentComboIndex]->AttackMontage;

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
	bCanNextCombo = false;
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
void UAttackComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner == nullptr)
		return;

	// 攻撃コンポーネント取得
	UAttackComponent* AttackComp = Owner->FindComponentByClass<UAttackComponent>();
	if (AttackComp == nullptr || AttackComp->GetCurrentAttackData() == nullptr)
		return;

	// 終了したモンタージュが現在再生中の攻撃モンタージュでない場合、
	// コンボが継続しているため、コンボインデックスをリセットしない
	if (Montage != AttackComp->GetCurrentAttackData()->AttackMontage)
		return;

	UE_LOG(LogTemp, Log, TEXT("Montage End!!"), CurrentComboIndex);
	CurrentComboIndex = 0;

	// 攻撃中フラグをリセット
	bIsAttacking = false;
}