// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Warrior/WarriorEnemy.h"
#include "Components/StaticMeshComponent.h"
#include <Player/PlayerCharacter.h>
#include <Components/BoxComponent.h>
#include <ActorComponent/DodgeComponent.h>
#include <ActorComponent/CombatComponent.h>
#include "ActorComponent/WeaponComponent.h"
#include "ActorComponent/AttackComponent.h"

AWarriorEnemy::AWarriorEnemy()
{
}

void AWarriorEnemy::OnConstruction(const FTransform& Transform)
{
}

void AWarriorEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
