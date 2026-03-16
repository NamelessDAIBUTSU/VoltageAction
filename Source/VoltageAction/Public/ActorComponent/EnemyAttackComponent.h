// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/AttackComponent.h"
#include "EnemyAttackComponent.generated.h"

// コンボ攻撃終了時デリゲート
DECLARE_MULTICAST_DELEGATE(FOnComboAttackEndDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VOLTAGEACTION_API UEnemyAttackComponent : public UAttackComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// コンボデータリストのサイズ取得
	int GetComboDataListSize() const { return ComboDataList.Num(); }

	// コンボ攻撃を開始
	void StartComboAttack(int ComboDataIndex);

	// 攻撃を試す
	void TryAttack(UComboDataAsset* NextComboData);

private:
	// 攻撃モンタージュ終了時のコールバック
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	// 最終攻撃モンタージュ終了時のコールバック
	UFUNCTION()
	void OnFinalAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted);

public:
	// コンボ攻撃終了時デリゲート
	FOnMontageEnded OnComboAttackEndDelegate;

private:
	// 所有するコンボデータリスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UComboDataAsset>> ComboDataList;
};
