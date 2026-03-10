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

public: /* カメラ */
	// マウスによるカメラ回転スピード
	UPROPERTY(EditAnywhere)
	float CameraXRotateSpeed = 0.1f;
	UPROPERTY(EditAnywhere)
	float CameraYRotateSpeed = 0.1f;

private: /* コンポーネント */
	// カメラコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;

	// カメラ回転用のスプリングアームコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	// 回避コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDodgeComponent> DodgeComp;

	// 戦闘仲介コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCombatComponent> CombatComp;

	// 攻撃コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAttackComponent> AttackComp;

	// パリィコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParryComponent> ParryComp;

	// HP管理コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HPComp;

	// 装備管理コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponComponent> WeaponComp;

private:
	// 生成する武器アクタのクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponActorBase> WeaponActorClass;
};
