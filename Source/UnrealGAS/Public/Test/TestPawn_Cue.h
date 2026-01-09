#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"

#include "TestPawn_Cue.generated.h"

UCLASS()
class UNREALGAS_API ATestPawn_Cue : public APawn
{
	GENERATED_BODY()

public:
	ATestPawn_Cue();

protected:
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return ASC; }

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;
};
