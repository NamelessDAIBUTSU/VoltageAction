
#include "PlayerController/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Player/PlayerCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <ActorComponent/DodgeComponent.h>
#include <UI/UIManager.h>
#include <UI/HUDCanvasWidget.h>

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

	// UIの初期化
	InitializeUI();
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
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// Possessしているキャラクターを取得
	ACharacter* PossessCharacter = Cast<ACharacter>(GetPawn());
	if (PossessCharacter == nullptr)
		return;

	const FVector2D InputAxis = Value.Get<FVector2D>();

	// カメラ軸で移動
	// カメラの取得
	FRotator CameraRot = GetControlRotation();
	// カメラの回転から前方向と右方向を計算
	FRotationMatrix CameraRotMat(CameraRot);
	FVector Forward = CameraRotMat.GetUnitAxis(EAxis::X);
	FVector Right = CameraRotMat.GetUnitAxis(EAxis::Y);

	PossessCharacter->AddMovementInput(Forward, InputAxis.X);
	PossessCharacter->AddMovementInput(Right, InputAxis.Y);
}

// カメラ回転
void AMyPlayerController::RotateCamera(const FInputActionValue& Value)
{
	const FVector2D InputAxis = Value.Get<FVector2D>();
	if (InputAxis.IsZero())
		return;

	APlayerCharacter* Body = Cast<APlayerCharacter>(GetPawn());
	if (Body == nullptr)
		return;

	Body->RotateCamera(InputAxis);

	// ログ
	UE_LOG(LogTemp, Log, TEXT("Camera Rotated: %s"), *InputAxis.ToString());
}

void AMyPlayerController::Dodge()
{
	// 本体の取得
	APlayerCharacter* Body = Cast<APlayerCharacter>(GetPawn());
	if (Body == nullptr)
		return;

	// 回避アクション
	if (UDodgeComponent* DodgeComp = Body->FindComponentByClass<UDodgeComponent>())
	{
		DodgeComp->Dodge();
	}
}

// UI初期化
void AMyPlayerController::InitializeUI()
{
	// UIManagerの生成
	UIManager = NewObject<UUIManager>(this, UUIManager::StaticClass());
	if (UIManager == nullptr)
		return;

	// UIManagerの初期化
	UIManager->Initialize();

	// メインキャンバスの生成
	if (HUDCanvasWidgetClass)
	{
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
}
