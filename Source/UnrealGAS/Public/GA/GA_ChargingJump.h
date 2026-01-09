#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "GA_ChargingJump.generated.h"

UCLASS()
class UNREALGAS_API UGA_ChargingJump : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_ChargingJump();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void InputReleased(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo
	) override;

protected:
	UFUNCTION()
	void UpdateChargingTime();

	void ExecuteSuperJump(const FGameplayAbilityActorInfo* ActorInfo);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability|ChargingJump")
	float MinJumpPower = 700.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability|ChargingJump")
	float MaxJumpPower = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability|ChargingJump")
	float MaxChargeTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PJB|Ability|ChargingJump")
	TSubclassOf<UGameplayEffect> ChargingEffectClass;

private:
	FActiveGameplayEffectHandle ChargingEffectHandle;
	FTimerHandle ChargingTimerHandle;
	float CurrentChargeTime = 0.0f;
	float ChargeTimeStep = 0.1f;
};
