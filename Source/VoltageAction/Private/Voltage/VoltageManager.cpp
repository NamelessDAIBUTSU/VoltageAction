// Fill out your copyright notice in the Description page of Project Settings.


#include "Voltage/VoltageManager.h"
#include "UI/VoltageGaugeWidget.h"

UVoltageManager::UVoltageManager()
{
}

void UVoltageManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // 
}

EVoltageRank UVoltageManager::ConvertVoltageToRank(float Voltage)
{
    if (Voltage < Rank1VoltageThreshold)
    {
        return EVoltageRank::Rank0;
    }
    else if (Voltage < Rank2VoltageThreshold)
    {
        return EVoltageRank::Rank1;
    }
    else if (Voltage < Rank3VoltageThreshold)
    {
        return EVoltageRank::Rank2;
    }
    else
    {
        return EVoltageRank::Rank3;
    }
}

// ボルテージの増減処理
void UVoltageManager::ChangeVoltage(float ChangedVoltage)
{
    CurrentVoltage = FMath::Clamp(CurrentVoltage + ChangedVoltage, 0.f, MaxVoltage);

	// ボルテージゲージウィジェットに更新通知
    FGaugeUpdateData UpdateData(CurrentVoltage, MaxVoltage, ChangedVoltage);
    OnVoltageChangedDelegate.Broadcast(UpdateData);
}

// ジャスト回避によるボルテージ増加通知
void UVoltageManager::OnJustDodge()
{
    ChangeVoltage(JustDodgeGainVoltage); 
}
// 被ダメージによるボルテージ減少通知
void UVoltageManager::OnTakeDamage()
{
    ChangeVoltage(TakeDamageLostVoltage);
}
