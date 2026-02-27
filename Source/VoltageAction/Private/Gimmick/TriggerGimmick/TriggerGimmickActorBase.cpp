// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TriggerGimmick/TriggerGimmickActorBase.h"
#include "Gimmick/ReactionGimmick/ReactionGimmickActorBase.h"

void ATriggerGimmickActorBase::BeginPlay()
{
	Super::BeginPlay();

	for (AReactionGimmickActorBase* ReactionGimmick : TargetGimmicksInstance)
	{
		if (ReactionGimmick)
		{
			TargetGimmicks.Add(ReactionGimmick);
		}
	}
}
