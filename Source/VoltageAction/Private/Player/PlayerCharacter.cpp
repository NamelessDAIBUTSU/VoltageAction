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
#include "ActorComponent/AttackComponent.h"
#include <Voltage/VoltageManager.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// コンポーネントの作成
	DodgeComp = CreateDefaultSubobject<UDodgeComponent>(TEXT("Dodge"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack"));
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// イベントのバインド
	if (UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>())
	{
		// ジャスト回避
		if (DodgeComp)
		{
			// ボルテージ増加
			DodgeComp->OnJustDodgeDelegate.AddUObject(VoltageManager, &UVoltageManager::OnJustDodge);

			// 無敵状態の開始
			if (CombatComp)
			{
				DodgeComp->OnJustDodgeDelegate.AddUObject(CombatComp, &UCombatComponent::OnStartInvincible);
			}
		}

		if (HPComp)
		{
			// 被ダメージ
			HPComp->OnDamagedDelegate.AddUObject(VoltageManager, &UVoltageManager::OnTakeDamage);

			// 死亡
			//HPComp->OnDeathDelegate.AddUObject(, &::);
		}
	}

	// 武器の生成
	if (WeaponActorClass)
	{
		if (WeaponComp)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			AWeaponActorBase* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActorBase>(WeaponActorClass, SpawnParams);
			if (SpawnedWeapon)
			{
				WeaponComp->SetWeapon(SpawnedWeapon);
			}

			// 武器をソケットに装着
			USkeletalMeshComponent* MeshComp = GetMesh();
			if (MeshComp && SpawnedWeapon)
			{
				FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
				SpawnedWeapon->AttachToComponent(MeshComp, AttachRules, SpawnedWeapon->GetAttachSocketName());
			}
		}
	}
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

// 攻撃を受信
EAttackResult APlayerCharacter::ReceiveAttack(const FAttackData& AttackData)
{
	// 戦闘はCombatComponentに任せる
	if (CombatComp)
	{
		return CombatComp->ReceiveAttack(AttackData);
	}

	return EAttackResult::None;
}

// 移動
void APlayerCharacter::TryMove(const FInputActionValue& Value)
{
	// 攻撃中なら移動しない
	if (AttackComp && AttackComp->IsAttacking())
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
