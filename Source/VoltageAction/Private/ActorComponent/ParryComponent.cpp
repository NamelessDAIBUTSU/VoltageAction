// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/ParryComponent.h"
#include "Player/PlayerCharacter.h"

UParryComponent::UParryComponent()
{
}


void UParryComponent::BeginPlay()
{
	Super::BeginPlay();

	// モンタージュ終了時イベントのバインド
	OnMontageEndDelegate.BindUObject(this, &ThisClass::OnParryMontageEnded);
}

// パリィ処理
void UParryComponent::TryParry()
{
	if (IsValid(ParryMontage) == false)
		return;

	// 自身の状態によってパリィが可能ではない場合、ここではじく
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		if (PlayerCharacter->CanParryState() == false)
			return;
	}

	// パリィモンタージュを再生
	if (APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner()))
	{
		Owner->PlayAnimMontage(ParryMontage);

		// プレイヤー状態をパリィ前に設定
		Owner->SetPlayerState(EPlayerState::PreParry);

		// モンタージュ終了時のイベントを設定
		if (UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, ParryMontage);
		}
	}
}

// パリィ成功時の処理
void UParryComponent::OnParrySuccess()
{
	// イベントの発火
	OnParrySuccessDelegate.Broadcast();
}

// パリィ終了時のイベント
void UParryComponent::OnParryMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 中断の場合は、中断側でステート変更が行われているため抜ける
	if (bInterrupted)
		return;

	if (APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner()))
	{
		Owner->SetPlayerState(EPlayerState::Idle);
	}
}

