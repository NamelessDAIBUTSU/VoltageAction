// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActorBase.h"
#include <Components/BoxComponent.h>
#include <ActorComponent/AttackComponent.h>


// Sets default values
AWeaponActorBase::AWeaponActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// 武器メッシュの作成
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeaponActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (AttackCollision)
	{
		// 生成初期はコリジョンの当たり判定を無効にする
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// オーバーラップイベント
		AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttackCollisionOverlapBegin);
	}
}

// Called every frame
void AWeaponActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 攻撃用コリジョンの有効/無効化
void AWeaponActorBase::SetAttackCollision(bool flag)
{
	if (AttackCollision)
	{
		ECollisionEnabled::Type EnabledType = flag ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
		AttackCollision->SetCollisionEnabled(EnabledType);
	}
}

// 攻撃用コリジョンオーバーラップ時イベント
void AWeaponActorBase::OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Owner)
	{
		// 自身の攻撃コンポーネントを取得
		UAttackComponent* AttackComp = Owner->FindComponentByClass<UAttackComponent>();

		// 攻撃ヒットを処理
		if (AttackComp)
		{
			AttackComp->HandleAttackHit(OtherActor);

			// 多重ヒットを防ぐためにコリジョンを無効化
			SetAttackCollision(false);
		}
	}
}
