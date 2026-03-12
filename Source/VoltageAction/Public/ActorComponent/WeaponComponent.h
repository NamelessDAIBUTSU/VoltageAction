// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/WeaponActorBase.h"
#include "WeaponComponent.generated.h"

/// <summary>
/// 装備する武器を管理するコンポーネント
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 武器の取得
	AWeaponActorBase* GetWeapon() const { return EquippedWeapon; }
	void SetWeapon(AWeaponActorBase* NewWeapon) { EquippedWeapon = NewWeapon; }

	// 初期生成する武器クラスの取得
	TSubclassOf<AWeaponActorBase> GetInitWeapon() const { return InitWeaponActorClass; }

private:
	// 装備中の武器
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActorBase> EquippedWeapon;

	// 初期生成する武器クラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponActorBase> InitWeaponActorClass;
};
