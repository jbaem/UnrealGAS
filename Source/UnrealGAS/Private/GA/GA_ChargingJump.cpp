#include "GA/GA_ChargingJump.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UGA_ChargingJump::UGA_ChargingJump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_ChargingJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	CurrentChargeTime = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(
		ChargingTimerHandle, 
		this, 
		&UGA_ChargingJump::UpdateChargingTime, 
		ChargeTimeStep, 
		true
	);

	if (ChargingEffectClass && ActorInfo->AbilitySystemComponent.IsValid())
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
			ChargingEffectClass,
			GetAbilityLevel(),
			EffectContext
		);
		if(SpecHandle.IsValid())
		{
			ChargingEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

}

void UGA_ChargingJump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	ExecuteSuperJump(ActorInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_ChargingJump::UpdateChargingTime()
{
	CurrentChargeTime += ChargeTimeStep;
	if(CurrentChargeTime >= MaxChargeTime)
	{
		CurrentChargeTime = MaxChargeTime;
		GetWorld()->GetTimerManager().ClearTimer(ChargingTimerHandle);
	}
}

void UGA_ChargingJump::ExecuteSuperJump(const FGameplayAbilityActorInfo * ActorInfo)
{
	if(ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("ChargingJump: Executing Super Jump"));
		if(ChargingEffectClass && ActorInfo->AbilitySystemComponent.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("ChargingJump: Removing Charging Effect"));
			UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
			ASC->RemoveActiveGameplayEffect(ChargingEffectHandle);
		}

		ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
		if (Character)
		{
			float ChargeRatio = FMath::Clamp(CurrentChargeTime / MaxChargeTime, 0.0f, 1.0f);
			float JumpPower = FMath::Lerp(MinJumpPower, MaxJumpPower, ChargeRatio);
			
			UE_LOG(LogTemp, Log, TEXT("ChargingJump: ChargeRatio=%f, JumpPower=%f"), ChargeRatio, JumpPower);
			
			FVector Direction(1, 0, 1);
			Direction.Normalize();
			Direction = Character->GetActorRotation().RotateVector(Direction);
			Character->LaunchCharacter(Direction * JumpPower, false, false);
		}
	}
}
