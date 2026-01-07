#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "StatusAttributeSet.generated.h"

// Attribute Set Macros
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

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
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "PJB|GAS|Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UStatusAttributeSet, MaxMana);
};
