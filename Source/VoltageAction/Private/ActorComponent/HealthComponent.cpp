// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/HealthComponent.h"
#include "GameFramework/Character.h"
#include "UI/VoltageGaugeWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// 現在のHPをMaxHPに設定
	CurrentHP = MaxHP;

	// ダメージ受けイベントをバインド
	if (AActor* Owner = GetOwner())
	{
		// ダメージ処理
		Owner->OnTakeAnyDamage.AddDynamic(
			this,
			&UHealthComponent::TakeAnyDamage
		);
	}

	// HPバー初期化用に更新デリゲートの発火
	FGaugeUpdateData UpdateData(CurrentHP, MaxHP, 0.f);
	OnUpdateHPDelegate.Broadcast(UpdateData);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// ダメージ受け処理
void UHealthComponent::TakeAnyDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	// ダメージ計算
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.f, CurrentHP);

	// 被ダメージ時デリゲートの発火（原因イベント）
	OnDamagedDelegate.Broadcast();

	// HP更新デリゲートの発火（結果イベント）
	FGaugeUpdateData UpdateData(CurrentHP, MaxHP, 0.f);
	OnUpdateHPDelegate.Broadcast(UpdateData);

	// 死亡処理の呼び出し
	if (IsDead())
	{
		Die();
	}
}

// 死亡処理
void UHealthComponent::Die()
{
	// 死亡時デリゲートの発火
	OnDieDelegate.Broadcast();

	// アクターの削除
	if (AActor* Owner = GetOwner())
	{
		Owner->Destroy();
	}	
}

