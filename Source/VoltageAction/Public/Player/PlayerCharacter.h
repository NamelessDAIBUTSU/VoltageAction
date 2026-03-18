// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/Weighted.h"
#include <Player/PlayerDef.h>
#include <Attack/AttackDef.h>
#include "Interface/Interface_DamageGetter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VOLTAGEACTION_API APlayerCharacter : public ACharacter, public IDamageGetter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* IDamageGetter */
	// 与えるダメージを取得
	virtual float GetFinalDamage() override;
	// 与える耐久値ダメージを取得
	virtual float GetFinalPoiseDamage() override;
	// 与えるブレイク値ダメージを取得
	virtual float GetFinalBreakDamage() override;

public: /* 入力によるアクション */
	// 移動
	void TryMove(const FInputActionValue& Value);

	// カメラ回転
	void RotateCamera(const FInputActionValue& Value);

public: /* プレイヤー状態 */
	void SetPlayerState(EPlayerState State);
	EPlayerState GetPlayerState() const { return PlayerState; }

	// 攻撃可能状態か
	bool CanAttackState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::PostAttack; }
	// パリィ可能状態か
	bool CanParryState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::PostParry; }
	// 回避可能状態か
	bool CanDodgeState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::PostAttack || PlayerState == EPlayerState::PostParry; }

	// 攻撃状態か
	bool IsAttackState() {return PlayerState == EPlayerState::Attack || PlayerState == EPlayerState::PostAttack;}
	// パリィ状態か
	bool IsParryState() {return PlayerState == EPlayerState::PreParry || PlayerState == EPlayerState::Parring || PlayerState == EPlayerState::Parry_End || PlayerState == EPlayerState::PostParry;}

private:
	// イベントのバインド
	void BindEvents();

	// 各種アニメーション再生
	UFUNCTION()
	void OnPlayHitAnim(const FAttackData& AttackData);
	UFUNCTION()
	void OnDie();

private: /* コンポーネント */
	// カメラ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;

	// カメラ回転用のスプリングアーム
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	// 回避
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDodgeComponent> DodgeComp;

	// 戦闘仲介
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCombatComponent> CombatComp;

	// 攻撃
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerAttackComponent> AttackComp;

	// パリィ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParryComponent> ParryComp;

	// HP管理
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HPComp;

	// 装備管理
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponComponent> WeaponComp;

private: /* アニメーション */
	// ヒット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitReactMontage;
	// 死亡
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DieMontage;

private:
	// 現在の状態
	EPlayerState PlayerState = EPlayerState::Idle;

	// マウスによるカメラ回転スピード
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CameraXRotateSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CameraYRotateSpeed = 0.1f;
};
