#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "TwinResource.generated.h"

UINTERFACE(MinimalAPI)
class UTwinResource : public UInterface
{
	GENERATED_BODY()
};

class UNREALGAS_API ITwinResource
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentHealth(float Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxHealth(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentMana(float Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxMana(float Value);
};
