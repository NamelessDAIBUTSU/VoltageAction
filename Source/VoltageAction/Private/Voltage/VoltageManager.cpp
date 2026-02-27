// Fill out your copyright notice in the Description page of Project Settings.


#include "Voltage/VoltageManager.h"

UVoltageManager::UVoltageManager()
{
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

// ジャスト回避によるボルテージ増加
void UVoltageManager::ApplyJustDodge()
{
    AddVoltage(JustDodgeGainVoltage); 
}

void UVoltageManager::ApplyTakeDamage()
{
    LostVoltage(TakeDamageLostVoltage);
}
