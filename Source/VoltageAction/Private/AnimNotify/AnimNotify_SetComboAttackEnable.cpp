// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_SetComboAttackEnable.h"
#include <Player/PlayerCharacter.h>
#include <ActorComponent/AttackComponent.h>

void UAnimNotify_SetComboAttackEnable::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (Player == nullptr)
		return;

	UAttackComponent* AttackComp = Player->FindComponentByClass<UAttackComponent>();
	if (AttackComp == nullptr)
		return;

	AttackComp->SetCanCombo(true);
}
