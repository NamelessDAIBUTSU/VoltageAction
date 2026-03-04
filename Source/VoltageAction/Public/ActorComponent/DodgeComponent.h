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
	// Sets default values for this component's properties
	UDodgeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 回避行動
	void Dodge();

	// ジャスト回避を通知
	void ApplyJustDodge();

	// 回避中か
	bool IsDodging();
	// ジャスト回避判定
	bool IsJustDodging();

	// 無敵状態の開始
	void StartInvincible();

	// 無敵時間終了時刻の取得
	float GetInvincibleEndTime() const;

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
};
