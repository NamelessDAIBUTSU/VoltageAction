// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"

// ジャスト回避デリゲート
DECLARE_MULTICAST_DELEGATE(FOnJustDodgeDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDodgeComponent();

protected:
	virtual void BeginPlay() override;

public:
	// 回避アクション
	void TryDodge();

	// ジャスト回避成功を通知
	void OnJustDodgeSuccess();

	// ジャスト回避判定
	bool IsJustDodging();

	// 無敵状態の開始
	void StartInvincible();

	// 無敵時間終了時刻の取得
	float GetInvincibleEndTime() const;

private:
	// 回避終了時のイベント
	UFUNCTION()
	void OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:
	// ジャスト回避通知デリゲート
	FOnJustDodgeDelegate OnJustDodgeDelegate;

private:
	// 回避アニメーションモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DodgeMontage;

	// ジャスト回避の成功判定時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float JustDodgeSec = 0.15f;

	// ジャスト回避状態終了時間
	float JustDodgeEndTime = 0.f;

	// 回避モンタージュ終了時のデリゲート
	FOnMontageEnded OnMontageEndDelegate;
};
