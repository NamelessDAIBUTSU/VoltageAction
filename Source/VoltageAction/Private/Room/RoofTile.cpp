// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/Tile/RoofTile.h"

// Sets default values
ARoofTile::ARoofTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoofTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoofTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

