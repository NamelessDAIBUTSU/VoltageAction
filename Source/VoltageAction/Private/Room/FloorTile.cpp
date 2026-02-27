// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/Tile/FloorTile.h"
#include <Room/RoomDef.h>

AFloorTile::AFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Cubeメッシュを割り当て
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube")
	);
}

void AFloorTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
