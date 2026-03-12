// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class VOLTAGEACTION_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// 敵HPバーウィジェットの初期化
	void InitializeEnemyHPBarWidget();

protected:
	// 戦闘コンポーネント
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
};
