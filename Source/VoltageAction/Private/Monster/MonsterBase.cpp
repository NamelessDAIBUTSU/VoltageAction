// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"
#include <PlayerController/MyPlayerController.h>
#include <UI/UIManager.h>
#include <ActorComponent/HealthComponent.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/EnemyAttackComponent.h>
#include <ActorComponent/WeaponComponent.h>

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 戦闘コンポーネントとHPコンポーネントの作成
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	AttackComp = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttackComp"));
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 生成後、敵HPバーウィジェットの初期化をする
	InitializeEnemyHPBarWidget();
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 与えるダメージを取得
float AMonsterBase::GetFinalDamage()
{
	if (AttackComp == nullptr)
		return 0.f;

	// 敵のベースダメージ × 現在の攻撃データの割合


	return 0.f;
}

void AMonsterBase::InitializeEnemyHPBarWidget()
{
	// プレイヤーコントローラーの取得
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC == nullptr)
		return;

	// UIマネージャーの取得
	if (UUIManager* UIManager = PC->GetUIManager())
	{
		UIManager->InitializeEnemyHPBarWidget(HPComp);
	}
}


