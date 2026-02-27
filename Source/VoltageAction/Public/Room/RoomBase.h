// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile/FloorTile.h"
#include "Tile/WallTile.h"
#include "Tile/RoofTile.h"
#include <Room/RoomDef.h>
#include "RoomBase.generated.h"

class ALevelSequenceActor;

UCLASS()
class VOLTAGEACTION_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoomBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 初期化処理
	virtual void InitializeRoom();
	// 終了処理
	virtual void FinalizeRoom() {}

public: /* シーケンス関連 */
	// ドア開閉シーケンスの再生
	void PlayDoorOpenSequence();
	// 落下シーケンスの再生
	void PlayFallSequence();
	// クリアシーケンスの再生
	void PlayClearSequence();

	// 開始演出シーケンスの停止
	void StopEntrySequence();

	// プレイヤーをリスポーンさせる
	UFUNCTION(BluePrintCallable)
	void OnRespawnPlayer();

	// プレイヤーを初期位置に移動させる
	UFUNCTION(BluePrintCallable)
	void OnEntryPlayer();

public:
	// 部屋ID
	int32 GetRoomID() const { return RoomID; }
	void SetRoomID(int32 Id) { RoomID = Id; }

	// リスポーン地点の取得
	FVector GetRespawnLocation() const;

	// 床タイルの追加
	void AddFloorTile(AFloorTile* Tile);
	// 壁タイルの追加
	void AddWallTile(AWallTile* Tile);
	// 天井タイルの追加
	void AddRoofTile(AFloorTile* Tile);

private:
	// シーケンスの再生
	void PlaySequenceImpl(ALevelSequenceActor* LSA);
	// シーケンスの停止
	void StopSequenceImpl(ALevelSequenceActor* LSA);

private: /* オブジェクト */
	// 床タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AFloorTile>> FloorTiles;
	// 壁タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AWallTile>> WallTiles;
	// 天井タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AFloorTile>> RoofTiles;

	// 部屋の状態
	UPROPERTY(VisibleAnywhere)
	ERoomState RoomState = ERoomState::InActive;

	// 部屋ID
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 RoomID = INDEX_NONE;

	// リスポーン地点
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> RespawnPoint;

private: /* シーケンス関連 */
	// レベルシーケンスアクター
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALevelSequenceActor> LSA_DoorOpen;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALevelSequenceActor> LSA_Fall;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALevelSequenceActor> LSA_Entry;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALevelSequenceActor> LSA_Clear;

	// エントリー演出フラグ
	bool bIsEntried = false;

	// 開始演出プレイヤーの移動速度
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float EntryMoveSpeed = 0.2f;
};
