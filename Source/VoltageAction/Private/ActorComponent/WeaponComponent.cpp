// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/WeaponComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner == nullptr)
		return;

	// 初期武器の生成
	if (InitWeaponActorClass)
	{
		// 生成
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Owner;
		AWeaponActorBase* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActorBase>(InitWeaponActorClass, SpawnParams);

		if (SpawnedWeapon)
		{
			// 装備
			SetWeapon(SpawnedWeapon);

			// 所有者のソケットに装着
			USkeletalMeshComponent* MeshComp = Owner->GetMesh();
			if (MeshComp)
			{
				FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
				SpawnedWeapon->AttachToComponent(MeshComp, AttachRules, SpawnedWeapon->GetAttachSocketName());
			}
		}
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

