// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/PlayerHPBarWidget.h"
#include "HealthComponent.generated.h"

// HP更新デリゲート
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateHPDelegate, const FHPBarUpdateData&);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VOLTAGEACTION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float GetCurrentHP() const { return CurrentHP; }

	// ダメージ受け処理
	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

private:
	// 死亡処理
	void Die();

public:
	// HP更新デリゲート
	FOnUpdateHPDelegate OnUpdateHPDelegate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.f;

	UPROPERTY(VisibleAnywhere)
	float CurrentHP = 0.f;
};