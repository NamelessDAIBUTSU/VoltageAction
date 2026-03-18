// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponent/DodgeComponent.h"
#include "ActorComponent/CombatComponent.h"
#include "ActorComponent/HealthComponent.h"
#include "ActorComponent/WeaponComponent.h"
#include "ActorComponent/PlayerAttackComponent.h"
#include "ActorComponent/ParryComponent.h"
#include <Voltage/VoltageManager.h>
#include <Attack/ComboDataAsset.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	if (UCharacterMovementComponent* CharaMoveComp = GetCharacterMovement())
	{
		CharaMoveComp->bOrientRotationToMovement = true;
		CharaMoveComp->bConstrainToPlane = true;
		CharaMoveComp->bSnapToPlaneAtStart = true;

		CharaMoveComp->RotationRate.Yaw = 1800.f;
	}

	// Create a camera boom...
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// コンポーネントの作成
	DodgeComp = CreateDefaultSubobject<UDodgeComponent>(TEXT("DodgeComp"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
	AttackComp = CreateDefaultSubobject<UPlayerAttackComponent>(TEXT("AttackComp"));
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
	ParryComp = CreateDefaultSubobject<UParryComponent>(TEXT("ParryComp"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// イベントのバインド
	BindEvents();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// 与えるダメージを取得
float APlayerCharacter::GetFinalDamage()
{
	if (WeaponComp == nullptr || AttackComp == nullptr)
		return 0.f;

	// 武器のベースダメージ × 現在の攻撃データの補正割合
	if (AWeaponActorBase* Weapon = WeaponComp->GetWeapon())
	{
		if (UAttackDataAsset* CurrentAttackData = AttackComp->GetCurrentAttackData())
		{
			return Weapon->GetBaseDamage() * CurrentAttackData->DamageMultiplier;
		}
	}

	return 0.f;
}

float APlayerCharacter::GetFinalPoiseDamage()
{
	if (WeaponComp == nullptr || AttackComp == nullptr)
		return 0.f;

	// 武器のベース耐久値ダメージ × 現在の攻撃データの補正割合
	if (AWeaponActorBase* Weapon = WeaponComp->GetWeapon())
	{
		if (UAttackDataAsset* CurrentAttackData = AttackComp->GetCurrentAttackData())
		{
			return Weapon->GetBasePoiseDamage() * CurrentAttackData->PoiseDamageMultiplier;
		}
	}

	return 0.f;
}

float APlayerCharacter::GetFinalBreakDamage()
{
	if (WeaponComp == nullptr || AttackComp == nullptr)
		return 0.f;

	// 武器のベースブレイクダメージ × 現在の攻撃データの補正割合
	if (AWeaponActorBase* Weapon = WeaponComp->GetWeapon())
	{
		if (UAttackDataAsset* CurrentAttackData = AttackComp->GetCurrentAttackData())
		{
			return Weapon->GetBaseBreakDamage() * CurrentAttackData->BreakDamageMultiplier;
		}
	}

	return 0.f;
}

// 移動
void APlayerCharacter::TryMove(const FInputActionValue& Value)
{
	if (PlayerState != EPlayerState::Idle)
		return;

	const FVector2D InputAxis = Value.Get<FVector2D>();

	// カメラ軸で移動
	FRotator CameraRot = GetControlRotation();
	// カメラの回転から前方向と右方向を計算
	FRotationMatrix CameraRotMat(CameraRot);
	FVector Forward = CameraRotMat.GetUnitAxis(EAxis::X);
	FVector Right = CameraRotMat.GetUnitAxis(EAxis::Y);

	// 移動
	AddMovementInput(Forward, InputAxis.X);
	AddMovementInput(Right, InputAxis.Y);
}

// カメラ回転
void APlayerCharacter::RotateCamera(const FInputActionValue& Value)
{
	if (IsValid(SpringArmComp) == false)
		return;

	const FVector2D InputAxis = Value.Get<FVector2D>();
	if (InputAxis.IsZero())
		return;

	if (InputAxis.X != 0.f)
	{
		//float XRotateSpeed = RotateVec.X < 0.f ? CameraXRotateSpeed * -1.f : CameraXRotateSpeed;
		float XRotateSpeed = InputAxis.X * CameraXRotateSpeed;
		AddControllerYawInput(XRotateSpeed);
	}
	if (InputAxis.Y != 0.f)
	{
		//float YRotateSpeed = RotateVec.Y < 0.f ? CameraYRotateSpeed * -1.f : CameraYRotateSpeed;
		float YRotateSpeed = InputAxis.Y * CameraYRotateSpeed;
		AddControllerPitchInput(YRotateSpeed);
	}
}

void APlayerCharacter::SetPlayerState(EPlayerState State)
{
	PlayerState = State;
}

// イベントのバインド
void APlayerCharacter::BindEvents()
{
	if (UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>())
	{
		if (DodgeComp)
		{
			// ジャスト回避成功：ボルテージ増加
			DodgeComp->OnJustDodgeDelegate.AddUObject(VoltageManager, &UVoltageManager::OnJustDodge);
			// ジャスト回避成功：無敵状態の開始
			if (CombatComp)
			{
				DodgeComp->OnJustDodgeDelegate.AddUObject(CombatComp, &UCombatComponent::OnStartInvincible);
			}
		}

		if (HPComp)
		{
			// 被ダメージ：ボルテージ増加、アニメーション再生
			HPComp->OnDamagedDelegate.AddUObject(VoltageManager, &UVoltageManager::OnTakeDamage);
			HPComp->OnDamagedDelegate.AddUObject(this, &ThisClass::OnPlayHitAnim);

			// 死亡
			HPComp->OnDieDelegate.AddUObject(this, &ThisClass::OnDie);
		}

		if (ParryComp)
		{
			// パリィ成功
			ParryComp->OnParrySuccessDelegate.AddUObject(VoltageManager, &UVoltageManager::OnParrySuccess);
		}
	}
}

// 各種アニメーション再生
void APlayerCharacter::OnPlayHitAnim(const FAttackData& AttackData)
{
	if (HitReactMontage)
	{
		// 再生
		PlayAnimMontage(HitReactMontage);

		// ステートをHitに変更
		PlayerState = EPlayerState::Hit;

		// アニメーション終了時にIdleに戻す
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			FOnMontageEnded OnMontageEndDelegate;
			OnMontageEndDelegate.BindLambda([this](UAnimMontage* Montage, bool bInterrupted)
				{
					PlayerState = EPlayerState::Idle;
				});
			AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, HitReactMontage);
		}
	}
}
void APlayerCharacter::OnDie()
{
	// ステートを変更
	PlayerState = EPlayerState::Dead;

	// モンタージュ再生
	if (DieMontage)
	{
		PlayAnimMontage(DieMontage);

		PlayerState = EPlayerState::Dead;
	}
}
