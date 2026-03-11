// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/DodgeComponent.h"
#include <Player/PlayerCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Voltage/VoltageManager.h>

// Sets default values for this component's properties
UDodgeComponent::UDodgeComponent()
{
}

void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	// モンタージュ終了時イベントのバインド
	OnMontageEndDelegate.BindUObject(this, &ThisClass::OnDodgeMontageEnded);
}

// 回避行動
void UDodgeComponent::TryDodge()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter == nullptr)
		return;

	if (PlayerCharacter->CanDodgeState() == false)
		return;

	// 回避モンタージュの再生
	if (IsValid(DodgeMontage))
	{
		PlayerCharacter->PlayAnimMontage(DodgeMontage);

		// 回避状態に設定
		PlayerCharacter->SetPlayerState(EPlayerState::Dodge);

		// モンタージュ終了時のイベントを設定
		if (UAnimInstance* AnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, DodgeMontage);
		}
	}
}

// ジャスト回避成功を通知
void UDodgeComponent::OnJustDodgeSuccess()
{
	// ジャスト回避成功イベントを発火
	OnJustDodgeDelegate.Broadcast();

	// ジャスト回避判定を終了
	JustDodgeEndTime = 0.f;
}

// ジャスト回避判定
bool UDodgeComponent::IsJustDodging()
{
	return GetInvincibleEndTime() >= GetWorld()->GetTimeSeconds();
}

// 無敵状態の開始
void UDodgeComponent::StartInvincible()
{
	// 無敵時間の終了時刻を設定
	JustDodgeEndTime = GetWorld()->GetTimeSeconds() + JustDodgeSec;
}

// 無敵時間終了時刻の取得
float UDodgeComponent::GetInvincibleEndTime() const
{
	return JustDodgeEndTime;
}

// 回避終了時のイベント
void UDodgeComponent::OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner()))
	{
		Owner->SetPlayerState(EPlayerState::Idle);
	}
}
