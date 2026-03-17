// Fill out your copyright notice in the Description page of Project Settings.


#include "Voltage/VoltageManager.h"
#include "UI/VoltageGaugeWidget.h"

UVoltageManager::UVoltageManager()
{
}

void UVoltageManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// ボルテージパラメータテーブルのロード
	VoltageParamTable = LoadObject<UVoltageParamTable>(nullptr, TEXT("/Game/VoltageAction/Voltage/Data/DA_VoltageParamTable.DA_VoltageParamTable"));
    if (VoltageParamTable == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load VoltageParamTable"));
    }
}

void UVoltageManager::Tick(float DeltaTime)
{
    // 最高ランクに達している場合、ランク維持状態の処理
    if (IsMaxRank())
    {
        bool IsMaintain = UpdateMaxRankMaintain(DeltaTime);
		// 維持状態であれば、ボルテージの減少を行わない
        if (IsMaintain)
            return;
    }

    // 毎フレーム、ボルテージを減少させる
	UpdateLostVoltage(DeltaTime);
}

TStatId UVoltageManager::GetStatId() const
{
    return TStatId();
}

bool UVoltageManager::IsTickable() const
{
	// ボルテージが0より大きい場合のみTick処理を行う
	return CurrentVoltage > 0.f;
}

EVoltageRank UVoltageManager::ConvertVoltageToRank(float Voltage)
{
    if(VoltageParamTable == nullptr)
        return EVoltageRank::Rank1;

    // 判定は小数点切り捨てで行う
	float FloorVoltage = FMath::FloorToFloat(Voltage);

    for (EVoltageRank Rank : TEnumRange<EVoltageRank>())
    {
        FVoltageRankParam* RankParam = VoltageParamTable->VoltageRankParams.Find(Rank);
        if (RankParam)
        {
            if (FloorVoltage <= RankParam->MaxVoltageInRank)
            {
                return Rank;
            }
        }
    }

    return EVoltageRank::Rank1;
}

// ボルテージの増減処理
void UVoltageManager::ChangeVoltage(float ChangedVoltage)
{
	// ボルテージランクが最大でボルテージ増加する場合、ボルテージ維持時間をリセットする
    if (IsMaxRank() && ChangedVoltage >= 0.f)
    {
        StartMaxRankMaintain();
    }
    else
    {
        // ボルテージの増減処理
        CurrentVoltage = FMath::Clamp(CurrentVoltage + ChangedVoltage, 0.f, MaxVoltage);

        // 現在のボルテージランクを更新
        CurrentRank = ConvertVoltageToRank(CurrentVoltage);

		// ボルテージランクが最大になった時の処理
        if (IsMaxRank())
        {
			// 最高ランクの維持時間をリセットして開始
            StartMaxRankMaintain();

            // 最大ランクに達したイベントを発火
            OnVoltageMaxRankDelegate.Broadcast();
        }

        // ボルテージゲージウィジェットに更新通知
        FGaugeUpdateData UpdateData(CurrentVoltage, MaxVoltage, ChangedVoltage, CurrentRank);
        OnVoltageChangedDelegate.Broadcast(UpdateData);
    }
}

// ジャスト回避によるボルテージ増加通知
void UVoltageManager::OnJustDodge()
{
    if (VoltageParamTable)
    {
        ChangeVoltage(VoltageParamTable->JustDodgeGainVoltage);
    }
}
// 被ダメージによるボルテージ減少通知
void UVoltageManager::OnTakeDamage()
{
    if (VoltageParamTable)
    {
        ChangeVoltage(VoltageParamTable->TakeDamageLostVoltage);
    }
}
// パリィ成功によるボルテージ増加
void UVoltageManager::OnParrySuccess()
{
    if (VoltageParamTable)
    {
        ChangeVoltage(VoltageParamTable->ParrySuccessGainVoltage);
    }
}

// 最高ランクの維持状態の処理
bool UVoltageManager::UpdateMaxRankMaintain(float DeltaTime)
{
    // ログ表示
	UE_LOG(LogTemp, Log, TEXT("UpdateMaxRankMaintain: ElapsedMaxRankMaintainSec = %f"), ElapsedMaxRankMaintainSec);

    if (VoltageParamTable == nullptr)
        return false;

    // 最高ランクの維持時間を取得
    const float MaintainSec = VoltageParamTable->MaxRankMaintainSec;

    // 経過時間の増加
    ElapsedMaxRankMaintainSec += DeltaTime;

    return ElapsedMaxRankMaintainSec < MaintainSec;
}

// 毎フレームのボルテージ減少処理
void UVoltageManager::UpdateLostVoltage(float DeltaTime)
{
    if (VoltageParamTable == nullptr)
        return;

    FVoltageRankParam* RankParam = VoltageParamTable->VoltageRankParams.Find(CurrentRank);
    if (RankParam)
    {
        ChangeVoltage(RankParam->DecreaseVoltagePerSec * DeltaTime);
    }
}

// 最大ランクの維持を開始
void UVoltageManager::StartMaxRankMaintain()
{
    ElapsedMaxRankMaintainSec = 0.f;
}
