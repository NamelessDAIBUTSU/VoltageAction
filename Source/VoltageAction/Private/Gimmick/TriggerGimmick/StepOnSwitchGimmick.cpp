// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TriggerGimmick/StepOnSwitchGimmick.h"
#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"
#include <Room/RoomManager.h>
#include <Room/RoomBase.h>

AStepOnSwitchGimmick::AStepOnSwitchGimmick()
{
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(RootComponent);

	// 当たり判定コンポーネントの作成
	SwitchCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchCollision"));
	SwitchCollision->SetupAttachment(RootComponent);
}

void AStepOnSwitchGimmick::BeginPlay()
{
	Super::BeginPlay();

	// Overlapイベントのバインド
	SwitchCollision->OnComponentBeginOverlap.AddDynamic(this, &AStepOnSwitchGimmick::OnOverlapBegin);
}

void AStepOnSwitchGimmick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ドア開閉シーケンスの再生
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		if (ARoomBase* CurrentRoom = RoomManager->GetCurrentRoom())
		{
			CurrentRoom->PlayDoorOpenSequence();
		}
	}

	// 当たり判定の無効化
	SwitchCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
