// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackReceiver.h"
#include "CombatComponent.generated.h"

// 攻撃受信デリゲート
DECLARE_MULTICAST_DELEGATE(FOnReceiveAttackDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 攻撃処理
	void Attack(AActor* DamagedActor, float Damage);

	// 攻撃受信処理
	EAttackResult ReceiveAttack(const FAttackData& AttackData);

public:
	// 攻撃受信デリゲート
	FOnReceiveAttackDelegate OnReceiveAttackDelegate;
};
