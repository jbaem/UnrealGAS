#include "GAS/ResourceAttributeSet.h"

#include "GameplayEffectExtension.h"

UResourceAttributeSet::UResourceAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(100.0f);

	InitMaxMana(100.0f);
	InitMana(100.0f);
}

void UResourceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	if(Attribute == GetMaxHealthAttribute())
	{
		// Set current health to new max health if it is greater than new max health
		// NOTE: level up scenario
		//if (NewValue > GetMaxHealth())
		//{
		//	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		//	ASC->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		//}
		NewValue = FMath::Max(NewValue, 1.0f);
	}

	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UResourceAttributeSet::PostAttributeChange(const FGameplayAttribute & Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if(Attribute == GetMaxHealthAttribute())
	{
		if (OldValue < NewValue)
		{
			SetHealth(GetHealth() + (NewValue - OldValue));
		}
		else if (GetHealth() > NewValue)
		{
			SetHealth(NewValue);
		}
	}

	if(Attribute == GetMaxManaAttribute())
	{
		if (OldValue < NewValue)
		{
			SetMana(GetMana() + (NewValue - OldValue));
		}
		else if (GetMana() > NewValue)
		{
			SetMana(NewValue);
		}
	}
}

void UResourceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// Called after a gameplay effect has been executed that modifies an attribute's base value
	// Note: This is only called for 'execute' type modifications, not for duration based effects
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if(GetHealth() <= 0.0f)
		{
			// TODO: Handle death
		}
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (GetMana() <= 0.0f)
		{
			// TODO: Handle out of mana
		}
	}
}
