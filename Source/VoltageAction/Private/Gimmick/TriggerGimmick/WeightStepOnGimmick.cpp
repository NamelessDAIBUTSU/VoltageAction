// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TriggerGimmick/WeightStepOnGimmick.h"

#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"
#include <Interface/Weighted.h>

AWeightStepOnGimmick::AWeightStepOnGimmick()
{
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(RootComponent);

	// 当たり判定コンポーネントの作成
	SwitchCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchCollision"));
	SwitchCollision->SetupAttachment(RootComponent);
}

void AWeightStepOnGimmick::BeginPlay()
{
	Super::BeginPlay();

	// Overlapイベントのバインド
	SwitchCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeightStepOnGimmick::OnOverlapBegin);
}

void AWeightStepOnGimmick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 触ったプレイヤーが重さを持っているかチェック
	if (OtherActor == nullptr)
		return;

	// WeightInterfaceの取得
	IWeighted* WeightedInterface = Cast<IWeighted>(OtherActor);
	if (WeightedInterface == nullptr)
		return;


	// 必要な重さを満たしているかチェック
	// 満たしていない場合
	if (WeightedInterface->GetWeight() < RequiredWeight)
	{

		return;
	}
	// 満たしている場合
	else
	{
		// ギミック起動
		for (AReactionGimmickActorBase* TargetGimmick : TargetGimmicksInstance)
		{
			if (TargetGimmick)
			{
				TargetGimmick->ActivateGimmick();
			}
		}

		// 当たり判定の無効化
		SwitchCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
