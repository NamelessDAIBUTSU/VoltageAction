// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecoratorBoolValue.h"

UBTDecoratorBoolValue::UBTDecoratorBoolValue()
{
	bNotifyTick = true;               // TickNode を呼んでもらう
	bAllowAbortChildNodes = true;     // 条件が変わったら子ノードを中断
}

bool UBTDecoratorBoolValue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return false;

	return BBComp->GetValueAsBool(BoolKey.SelectedKeyName) == Value;
}

void UBTDecoratorBoolValue::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 毎フレーム条件をチェックして条件変化があればBTを再評価
	bool bResult = CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (bResult == false)
	{
		OwnerComp.RequestExecution(this); 
	}
}