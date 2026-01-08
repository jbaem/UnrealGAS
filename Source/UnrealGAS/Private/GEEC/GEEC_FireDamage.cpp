#include "GEEC/GEEC_FireDamage.h"

#include "GAS/ResourceAttributeSet.h"
#include "GAS/StatusAttributeSet.h"

struct FFireDamageStatics
{
	// capture definition: health attribute
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);

	FFireDamageStatics()
	{
		// capture health from target entity, do not snapshot
		DEFINE_ATTRIBUTE_CAPTUREDEF(UResourceAttributeSet, Health, Target, false);
		// capture attack power from source entity, snapshot
		DEFINE_ATTRIBUTE_CAPTUREDEF(UStatusAttributeSet, AttackPower, Source, true);
	}
};

static FFireDamageStatics& FireDamageStatics()
{
	static FFireDamageStatics Statics;
	return Statics;
}

UGEEC_FireDamage::UGEEC_FireDamage()
{
	// Specify the relevant attributes to capture
	RelevantAttributesToCapture.Add(FireDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(FireDamageStatics().AttackPowerDef);

	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("Status.Debuff.Burn"));
	Tag_ElementFire = FGameplayTag::RequestGameplayTag(FName("Element.Fire"));
	//Tag_EffectDamage = FGameplayTag::RequestGameplayTag(FName("Effect.Damage"));
}

void UGEEC_FireDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
		float Damage = MinimumDamage;

		if (DamageTable)
		{
			float EffectLevel = Spec.GetLevel();
			FRealCurve* DamageCurve = DamageTable->FindCurve(FName("Damage"), TEXT("UGEEC_FireDamage"));
			if (DamageCurve)
			{
				Damage = DamageCurve->Eval(EffectLevel);
			}
		}

		FAggregatorEvaluateParameters EvaluateParams;
		EvaluateParams.SourceTags = SourceTags;
		EvaluateParams.TargetTags = TargetTags;

		float AttackPower = 0.0f;
		bool Result = ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			FireDamageStatics().AttackPowerDef, 
			EvaluateParams, 
			AttackPower
		);

		if (Result)
		{
			Damage += AttackPower;
		}
		else
		{
			// Failed to get current health, use minimum damage
		}

		//// Set Damage from SetByCaller
		//float Damage = Spec.GetSetByCallerMagnitude(Tag_EffectDamage, false, 1.0f);
		//if (Damage <= MinimumDamage)
		//{
		//	Damage = MinimumDamage;
		//}

		if (SourceTags && SourceTags->HasTag(Tag_ElementFire)
			&& TargetTags && TargetTags->HasTag(Tag_DebuffBurn))
		{
			Damage *= DamageMultiplier;
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireDamageStatics().HealthProperty,
					EGameplayModOp::Additive,
					-Damage
				)
			);
		}
	}
}
