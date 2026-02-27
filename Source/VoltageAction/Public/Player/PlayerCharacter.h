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

public:
	// カメラ回転
	void RotateCamera(FVector2D RotateVec);

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

	// 戦闘コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCombatComponent> CombatComp;

	// HP管理コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HPComp;
};
