// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Interface_DamageGetter.h"
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

private:
	// 敵HPバーウィジェットの初期化
	void InitializeEnemyHPBarWidget();

protected:
	// 戦闘仲介コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCombatComponent> CombatComp;

	// 攻撃コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAttackComponent> AttackComp;

	// HP管理コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UHealthComponent> HPComp;

	// 装備コンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWeaponComponent> WeaponComp;

	// 基本ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	float AttackBaseDamage = 10.0f;

	// 所有するコンボデータリスト

};
