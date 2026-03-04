// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHPBarWidget.h"
#include "ActorComponent/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UEnemyHPBarWidget::Initialize(UHealthComponent* HPComp)
{
	// イベントのバインド
	BindEvent(HPComp);

	// 初期のHPバーの状態を設定
	FHPBarUpdateData InitialData;
	InitialData.CurrentHP = HPComp ? HPComp->GetCurrentHP() : 0.f;
	InitialData.MaxHP = HPComp ? HPComp->GetMaxHP() : 0.f;
	UpdateHPBar(InitialData);
}

void UEnemyHPBarWidget::BindEvent(UHealthComponent* HPComp)
{
	if (HPComp)
	{
		// 多重バインド防止
		HPComp->OnUpdateHPDelegate.RemoveAll(this);

		// HP更新関数をバインド
		HPComp->OnUpdateHPDelegate.AddUObject(this, &UEnemyHPBarWidget::UpdateHPBar);
	}
}

// HPバーの更新
void UEnemyHPBarWidget::UpdateHPBar(const FHPBarUpdateData& UpdateData)
{
	// HPの割合を計算してバーに反映
	if (HPBar)
	{
		float HPPercent = UpdateData.MaxHP > 0.f ? UpdateData.CurrentHP / UpdateData.MaxHP : 0.f;
		HPBar->SetPercent(HPPercent);
	}

	// HPテキストを更新
	if (NumeratorText)
	{
		NumeratorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.CurrentHP)));
	}
	if (DenominatorText)
	{
		DenominatorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.MaxHP)));
	}
}
