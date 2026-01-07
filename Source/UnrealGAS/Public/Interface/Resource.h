#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Resource.generated.h"

UINTERFACE(MinimalAPI)
class UResource : public UInterface
{
	GENERATED_BODY()
};

class UNREALGAS_API IResource
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrent(float Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMax(float Value);
};
