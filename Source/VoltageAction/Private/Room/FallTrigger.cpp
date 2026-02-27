// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/FallTrigger.h"
#include "Components/BoxComponent.h"
#include <Player/PlayerCharacter.h>
#include <Room/RoomManager.h>
#include "Room/RoomBase.h"

// Sets default values
AFallTrigger::AFallTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
}

// Called when the game starts or when spawned
void AFallTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFallTrigger::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFallTrigger::OnOverlapEnd);
	}
}

// Called every frame
void AFallTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 落下時に落下用のカメラに切り替える
void AFallTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerBody = Cast<APlayerCharacter>(OtherActor);
	if (PlayerBody == nullptr)
		return;

	// 落下シーケンスの再生
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		if (ARoomBase* CurrentRoom = RoomManager->GetCurrentRoom())
		{
			CurrentRoom->PlayFallSequence();
		}
	}
}

// 落下終了時に、プレイヤーを元に戻す
void AFallTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerBody = Cast<APlayerCharacter>(OtherActor);
	if (PlayerBody == nullptr)
		return;



}