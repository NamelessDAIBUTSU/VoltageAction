#pragma once

#include "CoreMinimal.h"
#include "AttackDef.generated.h"

// 受信した攻撃データ
USTRUCT()
struct FAttackData
{
	GENERATED_BODY()

public:
	float Damage = 0.f;
	// 攻撃されたアクター
	UPROPERTY()
	TWeakObjectPtr<AActor> DamagedActor = nullptr;
};

// 攻撃結果
UENUM()
enum class EAttackResult : uint8
{
	Hit			UMETA(DisplayName = "ヒット"),
	Guard		UMETA(DisplayName = "ガード"),
	Parry		UMETA(DisplayName = "パリィ"),
	JustDodge	UMETA(DisplayName = "ジャスト回避"),
	None		UMETA(DisplayName = "エラー値")
};