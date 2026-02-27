// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"

AReactionGimmickActorBase::AReactionGimmickActorBase()
{
}

void AReactionGimmickActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AReactionGimmickActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// シーケンサーからギミック軌道するためのコールバック
void AReactionGimmickActorBase::OnSequenceActivate()
{
	ActivateGimmick();
}
