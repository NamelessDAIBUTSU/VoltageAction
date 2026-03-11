// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOLTAGEACTION_API UParryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// パリィ処理
	void TryParry();

	// パリィ成功を通知
	void OnParrySuccess();

private:
	// パリィ終了時のイベント
	UFUNCTION()
	void OnParryMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	// パリィモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ParryMontage;

	// パリィモンタージュ終了時のデリゲート
	FOnMontageEnded OnMontageEndDelegate;
};
