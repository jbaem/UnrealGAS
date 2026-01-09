#include "GC/GCNS_Test.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

UGCNS_Test::UGCNS_Test()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Test"));
}

bool UGCNS_Test::OnExecute_Implementation(AActor * MyTarget, const FGameplayCueParameters & Parameters) const
{
	UE_LOG(LogTemp, Warning, TEXT("UGCNS_Test::OnExecute_Implementation called"));
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning TestVFX at target location"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			MyTarget->GetWorld(),
			BurstVFX,
			MyTarget->GetActorLocation(),
			MyTarget->GetActorRotation()
		);
		return true;
	}
	return false;
}
