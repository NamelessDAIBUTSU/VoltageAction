// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include <PlayerController/MyPlayerController.h>
#include <UI/UIManager.h>
#include <ActorComponent/HealthComponent.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/EnemyAttackComponent.h>
#include <ActorComponent/WeaponComponent.h>
#include <ActorComponent/StaggerComponent.h>
#include "Attack/AttackDataAsset.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "AIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// コンポーネントの生成
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	AttackComp = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttackComp"));
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
	StaggerComp = CreateDefaultSubobject<UStaggerComponent>(TEXT("StaggerComp"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 生成後、敵HPバーウィジェットの初期化をする
	InitializeEnemyHPBarWidget();

	// イベントのバインド
	BindEvents();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::BindEvents()
{
	if (HPComp && StaggerComp)
	{
		// よろめきダメージイベント
		HPComp->OnDamagedDelegate.AddUObject(StaggerComp, &UStaggerComponent::OnTakeStaggerDamage);

		StaggerComp->OnStaggerDelegate.AddUObject(this, &ThisClass::OnSetStaggerType);
	}
}

// BehaviorTreeの停止
void AEnemyBase::OnSetStaggerType(EStaggerType Type)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController == nullptr)
		return;

	// BlackBoardを取得
	UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
	if (BBComp == nullptr)
		return;

	// BT停止用のフラグを立てる
	BBComp->SetValueAsEnum("StaggerType", static_cast<uint8>(Type));
}

// 与えるダメージを取得
float AEnemyBase::GetFinalDamage()
{
	if (AttackComp == nullptr)
		return 0.f;

	UAttackDataAsset* CurrentAttackData = AttackComp->GetCurrentAttackData();
	if (CurrentAttackData == nullptr)
		return 0.f;

	// 敵のベースダメージ × 現在の攻撃データの割合
	return AttackBaseDamage * CurrentAttackData->DamageMultiplier;
}

void AEnemyBase::InitializeEnemyHPBarWidget()
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
