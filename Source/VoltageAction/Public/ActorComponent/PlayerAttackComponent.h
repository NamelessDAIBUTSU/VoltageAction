// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/AttackComponent.h"
#include "PlayerAttackComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VOLTAGEACTION_API UPlayerAttackComponent : public UAttackComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// 攻撃モンタージュ終了時のコールバック
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
		
	// 攻撃アクション発生時
	void TryAttack(UComboDataAsset* NextComboData);

private:
	// 基本攻撃ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	float AttackBaseDamage = 10.0f;
};
