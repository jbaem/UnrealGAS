#include "GC/GCNA_Test.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_Test::AGCNA_Test()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Test2"));
	// Set to auto destroy on remove for testing
	bAutoDestroyOnRemove = true;
}

bool AGCNA_Test::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// for safety, deactivate any existing VFX
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}

	if (MyTarget)
	{
		SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			FountainVFX,
			MyTarget->GetActorLocation(),
			MyTarget->GetActorRotation()
		);
		return true;
	}
    return false;
}

bool AGCNA_Test::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
