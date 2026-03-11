// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/Weighted.h"
#include <Player/PlayerDef.h>
#include "Interface/AttackReceiver.h"
#include "PlayerCharacter.generated.h"

class APlayerGhost;
class UGhostManagerComponent;

UCLASS()
class VOLTAGEACTION_API APlayerCharacter : public ACharacter, public IAttackReceiver
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* IAttackReceiver */
	// 攻撃を受信
	virtual EAttackResult ReceiveAttack(const FAttackData& AttackData) override;

public: /* 入力によるアクション */
	// 移動
	void TryMove(const FInputActionValue& Value);

	// カメラ回転
	void RotateCamera(const FInputActionValue& Value);

public: /* プレイヤー状態 */
	void SetPlayerState(EPlayerState State);
	EPlayerState GetPlayerState() const { return PlayerState; }

	// 攻撃可能状態か
	bool CanAttackState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::Attacked; }
	// パリィ可能状態か
	bool CanParryState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::Parried; }
	// 回避可能状態か
	bool CanDodgeState() { return PlayerState == EPlayerState::Idle || PlayerState == EPlayerState::Attacked || PlayerState == EPlayerState::Parried; }

	// 攻撃状態か
	bool IsAttackState() {return PlayerState == EPlayerState::Attack || PlayerState == EPlayerState::Attacked;}
	// パリィ状態か
	bool IsParryState() {return PlayerState == EPlayerState::Parry || PlayerState == EPlayerState::Parried;}

public: /* カメラ */
	// マウスによるカメラ回転スピード
	UPROPERTY(EditAnywhere)
	float CameraXRotateSpeed = 0.1f;
	UPROPERTY(EditAnywhere)
	float CameraYRotateSpeed = 0.1f;

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
	TObjectPtr<class UAttackComponent> AttackComp;

	// パリィ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParryComponent> ParryComp;

	// HP管理
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HPComp;

	// 装備管理
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponComponent> WeaponComp;

private:
	// 生成する武器アクタのクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponActorBase> WeaponActorClass;

	// 現在の状態
	EPlayerState PlayerState = EPlayerState::Idle;
};
