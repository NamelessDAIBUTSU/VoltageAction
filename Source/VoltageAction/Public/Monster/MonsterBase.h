// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Interface_DamageGetter.h"
#include "MonsterData.h"
#include "MonsterBase.generated.h"

UCLASS()
class VOLTAGEACTION_API AMonsterBase : public ACharacter, public IDamageGetter
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public: /* IDamageGetter */
	// 与えるダメージを取得
	virtual float GetFinalDamage() override;

public:
	// 攻撃可能状態か
	bool CanAttackState() { return EnemyState == EEnemyState::Idle; }

	// 現在のステート
	void SetEnemyState(EEnemyState State) { EnemyState = State; }
	EEnemyState GetEnemyState() const { return EnemyState; }

private:
	// 敵HPバーウィジェットの初期化
	void InitializeEnemyHPBarWidget();

protected: /* コンポーネント */
	// 戦闘仲介コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCombatComponent> CombatComp;

	// 攻撃コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UEnemyAttackComponent> AttackComp;

	// HP管理コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UHealthComponent> HPComp;

	// 装備コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWeaponComponent> WeaponComp;

protected:
	// 敵の現在のステート
	EEnemyState EnemyState;

	// 基本攻撃ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	float AttackBaseDamage = 10.0f;
};
