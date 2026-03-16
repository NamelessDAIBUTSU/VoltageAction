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
	// 攻撃処理
	// #MEMO : 攻撃用コリジョンのオーバーラップ時に呼ぶ
	void HandleAttackHit(AActor* DamagedActor);

	// 現在のコンボデータ
	UComboDataAsset* GetCurrentComboData() const;
	void SetCurrentAttackData(UComboDataAsset* NewComboData);

	// 現在の攻撃データを取得
	class UAttackDataAsset* GetCurrentAttackData() const;

	// 現在コンボの最終攻撃か
	bool IsFinalAttackInCurrentCombo();

	// 次回攻撃がコンボ攻撃の初撃か
	bool CheckIsNextAttackFirst(UComboDataAsset* NextComboData);

protected:
	// 次の攻撃のために情報を設定
	void SetupNextAttack(UComboDataAsset* NextComboData);

private:
	// 攻撃イベント実行
	void ExecAttack(EAttackResult AttackResult, const FAttackData& AttackData);

protected:
	// 現在のコンボデータ
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UComboDataAsset> CurrentComboData = nullptr;

	// 現在の攻撃データインデックス
	int32 CurrentAttackIndexInCombo = INDEX_NONE;

	// 攻撃モンタージュ終了時のデリゲート
	FOnMontageEnded OnMontageEndDelegate;
};
