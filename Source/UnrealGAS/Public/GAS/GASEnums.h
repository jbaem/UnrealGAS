#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	HASTE		UMETA(DisplayName = "Haste"),
	SUPERJUMP	UMETA(DisplayName = "Super Jump"),
	CHARGINGJUMP	UMETA(DisplayName = "Charging Jump"),
};
