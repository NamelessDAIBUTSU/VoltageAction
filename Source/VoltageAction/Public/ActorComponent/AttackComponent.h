// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interface/AttackReceiver.h"
#include "AttackComponent.generated.h"

class UComboDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// 攻撃ヒット時
	void HandleAttackHit(AActor* DamagedActor);

	// 攻撃アクション発生時
	void TryAttack(UComboDataAsset* NextComboData);

	// 現在のコンボデータ
	UComboDataAsset* GetCurrentComboData() const { return CurrentComboData.Get(); }

private:
	// 現在の攻撃データを取得
	class UAttackDataAsset* GetCurrentAttackData() const;

	// 攻撃イベント実行
	void ExecAttack(EAttackResult AttackResult, const FAttackData& AttackData);

	// 攻撃アニメーションモンタージュ終了時のコールバック
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 現在コンボの最終攻撃か
	bool IsFinalAttackInCurrentCombo();

private:
	// 現在のコンボデータ
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UComboDataAsset> CurrentComboData = nullptr;

	// 現在のコンボインデックス
	int32 CurrentComboIndex = INDEX_NONE;

	// 攻撃モンタージュ終了時のデリゲート
	FOnMontageEnded OnMontageEndDelegate;
};
