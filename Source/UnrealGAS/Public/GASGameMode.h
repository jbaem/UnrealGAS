#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GASGameMode.generated.h"

UCLASS(abstract)
class UNREALGAS_API AGASGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGASGameMode();
};
