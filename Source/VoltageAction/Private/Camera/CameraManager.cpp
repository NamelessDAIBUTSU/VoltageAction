// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraManager.h"
#include "Camera/IngameCameraBase.h"
#include <Room/RoomManager.h>

UCameraManager::UCameraManager()
	: CurrentCamera(nullptr)
{

}

// 初期化
void UCameraManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CurrentCamera = nullptr;
	CameraList.Empty();

	// RoomManagerに依存しているため、RoomManagerを先に初期化
	Collection.InitializeDependency<URoomManager>();
}

// カメラの登録
void UCameraManager::RegisterCamera(AIngameCameraBase* NewCamera)
{
	if (NewCamera && CameraList.Contains(NewCamera) == false)
	{
		CameraList.Add(NewCamera);
	}
}
// カメラの登録解除
void UCameraManager::UnregisterCamera(AIngameCameraBase* RemoveCamera)
{
	if (RemoveCamera)
	{
		// 解除
		CameraList.Remove(RemoveCamera);

		// 現在のカメラが解除された場合、リストの先頭のカメラに切り替え
		if (CurrentCamera == RemoveCamera)
		{
			CurrentCamera = CameraList.IsEmpty() == false ? CameraList[0] : nullptr;
		}
	}
}

// カメラの取得
AIngameCameraBase* UCameraManager::GetCamera(ECameraChannel Cannel)
{
	// 登録されたカメラの中から指定されたチャンネルのカメラを探す
	for (AIngameCameraBase* Camera : CameraList)
	{
		if (Camera && Camera->GetCameraChannel() == Cannel)
		{
			return Camera;
		}
	}

	return nullptr;
}

// 現在のカメラを取得
AIngameCameraBase* UCameraManager::GetCurrentCamera() const
{
	return CurrentCamera.Get();
}
// 現在のカメラを設定
void UCameraManager::SetCurrentCamera(AIngameCameraBase* NewCamera)
{
	CurrentCamera = NewCamera;
}

// 登録されたカメラのリストを取得
const TArray<AIngameCameraBase*>& UCameraManager::GetCameraList() const
{
	return CameraList;
}




