// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/Tile/GhostWallTile.h"

AGhostWallTile::AGhostWallTile()
{
}

void AGhostWallTile::BeginPlay()
{
	Super::BeginPlay();

	// ゴーストウォールはゴーストとアストラルが通れるように無視設定にする
	if (BoxComp)
	{
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	}
}
