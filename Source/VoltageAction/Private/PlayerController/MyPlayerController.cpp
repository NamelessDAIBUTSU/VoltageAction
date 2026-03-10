
#include "PlayerController/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Player/PlayerCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <ActorComponent/DodgeComponent.h>
#include <UI/UIManager.h>
#include <UI/HUDCanvasWidget.h>
#include <ActorComponent/HealthComponent.h>
#include <ActorComponent/CombatComponent.h>
#include <ActorComponent/AttackComponent.h>
#include <ActorComponent/ParryComponent.h>
#include <ActorComponent/WeaponComponent.h>
#include <Weapon/WeaponActorBase.h>

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 最初は本体用コンテキストを登録
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC_PlayerCharacter, 0);
	}
}

// プレイヤーが生成された後の初期化処理
void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// UIの初期化
	InitializeUI(aPawn);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 関数のバインド
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		EIC->BindAction(IA_Mouse, ETriggerEvent::Triggered, this, &AMyPlayerController::RotateCamera);
		EIC->BindAction(IA_Dodge, ETriggerEvent::Started, this, &AMyPlayerController::Dodge);
		EIC->BindAction(IA_LightAttack, ETriggerEvent::Started, this, &AMyPlayerController::LightAttack);
		EIC->BindAction(IA_HeavyAttack, ETriggerEvent::Started, this, &AMyPlayerController::HeavyAttack);
		EIC->BindAction(IA_Parry, ETriggerEvent::Started, this, &AMyPlayerController::Parry);
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// 移動を試す
	PlayerCharacter->TryMove(Value);
}

// カメラ回転
void AMyPlayerController::RotateCamera(const FInputActionValue& Value)
{
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// カメラ回転処理
	PlayerCharacter->RotateCamera(Value);
}

void AMyPlayerController::Dodge()
{
	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// 回避アクションを試す
	if (UDodgeComponent* DodgeComp = PlayerCharacter->FindComponentByClass<UDodgeComponent>())
	{
		DodgeComp->TryDodge();
	}
}

void AMyPlayerController::LightAttack()
{
	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// 攻撃用のコンポーネントを取得
	UAttackComponent* AttackComp = PlayerCharacter->FindComponentByClass<UAttackComponent>();
	if (AttackComp == nullptr)
		return;

	// 武器コンポーネントから武器の取得
	if (UWeaponComponent* WeaponComp = PlayerCharacter->FindComponentByClass<UWeaponComponent>())
	{
		if (AWeaponActorBase* Weapon = WeaponComp->GetWeapon())
		{
			// 弱攻撃コンボデータを取得
			UComboDataAsset* LightComboData = Weapon->GetLightComboData();

			// 攻撃を試みる
			AttackComp->TryAttack(LightComboData);
		}
	}
}

void AMyPlayerController::HeavyAttack()
{
	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// 攻撃用のコンポーネントを取得
	UAttackComponent* AttackComp = PlayerCharacter->FindComponentByClass<UAttackComponent>();
	if (AttackComp == nullptr)
		return;


	// 武器コンポーネントから武器の取得
	if (UWeaponComponent* WeaponComp = PlayerCharacter->FindComponentByClass<UWeaponComponent>())
	{
		if (AWeaponActorBase* Weapon = WeaponComp->GetWeapon())
		{
			// 強攻撃コンボデータを取得
			UComboDataAsset* HeavyComboData = Weapon->GetHeavyComboData();
			
			// 攻撃を試みる
			AttackComp->TryAttack(HeavyComboData);
		}
	}
}

void AMyPlayerController::Parry()
{
	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	// パリィアクション
	if (UParryComponent* ParryComp = PlayerCharacter->FindComponentByClass<UParryComponent>())
	{
		ParryComp->TryParry();
	}
}

APlayerCharacter* AMyPlayerController::GetPlayerCharacter() const
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	return PlayerCharacter;
}

// プレイヤーが必要なUI初期化
void AMyPlayerController::InitializeUI(APawn* aPawn)
{
	if (aPawn == nullptr)
		return;

	// UIManagerの生成
	UIManager = NewObject<UUIManager>(this, UUIManager::StaticClass());
	if (UIManager == nullptr)
		return;

	// UIManagerの初期化
	UIManager->Initialize();

	// メインキャンバスの生成
	CreateHUDCanvasWidget();

	// プレイヤー情報が必要なUIの初期化
	InitializeUIWithPlayer(aPawn);
}

// プレイヤー情報が必要なUI初期化
void AMyPlayerController::InitializeUIWithPlayer(APawn* aPawn)
{
	// HPバーの初期化
	InitializeHPBarIWidget(aPawn);

	// ボルテージゲージの初期化
	InitializeVoltageGaugeWidget(aPawn);
}

// HPバーの初期化
void AMyPlayerController::InitializeHPBarIWidget(APawn* aPawn)
{
	if (aPawn == nullptr || UIManager == nullptr)
		return;

	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	if (UHealthComponent* HPComp = PlayerCharacter->FindComponentByClass<UHealthComponent>())
	{
		UIManager->InitializePlayerHPBarWidget(HPComp);
	}
}
// ボルテージゲージの初期化
void AMyPlayerController::InitializeVoltageGaugeWidget(APawn* aPawn)
{
	if (aPawn == nullptr || UIManager == nullptr)
		return;

	// プレイヤーの取得
	APlayerCharacter* PlayerCharacter = GetPlayerCharacter();
	if (PlayerCharacter == nullptr)
		return;

	if (UHealthComponent* HPComp = PlayerCharacter->FindComponentByClass<UHealthComponent>())
	{
		UIManager->InitializeVoltageGaugeWidget(HPComp);
	}
}

// メインキャンバスの生成
void AMyPlayerController::CreateHUDCanvasWidget()
{
	if (UIManager == nullptr || HUDCanvasWidgetClass == nullptr)
		return;

	UHUDCanvasWidget* CanvasWidget = CreateWidget<UHUDCanvasWidget>(this, HUDCanvasWidgetClass);
	if (CanvasWidget)
	{
		// 初期化
		CanvasWidget->InitializeWidget();

		// 表示
		CanvasWidget->AddToViewport();

		// マネージャー管理下に設定
		UIManager->SetHUDCanvasWidget(CanvasWidget);
	}
}
