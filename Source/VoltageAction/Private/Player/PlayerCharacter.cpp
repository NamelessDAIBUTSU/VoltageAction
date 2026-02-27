// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponent/DodgeComponent.h"
#include "ActorComponent/CombatComponent.h"
#include "ActorComponent/HealthComponent.h"
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
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// イベントのバインド
	// ジャスト回避
	if (UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>())
	{
		if (DodgeComp)
		{
			DodgeComp->OnJustDodgeDelegate.AddUObject(VoltageManager, &UVoltageManager::ApplyJustDodge);
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

void APlayerCharacter::RotateCamera(FVector2D RotateVec)
{
	if (IsValid(SpringArmComp) == false)
		return;

	if (RotateVec.X != 0.f)
	{
		float XRotateSpeed = RotateVec.X < 0.f ? CameraXRotateSpeed * -1.f : CameraXRotateSpeed;
		AddControllerYawInput(XRotateSpeed);
	}
	if (RotateVec.Y != 0.f)
	{
		float YRotateSpeed = RotateVec.Y < 0.f ? CameraYRotateSpeed * -1.f : CameraYRotateSpeed;
		AddControllerPitchInput(YRotateSpeed);
	}
}
