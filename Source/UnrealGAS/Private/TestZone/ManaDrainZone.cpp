#include "TestZone/ManaDrainZone.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AManaDrainZone::AManaDrainZone()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AManaDrainZone::BeginPlay()
{
	Super::BeginPlay();
}

void AManaDrainZone::ApplyZoneEffect(UAbilitySystemComponent* ASC)
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddInstigator(this, this);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ManaDrainEffectClass, 1.f, EffectContext);
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (ActiveGEHandle.IsValid())
		{
			ActiveEffectHandle[ASC] = ActiveGEHandle;
		}
	}
}
