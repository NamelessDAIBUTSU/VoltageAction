// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
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

public:
	// 本体用入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC_Body;
	// アストラル用入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC_Astral;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Dodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Mouse;
};
