#pragma once

#include "CoreMinimal.h"
#include "TestZone/TestZone.h"

#include "DamageZone.generated.h"

UCLASS()
class UNREALGAS_API ADamageZone : public ATestZone
{
	GENERATED_BODY()
	
public:	
	ADamageZone();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PJB|Test")
	TSubclassOf<class UGameplayEffect> DamageEffectClass = nullptr;

protected:
	virtual void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
