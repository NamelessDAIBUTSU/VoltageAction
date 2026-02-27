// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/EntryTrigger.h"
#include "Components/BoxComponent.h"
#include <Player/PlayerCharacter.h>
#include <Room/RoomBase.h>
#include <Room/RoomManager.h>

// Sets default values
AEntryTrigger::AEntryTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
}

// Called when the game starts or when spawned
void AEntryTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEntryTrigger::OnOverlapBegin);
	}
}

// Called every frame
void AEntryTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEntryTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 開始演出を停止
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		if (ARoomBase* CurrentRoom = RoomManager->GetCurrentRoom())
		{
			CurrentRoom->StopEntrySequence();
		}
	}

	// 当たり判定を無効化
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

