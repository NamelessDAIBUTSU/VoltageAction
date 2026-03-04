// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UUIManager;

UCLASS()
class VOLTAGEACTION_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	// プレイヤーが生成された後の初期化処理
	virtual void OnPossess(APawn* aPawn) override;

	// 入力バインド設定
	virtual void SetupInputComponent() override;

public:
	// 移動
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	// カメラ回転
	UFUNCTION()
	void RotateCamera(const FInputActionValue& Value);

	// 避ける
	UFUNCTION()
	void Dodge();

	// UIManagerの取得
	UUIManager* GetUIManager() const { return UIManager; }

private:
	// UI初期化
	void InitializeUI();

	// HPバーの初期化を試みる
	void TryHPBarInitialize(APawn* aPawn);

public:
	// 入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC_PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Dodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Mouse;
	
private:
	// HUDキャンバスクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHUDCanvasWidget> HUDCanvasWidgetClass;

	// UI管理用のManager
	UPROPERTY()
	TObjectPtr<UUIManager> UIManager = nullptr;
};
