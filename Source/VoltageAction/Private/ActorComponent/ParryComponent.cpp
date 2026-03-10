// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/ParryComponent.h"

// Sets default values for this component's properties
UParryComponent::UParryComponent()
{
}


// Called when the game starts
void UParryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// パリィ処理
void UParryComponent::TryParry()
{
	// パリィモンタージュを再生
	if (ParryMontage)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			UAnimInstance* AnimInstance = Owner->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(ParryMontage);
			}
		}
	}
}

// パリィ成功時の処理
void UParryComponent::OnParrySuccess()
{
}

