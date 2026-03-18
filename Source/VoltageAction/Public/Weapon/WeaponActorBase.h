// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActorBase.generated.h"

class UComboDataAsset;

/// <summary>
/// プレイヤーが装備する武器の基底クラス
/// </summary>
UCLASS()
class VOLTAGEACTION_API AWeaponActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponActorBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// アタッチするソケット名の取得
	FName GetAttachSocketName() const { return AttachSocketName; }

	// 基礎攻撃力の取得
	float GetBaseDamage() const { return BaseDamage; }
	float GetBasePoiseDamage() const { return BasePoiseDamage; }
	float GetBaseBreakDamage() const { return BaseBreakDamage; }

	// 弱攻撃コンボデータの取得
	UComboDataAsset* GetLightComboData() const { return LightComboData; }
	// 強攻撃コンボデータの取得
	UComboDataAsset* GetHeavyComboData() const { return HeavyComboData; }

	// 攻撃用コリジョンの有効/無効化
	void SetAttackCollision(bool flag);

public:
	// 攻撃用コリジョンオーバーラップ時イベント
	UFUNCTION()
	void OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// スタティックメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	// アタッチするソケット名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName AttachSocketName = TEXT("WeaponSocket");

	// 基礎攻撃力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 10.f;

	// 基礎耐久値ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	float BasePoiseDamage = 10.f;

	// 基礎ブレイクダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	float BaseBreakDamage = 10.f;

	// 攻撃用コリジョン
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> AttackCollision;

private: /* 武器に紐づくコンボ攻撃データ */
	// 弱攻撃コンボ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UComboDataAsset> LightComboData;
	// 強攻撃コンボ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UComboDataAsset> HeavyComboData;
};
