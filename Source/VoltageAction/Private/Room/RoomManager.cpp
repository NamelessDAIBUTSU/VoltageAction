#include "Room/RoomManager.h"
#include "Room/RoomBase.h"

URoomManager::URoomManager()
{
}

void URoomManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

// 部屋の追加
void URoomManager::AddRoom(ARoomBase* NewRoom)
{
	if (NewRoom == nullptr)
		return;

	Rooms.Add(NewRoom);

	// もしも初めての追加であれば、現在の部屋に設定する
	if (CurrentRoom == nullptr)
	{
		CurrentRoom = NewRoom;
	}
}

ARoomBase* URoomManager::GetRoom(int32 RoomID) const
{
	return nullptr;
}
