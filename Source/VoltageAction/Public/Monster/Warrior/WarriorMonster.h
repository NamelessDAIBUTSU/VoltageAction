// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "WarriorMonster.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AWarriorMonster : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	AWarriorMonster();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// コリジョンの有効か
	void SetAttackCollisionEnabled(bool bEnabled);

	// オーバーラップイベント
	UFUNCTION()
	void OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// 槍のメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UStaticMeshComponent> SpearMesh;

	// 攻撃用コリジョン
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> AttackCollision;

	// 槍攻撃のダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
	float AttackDamage = 10.0f;
};
