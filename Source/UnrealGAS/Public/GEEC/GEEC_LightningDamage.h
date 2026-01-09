#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "GEEC_LightningDamage.generated.h"

UCLASS()
class UNREALGAS_API UGEEC_LightningDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_LightningDamage();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float MinimumDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float DamageMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	TObjectPtr<UCurveTable> DamageTable = nullptr;

private:
	FGameplayTag Tag_DebuffShock;
	FGameplayTag Tag_ElementLightning;
};
