#include "GA/GA_SuperJump.h"

#include "GameFramework/Character.h"

UGA_SuperJump::UGA_SuperJump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_SuperJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FVector Direction(1, 0, 1);
	Direction.Normalize();
	Direction = Character->GetActorRotation().RotateVector(Direction);
	Character->LaunchCharacter(Direction * JumpPower, false, false);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
