#include "GC/GCNA_HitTest.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_HitTest::AGCNA_HitTest()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.TestHit"));
	bAutoDestroyOnRemove = true;
}

bool AGCNA_HitTest::OnActive_Implementation(AActor * MyTarget, const FGameplayCueParameters & Parameters)
{
	if (SpawnedVFX.IsValid())		// 안전장치(혹시 만들어진게 있으면 제거하고 진행하라)
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}

	if (MyTarget)
	{
		// Need to include effect context hit result when applying this gameplay cue
		const FHitResult* HitResult = Parameters.EffectContext.Get()->GetHitResult();
		FRotator HitRotator = HitResult->ImpactNormal.Rotation();
		
		SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			TestVFX,
			HitResult->ImpactPoint,
			HitRotator
		);
		return true;
	}
	return false;
}

bool AGCNA_HitTest::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())		// 안전장치(혹시 만들어진게 있으면 제거하고 진행하라)
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
