// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UUIManager;
class UInputAction;

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
	// 弱攻撃
	UFUNCTION()
	void LightAttack();
	// 強攻撃
	UFUNCTION()
	void HeavyAttack();
	// パリィ
	UFUNCTION()
	void Parry();

	// UIManagerの取得
	UUIManager* GetUIManager() const { return UIManager; }

private:
	// プレイヤーの取得
	class APlayerCharacter* GetPlayerCharacter() const;

	// UI初期化
	void InitializeUI(APawn* aPawn);
	// プレイヤー情報が必要なUI初期化
	void InitializeUIWithPlayer(APawn* aPawn);
	// HPバーの初期化
	void InitializeHPBarIWidget(APawn* aPawn);
	// ボルテージゲージの初期化
	void InitializeVoltageGaugeWidget(APawn* aPawn);

	// メインキャンバスの生成
	void CreateHUDCanvasWidget();

private:
	// 入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> IMC_PlayerCharacter;
	
	// 入力アクション
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Dodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Mouse;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_LightAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_HeavyAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Parry;

	// 生成するHUDキャンバスクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHUDCanvasWidget> HUDCanvasWidgetClass;

	// UI管理用のManager
	UPROPERTY()
	TObjectPtr<UUIManager> UIManager = nullptr;
};
