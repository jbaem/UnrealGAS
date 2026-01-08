#pragma once

#include "CoreMinimal.h"
#include "TestZone/TestZone.h"

#include "ManaDrainZone.generated.h"

UCLASS()
class UNREALGAS_API AManaDrainZone : public ATestZone
{
	GENERATED_BODY()

public:
	AManaDrainZone();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PJB|Test")
	TSubclassOf<class UGameplayEffect> ManaDrainEffectClass = nullptr;

protected:
	virtual void ApplyZoneEffect(class UAbilitySystemComponent* ASC) override;
};
