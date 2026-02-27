// Fill out your copyright notice in the Description page of Project Settings.

#include "Room/RoomBase.h"
#include <Kismet/GameplayStatics.h>
#include <Room/RoomManager.h>
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include <Player/PlayerCharacter.h>
#include <GameFramework/CharacterMovementComponent.h>

ARoomBase::ARoomBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 部屋の原点を設定
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));

}

void ARoomBase::BeginPlay()
{
	Super::BeginPlay();

	// ルームマネージャーに登録
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		RoomManager->AddRoom(this);
	}

	InitializeRoom();
}

void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 初期化処理
void ARoomBase::InitializeRoom()
{
	PlaySequenceImpl(LSA_Entry);
}

// リスポーン地点の取得
FVector ARoomBase::GetRespawnLocation() const 
{
	return IsValid(RespawnPoint) ? RespawnPoint->GetActorLocation() : FVector();
}

void ARoomBase::AddFloorTile(AFloorTile* Tile)
{
	FloorTiles.Add(Tile);
}

void ARoomBase::AddWallTile(AWallTile* Tile)
{
	WallTiles.Add(Tile);
}

void ARoomBase::AddRoofTile(AFloorTile* Tile)
{
	RoofTiles.Add(Tile);
}

// シーケンスの再生
void ARoomBase::PlaySequenceImpl(ALevelSequenceActor* LSA)
{
	if (IsValid(LSA) && IsValid(LSA->SequencePlayer))
	{
		LSA->SequencePlayer->Play();
	}
}
// シーケンスの停止
void ARoomBase::StopSequenceImpl(ALevelSequenceActor* LSA)
{
	if (IsValid(LSA) && IsValid(LSA->SequencePlayer))
	{
		LSA->SequencePlayer->Stop();
	}
}

// ドア開閉シーケンスの再生
void ARoomBase::PlayDoorOpenSequence()
{
	PlaySequenceImpl(LSA_DoorOpen);
}

// 落下シーケンスの再生
void ARoomBase::PlayFallSequence()
{
	PlaySequenceImpl(LSA_Fall);
}

void ARoomBase::PlayClearSequence()
{
	PlaySequenceImpl(LSA_Clear);
}

// 開始演出シーケンスの停止
void ARoomBase::StopEntrySequence()
{
	StopSequenceImpl(LSA_Entry);
}

// プレイヤーをリスポーンさせる
void ARoomBase::OnRespawnPlayer()
{
	// プレイヤーの取得
	APlayerCharacter* PlayerBody = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerBody == nullptr)
		return;


	// 落下したプレイヤーを復活ポイントに戻す
	PlayerBody->SetActorLocation(GetRespawnLocation());

	// プレイヤーに固定落下ダメージを与える

}

void ARoomBase::OnEntryPlayer()
{
	// 到達したなら更新停止
	if (bIsEntried)		
		return;

	// プレイヤーの取得
	APlayerCharacter* PlayerBody = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerBody == nullptr)
		return;

	UCharacterMovementComponent* CharacterMovement = PlayerBody->GetCharacterMovement();
	if (CharacterMovement == nullptr)
		return;

	// プレイヤーを初期位置に移動させる
	FVector MoveDirection = GetRespawnLocation() - PlayerBody->GetActorLocation();
	MoveDirection.Z = 0.f;
	MoveDirection.Normalize();
	CharacterMovement->AddInputVector(MoveDirection * EntryMoveSpeed, true);

	// 到達したら位置を補正
	if (PlayerBody->GetActorLocation().Equals(GetRespawnLocation(), 10.f))
	{
		PlayerBody->SetActorLocation(GetRespawnLocation());
		bIsEntried = true;
	}
}

