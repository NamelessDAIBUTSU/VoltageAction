// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Attack/AttackDef.h>
#include "StaggerComponent.generated.h"

UENUM(BlueprintType)
enum class EStaggerType : uint8
{
	Stagger		UMETA(DisplayName = "よろめき"),
	Break		UMETA(DisplayName = "ブレイク"),
	NONE		UMETA(DisplayName = "無し"),
};

// よろめき発生時デリゲート
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaggerDelegate, EStaggerType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UStaggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaggerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// よろめき中か
	bool IsStagger() const { return CurrentStaggerType == EStaggerType::Stagger; }
	// ブレイク中か
	bool IsBreaking() const { return CurrentStaggerType == EStaggerType::Break; }

	// 耐久値 / ブレイク値へのダメージ
	void OnTakeStaggerDamage(const FAttackData& AttackData);

	// 耐性値の減少
	void OnDecreasePoiseNum(float Damage);
	// ブレイク値の減少
	void OnDecreaseBreakNum(float Damage);

private:
	// 耐性値の回復更新
	void UpdateRestorePoise(float DeltaTime);
	// ブレイク値の回復更新
	void UpdateRestoreBreak(float DeltaTime);

	// よろめき発生
	void ExecStagger();
	// ブレイク発生
	void ExecBreak();

	// パラメータのリセット
	void ResetPoise();
	void ResetBreak();

public:
	// よろめき発生時デリゲート
	FOnStaggerDelegate OnStaggerDelegate;

private: /* アニメーション */
	// よろめきモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> StaggerMontage;
	// ブレイクモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> BreakMontage;

private:
	// 初期耐性値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InitPoiseNum;
	// 初期ブレイク値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InitBreakNum;

	// 1秒で回復する耐性値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RestorePoiseNum;
	// 1秒で回復するブレイク値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RestoreBreakNum;

	// 現在の耐性値
	float CurrentPoiseNum = 0.f;
	// 現在のブレイク値
	float CurrentBreakNum = 0.f;

	// 現在の状態
	EStaggerType CurrentStaggerType = EStaggerType::NONE;
};
