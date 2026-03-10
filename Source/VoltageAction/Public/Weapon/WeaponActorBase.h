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
	// Sets default values for this actor's properties
	AWeaponActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// アタッチするソケット名の取得
	FName GetAttachSocketName() const { return AttachSocketName; }

	// 基礎攻撃力の取得
	float GetBaseDamage() const { return BaseDamage; }
	// 弱攻撃コンボデータの取得
	UComboDataAsset* GetLightComboData() const { return LightComboData; }
	// 強攻撃コンボデータの取得
	UComboDataAsset* GetHeavyComboData() const { return HeavyComboData; }

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

private: /* 武器に紐づくコンボ攻撃データ */
	// 弱攻撃コンボ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UComboDataAsset> LightComboData;
	// 強攻撃コンボ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UComboDataAsset> HeavyComboData;
};
