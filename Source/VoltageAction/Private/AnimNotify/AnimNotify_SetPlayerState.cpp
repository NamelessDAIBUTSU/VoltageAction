// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_SetPlayerState.h"
#include <Player/PlayerCharacter.h>

void UAnimNotify_SetPlayerState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->SetPlayerState(NewState);
}
