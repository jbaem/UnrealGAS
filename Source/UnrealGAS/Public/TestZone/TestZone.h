#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"

#include "TestZone.generated.h"

UCLASS()
class UNREALGAS_API ATestZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestZone();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> Collision;

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	virtual void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	TMap<class UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandle;
};
