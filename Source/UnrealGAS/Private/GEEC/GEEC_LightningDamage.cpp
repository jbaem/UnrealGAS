#include "GEEC/GEEC_LightningDamage.h"

#include "GAS/ResourceAttributeSet.h"
#include "GAS/StatusAttributeSet.h"

struct FLightningDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalRate);

	FLightningDamageStatics()
	{
		// capture from target, do not snapshot
		DEFINE_ATTRIBUTE_CAPTUREDEF(UResourceAttributeSet, Health, Target, false);
		// capture from source, snapshot
		DEFINE_ATTRIBUTE_CAPTUREDEF(UStatusAttributeSet, AttackPower, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UStatusAttributeSet, CriticalRate, Source, true);
	}
};

static FLightningDamageStatics& LightningDamageStatics()
{
	static FLightningDamageStatics Statics;
	return Statics;
}


UGEEC_LightningDamage::UGEEC_LightningDamage()
{
	RelevantAttributesToCapture.Add(LightningDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(LightningDamageStatics().AttackPowerDef);
	RelevantAttributesToCapture.Add(LightningDamageStatics().CriticalRateDef);

	Tag_DebuffShock = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Shock"));
	Tag_ElementLightning = FGameplayTag::RequestGameplayTag(FName("Element.Lightning"));
}

void UGEEC_LightningDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

		float Damage = MinimumDamage;
		float Multiplier = DamageMultiplier;

		if (DamageTable)
		{
			float EffectLevel = Spec.GetLevel();
			FRealCurve* DamageCurve = DamageTable->FindCurve(FName("Damage"), TEXT("UUGEEC_LightningDamage"));
			if (DamageCurve)
			{
				Damage = DamageCurve->Eval(EffectLevel);
			}
			FRealCurve* MultiplierCurve = DamageTable->FindCurve(FName("Multiplier"), TEXT("UUGEEC_LightningDamage"));
			if (MultiplierCurve)
			{
				Multiplier = MultiplierCurve->Eval(EffectLevel);
			}
		}

		FAggregatorEvaluateParameters EvaluateParameters;
		EvaluateParameters.SourceTags = SourceTags;
		EvaluateParameters.TargetTags = TargetTags;
		float AttackPower = 0.0f;
		bool Result = ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			LightningDamageStatics().AttackPowerDef,
			EvaluateParameters,
			AttackPower
		);
		if (Result)
		{
			Damage += AttackPower;
		}
		else
		{
			// Cannot get AttackPower attribute, use default Damage value
		}

		float CriticalRate = 0.0f;
		Result = ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			LightningDamageStatics().CriticalRateDef,
			EvaluateParameters,
			CriticalRate
		);
		if (Result)
		{
			if (FMath::FRand() <= CriticalRate)
			{
				Damage *= 2.0f;
			}
		}
		else
		{
			// Cannot get CriticalRate attribute, skip critical hit check
		}

		if (SourceTags && SourceTags->HasTag(Tag_ElementLightning)
			&& TargetTags && TargetTags->HasTag(Tag_DebuffShock))
		{
			Damage *= Multiplier;
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					LightningDamageStatics().HealthProperty,
					EGameplayModOp::Additive,
					-Damage
				)
			);
		}
	}
}
