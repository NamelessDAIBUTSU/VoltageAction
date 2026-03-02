// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActorBase.h"

// Sets default values
AWeaponActorBase::AWeaponActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 武器メッシュの作成
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

// Called when the game starts or when spawned
void AWeaponActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

