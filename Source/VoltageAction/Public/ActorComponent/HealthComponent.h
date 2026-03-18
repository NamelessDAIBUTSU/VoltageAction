// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/PlayerHPBarWidget.h"
#include "../Attack/AttackDef.h"
#include "HealthComponent.generated.h"

struct FGaugeUpdateData;

// HP更新デリゲート
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateHPDelegate, const FGaugeUpdateData&);
// 被ダメージデリゲート
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamagedDelegate, const FAttackData&);
// 死亡デリゲート
DECLARE_MULTICAST_DELEGATE(FOnDieDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VOLTAGEACTION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// HPの取得
	float GetCurrentHP() const { return CurrentHP; }
	float GetMaxHP() const { return MaxHP; }

	// 死亡判定
	bool IsDead() const { return CurrentHP <= 0.f; }

	// ダメージ受け処理
	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

private:
	// 死亡処理
	void Die();

public:
	// プレイヤーHP更新デリゲート
	FOnUpdateHPDelegate OnUpdateHPDelegate;
	// 被ダメージ時デリゲート
	FOnDamagedDelegate OnDamagedDelegate;
	// 死亡時デリゲート
	FOnDieDelegate OnDieDelegate;

private:
	UPROPERTY(VisibleAnywhere)
	float CurrentHP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.f;
};