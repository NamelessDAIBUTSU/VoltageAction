// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Warrior/WarriorMonster.h"
#include "Components/StaticMeshComponent.h"
#include <Player/PlayerCharacter.h>
#include <Components/BoxComponent.h>
#include <ActorComponent/DodgeComponent.h>
#include <ActorComponent/CombatComponent.h>
#include "ActorComponent/WeaponComponent.h"
#include "ActorComponent/AttackComponent.h"

AWarriorMonster::AWarriorMonster()
{

}

void AWarriorMonster::OnConstruction(const FTransform& Transform)
{
}

void AWarriorMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
