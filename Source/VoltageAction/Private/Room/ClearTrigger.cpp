// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/ClearTrigger.h"
#include "Components/BoxComponent.h"
#include <Player/PlayerCharacter.h>
#include <Room/RoomManager.h>
#include "Room/RoomBase.h"

// Sets default values
AClearTrigger::AClearTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
}

// Called when the game starts or when spawned
void AClearTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AClearTrigger::OnOverlapBegin);
	}
}

// Called every frame
void AClearTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClearTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerBody = Cast<APlayerCharacter>(OtherActor);
	if (PlayerBody == nullptr)
		return;


	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		// 現在の部屋の終了処理
		if (ARoomBase* CurrentRoom = RoomManager->GetCurrentRoom())
		{
			// 現在の部屋の終了処理
			CurrentRoom->FinalizeRoom();

			// クリア演出再生
			CurrentRoom->PlayClearSequence();
		}

		// 次の部屋の初期化処理
		if (ARoomBase* NextRoom = RoomManager->GetRoom(NextRoomID))
		{
			// 現在の部屋を更新
			RoomManager->SetCurrentRoom(NextRoom);
		}
	}

	// 当たり判定を無効化
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

