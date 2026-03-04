// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VoltageGaugeWidget.h"
#include <Voltage/VoltageManager.h>
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include <ActorComponent/HealthComponent.h>

void UVoltageGaugeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// 初期化
void UVoltageGaugeWidget::Initialize(UHealthComponent* HPComp)
{
	// イベントのバインド
	BindEvent(HPComp);

	// 初期のHPバーの状態を設定
	UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>();
	if (VoltageManager)
	{
		FGaugeUpdateData InitialData(VoltageManager->GetCurrentVoltage(), VoltageManager->GetMaxVoltage(), 0.f);
		UpdateVoltageGaugeImpl(InitialData);
	}
}

// バインドするボルテージ更新
void UVoltageGaugeWidget::OnUpdateVoltageGauge(const FGaugeUpdateData& UpdateData)
{
	// 初期のHPバーの状態を設定
	UpdateVoltageGaugeImpl(UpdateData);
}

// ボルテージゲージの更新
void UVoltageGaugeWidget::UpdateVoltageGaugeImpl(const FGaugeUpdateData& UpdateData)
{
	// HPの割合を計算してバーに反映
	if (VoltageGauge)
	{
		float Ratio = UpdateData.MaxValue > 0.f ? UpdateData.CurrentValue / UpdateData.MaxValue : 0.f;
		VoltageGauge->SetPercent(Ratio);
	}

	// ボルテージテキストを更新
	if (NumeratorText)
	{
		NumeratorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.CurrentValue)));
	}
	if (DenominatorText)
	{
		DenominatorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.MaxValue)));
	}
}

void UVoltageGaugeWidget::BindEvent(UHealthComponent* HPComp)
{
	// ジャスト回避時のイベント
	if (UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>())
	{
		VoltageManager->OnVoltageChangedDelegate.RemoveAll(this);
		VoltageManager->OnVoltageChangedDelegate.AddUObject(this, &UVoltageGaugeWidget::OnUpdateVoltageGauge);
	}
}
