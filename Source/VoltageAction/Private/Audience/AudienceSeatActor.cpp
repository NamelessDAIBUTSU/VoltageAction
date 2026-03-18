// Fill out your copyright notice in the Description page of Project Settings.


#include "Audience/AudienceSeatActor.h"

AAudienceSeatActor::AAudienceSeatActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// 床メッシュの作成
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(RootComponent);

	// 階段メッシュの生成
	FirstStairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstStairMesh"));
	FirstStairMesh->SetupAttachment(RootComponent);
	SecondStairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondStairMesh"));
	SecondStairMesh->SetupAttachment(RootComponent);
	ThirdStairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdStairMesh"));
	ThirdStairMesh->SetupAttachment(RootComponent);
}

void AAudienceSeatActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAudienceSeatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

