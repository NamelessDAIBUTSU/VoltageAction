// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/StaggerComponent.h"
#include <Enemy/EnemyBase.h>

UStaggerComponent::UStaggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStaggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ひるみ値、ブレイク値の初期化
	ResetPoise();
	ResetBreak();
}

void UStaggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// よろめき中の時間更新
	if (CurrentStaggerType == EStaggerType::Stagger)
	{

		return;
	}
	// ブレイク中の時間更新
	if (CurrentStaggerType == EStaggerType::Break)
	{

		return;
	}

	// 耐性値の回復更新
	UpdateRestorePoise(DeltaTime);

	// ブレイク値の回復更新
	UpdateRestoreBreak(DeltaTime);
}

// 耐久値 / ブレイク値へのダメージ
void UStaggerComponent::OnTakeStaggerDamage(const FAttackData& AttackData)
{
	OnDecreasePoiseNum(AttackData.PoiseDamage);
	OnDecreaseBreakNum(AttackData.BreakDamage);
}

// 耐性値の減少
void UStaggerComponent::OnDecreasePoiseNum(float Damage)
{
	CurrentPoiseNum -= Damage;

	UE_LOG(LogTemp, Log, TEXT("PoiseDamage %f, Current %f"), Damage, CurrentPoiseNum);

	// よろめき発生
	if (CurrentPoiseNum <= 0.f)
	{
		ExecStagger();
	}
}

// ブレイク値の減少
void UStaggerComponent::OnDecreaseBreakNum(float Damage)
{
	CurrentBreakNum -= Damage;

	UE_LOG(LogTemp, Log, TEXT("BreakDamage %f, Current %f"), Damage, CurrentBreakNum);

	// ブレイク発生
	if (CurrentBreakNum <= 0.f)
	{
		ExecBreak();
	}
}

// 耐性値の回復更新
void UStaggerComponent::UpdateRestorePoise(float DeltaTime)
{
	CurrentPoiseNum = FMath::Clamp(CurrentPoiseNum + RestorePoiseNum * DeltaTime, 0.f, InitPoiseNum);
}

// ブレイク値の回復更新
void UStaggerComponent::UpdateRestoreBreak(float DeltaTime)
{
	CurrentBreakNum = FMath::Clamp(CurrentBreakNum + RestorePoiseNum * DeltaTime, 0.f, InitBreakNum);
}

// よろめき発生
void UStaggerComponent::ExecStagger()
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwner());
	if (Enemy == nullptr)
		return;

	// ステート変更
	CurrentStaggerType = EStaggerType::Stagger;

	// モンタージュ再生
	Enemy->PlayAnimMontage(StaggerMontage);

	// イベント発火
	OnStaggerDelegate.Broadcast(CurrentStaggerType);

	// パラメータのリセット
	ResetPoise();
}

// ブレイク発生
void UStaggerComponent::ExecBreak()
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwner());
	if (Enemy == nullptr)
		return;

	// ステート変更
	CurrentStaggerType = EStaggerType::Break;

	// モンタージュ再生
	Enemy->PlayAnimMontage(BreakMontage);

	// イベント発火
	OnStaggerDelegate.Broadcast(CurrentStaggerType);

	// パラメータのリセット
	ResetBreak();
}

// パラメータのリセット
void UStaggerComponent::ResetPoise()
{
	CurrentPoiseNum = InitPoiseNum;
}
void UStaggerComponent::ResetBreak()
{
	CurrentBreakNum = InitBreakNum;
}

