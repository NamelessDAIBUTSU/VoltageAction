// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/CombatComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Interface/AttackReceiver.h>
#include <Player/PlayerCharacter.h>
#include <ActorComponent/DodgeComponent.h>

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

