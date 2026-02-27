// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ReactionGimmick/DoubleDoorGimmick.h"

ADoubleDoorGimmick::ADoubleDoorGimmick()
{
	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorMesh"));
	LeftDoorMesh->SetupAttachment(RootComponent);
	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorMesh"));
	RightDoorMesh->SetupAttachment(RootComponent);
}

// ギミック起動
void ADoubleDoorGimmick::ActivateGimmick()
{

}
