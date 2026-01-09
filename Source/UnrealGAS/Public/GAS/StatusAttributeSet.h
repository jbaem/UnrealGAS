#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GASMacros.h"

#include "StatusAttributeSet.generated.h"

UCLASS()
class UNREALGAS_API UStatusAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UStatusAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData CriticalRate;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, CriticalRate);
	
	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, MoveSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData JumpPower;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, JumpPower);
};
