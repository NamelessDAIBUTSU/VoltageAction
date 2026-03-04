// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CombatComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Interface/AttackReceiver.h>
#include <Player/PlayerCharacter.h>
#include <ActorComponent/DodgeComponent.h>

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
void UCombatComponent::Attack(AActor* DamagedActor, float Damage)
{
	if (DamagedActor == nullptr)
		return;

	AActor* AttackedOwner = GetOwner();
	if (AttackedOwner == nullptr)
		return;

	// 送信する攻撃情報を作成
	FAttackData AttackData;
	AttackData.Damage = Damage;

	IAttackReceiver* AttackReceiver = Cast<IAttackReceiver>(DamagedActor);
	if (AttackReceiver)
	{
		// 攻撃を受ける側で攻撃受信
		EAttackResult Result = AttackReceiver->ReceiveAttack(AttackData);

		// 当たっていたらダメージイベントを発火
		if (Result == EAttackResult::Hit)
		{
			UGameplayStatics::ApplyDamage(DamagedActor, Damage, AttackedOwner->GetInstigatorController(), AttackedOwner, UDamageType::StaticClass());
		}
	}
}

// 攻撃処理
EAttackResult UCombatComponent::ReceiveAttack(const FAttackData& AttackData)
{
	AActor* DamagedOwner = GetOwner();
	if (DamagedOwner == nullptr)
		return EAttackResult::None;

	// 無敵状態なら攻撃を無効化
	if(bIsInvincible)
		return EAttackResult::None;

	// ジャスト回避判定
	if (UDodgeComponent* DodgeComp = DamagedOwner->FindComponentByClass<UDodgeComponent>())
	{
		if (DodgeComp->IsJustDodging())
		{
			// ジャスト回避を通知
			DodgeComp->ApplyJustDodge();

			return EAttackResult::JustDodge;
		}
	}

	// #TODO : パリィ判定, etc...


	// 攻撃受信イベント発火
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

