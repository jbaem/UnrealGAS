#include "GAS/StatusAttributeSet.h"
#include "GameplayEffectExtension.h"

UStatusAttributeSet::UStatusAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(100.0f);
}

void UStatusAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth());
	}
}

void UStatusAttributeSet::PostAttributeChange(const FGameplayAttribute & Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

}

void UStatusAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if(GetHealth() <= 0.0f)
		{
			// TODO: Handle death
		}
	}
}
