// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraDef.h"
#include "IngameCameraBase.generated.h"

/**
 * 
 */
UCLASS()
class VOLTAGEACTION_API AIngameCameraBase : public ACameraActor
{
	GENERATED_BODY()
	
public:
	AIngameCameraBase();

public:
	// カメラチャンネルの取得
	ECameraChannel GetCameraChannel() const { return CameraChannel; }

protected:
	// カメラチャンネル
	UPROPERTY(EditAnywhere, Category = "IngameCameraBase")
	ECameraChannel CameraChannel;
};
