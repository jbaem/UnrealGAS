#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TestPC.generated.h"

class UInputMappingContext;

UCLASS()
class UNREALGAS_API ATestPC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;
};
