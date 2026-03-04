// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/DodgeComponent.h"
#include <Player/PlayerCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Voltage/VoltageManager.h>

// Sets default values for this component's properties
UDodgeComponent::UDodgeComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDodgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// 回避行動
void UDodgeComponent::Dodge()
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner == nullptr)
		return;

	if (UCharacterMovementComponent* MoveComp = Owner->GetCharacterMovement())
	{
		if (MoveComp->IsFalling())
			return;
	}

	// すでに回避モーション中なら何もしない
	if (IsDodging())
		return;

	// 回避モンタージュの再生
	if (UAnimInstance* AnimInst = Owner->GetMesh()->GetAnimInstance())
	{
		if (IsValid(DodgeMontage))
		{
			AnimInst->Montage_Play(DodgeMontage);
		}
	}
}

// ジャスト回避を通知
void UDodgeComponent::ApplyJustDodge()
{
	// ジャスト回避成功イベントを発火
	OnJustDodgeDelegate.Broadcast();

	// ジャスト回避判定を終了
	JustDodgeEndTime = 0.f;
}

// 回避中か
bool UDodgeComponent::IsDodging()
{
	APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner == nullptr)
		return false;

	if (UAnimInstance* AnimInst = Owner->GetMesh()->GetAnimInstance())
	{
		return AnimInst->Montage_IsPlaying(DodgeMontage);
	}

	return false;
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
