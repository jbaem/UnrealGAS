#include "TestZone/DamageZone.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

ADamageZone::ADamageZone()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ADamageZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADamageZone::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnBeginOverlap(OverlappedActor, OtherActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (ASC)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddInstigator(this, this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			ActiveEffectHandle.Add(ASC, ActiveGEHandle);
		}
	}
}

void ADamageZone::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnEndOverlap(OverlappedActor, OtherActor);
}
