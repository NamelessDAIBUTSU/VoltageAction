// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TriggerGimmick/KeepSteppingOnGimmick.h"
#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"

AKeepSteppingOnGimmick::AKeepSteppingOnGimmick()
{
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(RootComponent);

	// 当たり判定コンポーネントの作成
	SwitchCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchCollision"));
	SwitchCollision->SetupAttachment(RootComponent);
}

void AKeepSteppingOnGimmick::BeginPlay()
{
	Super::BeginPlay();

	// Overlapイベントのバインド
	SwitchCollision->OnComponentBeginOverlap.AddDynamic(this, &AKeepSteppingOnGimmick::OnOverlapBegin);
	SwitchCollision->OnComponentEndOverlap.AddDynamic(this, &AKeepSteppingOnGimmick::OnOverlapEnd);
}

void AKeepSteppingOnGimmick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ギミック起動
	for (AReactionGimmickActorBase* TargetGimmick : TargetGimmicksInstance)
	{
		if (TargetGimmick)
		{
			TargetGimmick->ActivateGimmick();
		}
	}
}

void AKeepSteppingOnGimmick::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ギミック停止
	for (AReactionGimmickActorBase* TargetGimmick : TargetGimmicksInstance)
	{
		if (TargetGimmick)
		{
			TargetGimmick->DeactivateGimmick();
		}
	}
}
