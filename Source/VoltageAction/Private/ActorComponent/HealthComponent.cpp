// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/HealthComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ダメージ受けイベントをバインド
	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(
			this,
			&UHealthComponent::TakeAnyDamage
		);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// ダメージ受け処理
void UHealthComponent::TakeAnyDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	CurrentHP -= Damage;

	// HP更新デリゲートの発火
	OnUpdateHPDelegate.Broadcast(CurrentHP, Damage);

	if (CurrentHP <= 0.f)
	{
		Die();
	}
}

// 死亡処理
void UHealthComponent::Die()
{
	if (AActor* Owner = GetOwner())
	{
		Owner->Destroy();
	}	
}

