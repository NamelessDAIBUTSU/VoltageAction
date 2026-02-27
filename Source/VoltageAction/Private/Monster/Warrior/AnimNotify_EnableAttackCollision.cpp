// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Warrior/AnimNotify_EnableAttackCollision.h"
#include <Monster/Warrior/WarriorMonster.h>

void UAnimNotify_EnableAttackCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// コリジョンの有効化
	if (AWarriorMonster* Warrior = Cast<AWarriorMonster>(MeshComp->GetOwner()))
	{
		Warrior->SetAttackCollisionEnabled(true);
	}
}
