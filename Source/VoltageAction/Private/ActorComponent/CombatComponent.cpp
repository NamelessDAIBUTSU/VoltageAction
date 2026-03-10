// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CombatComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Interface/AttackReceiver.h>
#include <Player/PlayerCharacter.h>
#include <ActorComponent/DodgeComponent.h>
#include <ActorComponent/ParryComponent.h>

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// 攻撃処理
EAttackResult UCombatComponent::ReceiveAttack(const FAttackData& AttackData)
{
	AActor* DamagedOwner = GetOwner();
	if (DamagedOwner == nullptr)
		return EAttackResult::None;

	// 無敵状態なら無効
	if(bIsInvincible)
		return EAttackResult::None;

	// ジャスト回避判定
	if (UDodgeComponent* DodgeComp = DamagedOwner->FindComponentByClass<UDodgeComponent>())
	{
		if (DodgeComp->IsJustDodging())
		{
			// ジャスト回避成功を通知
			DodgeComp->OnJustDodgeSuccess();

			return EAttackResult::JustDodge;
		}
	}

	// パリィ判定
	if (UParryComponent* ParryComp = DamagedOwner->FindComponentByClass<UParryComponent>())
	{
		if (ParryComp->IsParrying())
		{
			// パリィ成功を通知
			ParryComp->OnParrySuccess();

			return EAttackResult::Parry;
		}
	}

	// 攻撃成功
	return EAttackResult::Hit;
}

// 無敵状態の開始
void UCombatComponent::OnStartInvincible()
{
	// タイマーをクリア
	GetWorld()->GetTimerManager().ClearTimer(InvincibleTimer);

	// 無敵状態を開始
	bIsInvincible = true;

	// 無敵状態の終了をタイマーでセット
	GetWorld()->GetTimerManager().SetTimer(
		InvincibleTimer,
		this,
		&UCombatComponent::OnEndInvincible,
		InvincibleSec,
		false
	);

	// ログ表示
	UE_LOG(LogTemp, Log, TEXT("Invincibility started for %f seconds."), InvincibleSec);
}

// 無敵状態の終了
void UCombatComponent::OnEndInvincible()
{
	bIsInvincible = false;

	// タイマーをクリア
	GetWorld()->GetTimerManager().ClearTimer(InvincibleTimer);

	// ログ表示
	UE_LOG(LogTemp, Log, TEXT("Invincibility ended."));
}

// 入力時呼ばれる攻撃イベント
void UCombatComponent::OnAttack()
{
}

// 入力時呼ばれるパリィイベント
void UCombatComponent::OnParry()
{
}
