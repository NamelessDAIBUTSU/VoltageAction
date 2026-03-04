// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHPBarWidget.h"
#include "ActorComponent/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI/VoltageGaugeWidget.h"

void UPlayerHPBarWidget::Initialize(UHealthComponent* HPComp)
{
	// イベントのバインド
	BindEvent(HPComp);

	// 初期のHPバーの状態を設定
	FGaugeUpdateData InitialData;
	InitialData.CurrentValue = HPComp ? HPComp->GetCurrentHP() : 0.f;
	InitialData.MaxValue = HPComp ? HPComp->GetMaxHP() : 0.f;
	UpdateHPBar(InitialData);
}

void UPlayerHPBarWidget::BindEvent(UHealthComponent* HPComp)
{
	if (HPComp)
	{
		// 多重バインド防止
		HPComp->OnUpdateHPDelegate.RemoveAll(this);

		// HP更新関数をバインド
		HPComp->OnUpdateHPDelegate.AddUObject(this, &UPlayerHPBarWidget::UpdateHPBar);
	}
}

// HPバーの更新
void UPlayerHPBarWidget::UpdateHPBar(const FGaugeUpdateData& UpdateData)
{
	// HPの割合を計算してバーに反映
	if (HPBar)
	{
		float HPPercent = UpdateData.MaxValue > 0.f ? UpdateData.CurrentValue / UpdateData.MaxValue : 0.f;
		HPBar->SetPercent(HPPercent);
	}

	// HPテキストを更新
	if (NumeratorText)
	{
		NumeratorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.CurrentValue)));
	}
	if (DenominatorText)
	{
		DenominatorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.MaxValue)));
	}
}
