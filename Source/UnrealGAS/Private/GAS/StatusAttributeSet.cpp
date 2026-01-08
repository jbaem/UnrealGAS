#include "GAS/StatusAttributeSet.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusAttributeSet::UStatusAttributeSet()
{
	InitAttackPower(10.0f);
	InitMoveSpeed(500.0f);
	InitJumpPower(700.0f);
}

void UStatusAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UStatusAttributeSet::PostAttributeChange(const FGameplayAttribute & Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);

	if(Attribute == GetMoveSpeedAttribute())
	{
		AActor* OwningActor = GetOwningActor();
		ACharacter* OwningChar = Cast<ACharacter>(OwningActor);
		if(OwningChar)
		{
			OwningChar->GetCharacterMovement()->MaxWalkSpeed = NewValue;
		}
	}

	if(Attribute == GetJumpPowerAttribute())
	{
		AActor* OwningActor = GetOwningActor();
		ACharacter* OwningChar = Cast<ACharacter>(OwningActor);
		if(OwningChar)
		{
			OwningChar->GetCharacterMovement()->JumpZVelocity = NewValue;
		}
	}
}

void UStatusAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);
}
