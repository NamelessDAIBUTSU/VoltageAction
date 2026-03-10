// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackReceiver.h"
#include "CombatComponent.generated.h"

class UAnimMontage;

// 攻撃受信デリゲート
DECLARE_MULTICAST_DELEGATE(FOnReceiveAttackDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	// 攻撃受信処理
	EAttackResult ReceiveAttack(const FAttackData& AttackData);

	// 無敵状態の取得
	bool IsInvincible() const { return bIsInvincible; }

public: /* コールバック */
	// 無敵状態の開始
	void OnStartInvincible();
	// 無敵状態の終了
	void OnEndInvincible();

	// 入力時呼ばれる攻撃イベント
	void OnAttack();
	// 入力時呼ばれるパリィイベント
	void OnParry();

public:
	// 攻撃受信デリゲート
	FOnReceiveAttackDelegate OnReceiveAttackDelegate;

private: /* 無敵関連 */
	// 無敵状態フラグ
	bool bIsInvincible = false;

	// 無敵状態の終了処理用ハンドル
	FTimerHandle InvincibleTimer;

	// 無敵状態の持続時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InvincibleSec = 0.5f;
};
