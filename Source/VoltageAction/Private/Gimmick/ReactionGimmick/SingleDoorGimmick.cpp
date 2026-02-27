// Fill out your copyright notice in the Description page of Project Settings.

#include "Gimmick/ReactionGimmick/SingleDoorGimmick.h"

ASingleDoorGimmick::ASingleDoorGimmick()
{
	// 明示的に Tick を有効化（親が設定していても念のため）
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->SetupAttachment(RootComponent);

	// タイムラインの作成
	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenTimeline"));
}

void ASingleDoorGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASingleDoorGimmick::BeginPlay()
{
	Super::BeginPlay();

	// 初期位置の設定
	ClosedLocation = DoorMesh->GetRelativeLocation();

	// ドアの高さ分下へ移動した位置を開いた位置とする
	OpenedLocation = ClosedLocation + FVector(0.f, 0.f, DoorMesh->Bounds.GetBox().GetSize().Z * -1.f);

	// タイムラインの初期設定
	if (OpenTimeline)
	{
		OpenTimeline->PrimaryComponentTick.bCanEverTick = true;
		OpenTimeline->PrimaryComponentTick.bStartWithTickEnabled = true;

		// タイムラインにバインド
		if (OpenCurve)
		{
			FOnTimelineFloat UpdateFunc;
			UpdateFunc.BindUFunction(this, FName("OnTimelineUpdate"));

			OpenTimeline->AddInterpFloat(OpenCurve, UpdateFunc);
		}
	}
}

void ASingleDoorGimmick::ActivateGimmick()
{
	// タイムライン再生
	if (OpenTimeline)
	{
		OpenTimeline->PlayFromStart();
	}
}

void ASingleDoorGimmick::DeactivateGimmick()
{
	// タイムライン停止
	if (OpenTimeline)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	{
		OpenTimeline->Reverse();
	}
}

// タイムライン更新処理
void ASingleDoorGimmick::OnTimelineUpdate(float Value)
{
	FVector NewLocation = FMath::Lerp(ClosedLocation, OpenedLocation, Value);
	DoorMesh->SetRelativeLocation(NewLocation);
}
