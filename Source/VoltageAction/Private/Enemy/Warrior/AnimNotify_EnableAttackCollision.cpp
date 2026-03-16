// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Warrior/AnimNotify_EnableAttackCollision.h"
#include <Enemy/Warrior/WarriorEnemy.h>
#include <ActorComponent/WeaponComponent.h>

void UAnimNotify_EnableAttackCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 攻撃コリジョンの有効/無効化
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
		return;

	// 武器の取得
	UWeaponComponent* EquipComp = Owner->FindComponentByClass<UWeaponComponent>();
	if (EquipComp == nullptr)
		return;

	// 攻撃用コリジョンの有効/無効化
	if (AWeaponActorBase* Weapon = EquipComp->GetWeapon())
	{
		Weapon->SetAttackCollision(bIsEnabled);
	}
}
