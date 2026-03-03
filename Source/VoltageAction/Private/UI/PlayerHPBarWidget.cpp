// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHPBarWidget.h"
#include "ActorComponent/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UPlayerHPBarWidget::BindEvent(UHealthComponent* HPComp)
{
	// HP更新関数をバインド
	if (HPComp)
	{
		HPComp->OnUpdateHPDelegate.AddUObject(this, &UPlayerHPBarWidget::UpdateHPBar);
	}
}

// HPバーの更新
void UPlayerHPBarWidget::UpdateHPBar(const FHPBarUpdateData& UpdateData)
{
	if (HPBar && NumeratorText && DenominatorText)
	{
		float HPPercent = UpdateData.CurrentHP / UpdateData.MaxHP;

		HPBar->SetPercent(HPPercent);

		NumeratorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.CurrentHP)));
		DenominatorText->SetText(FText::AsNumber(FMath::RoundToInt(UpdateData.MaxHP)));
	}
}
