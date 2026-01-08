#include "Bar/TwinBarWidget.h"

#include "Components/ProgressBar.h"
#include "Interface/Resource.h"

#include "Bar/BarWidget.h"

void UTwinBarWidget::NativeConstruct()
{
	SetProgressBarColor();
}

void UTwinBarWidget::UpdateCurrentHealth_Implementation(float Value)
{
	IResource::Execute_UpdateCurrent(Health.Get(), Value);
}

void UTwinBarWidget::UpdateMaxHealth_Implementation(float Value)
{
	IResource::Execute_UpdateMax(Health.Get(), Value);
}

void UTwinBarWidget::UpdateCurrentMana_Implementation(float Value)
{
	IResource::Execute_UpdateCurrent(Mana.Get(), Value);
}

void UTwinBarWidget::UpdateMaxMana_Implementation(float Value)
{
	IResource::Execute_UpdateMax(Mana.Get(), Value);
}

void UTwinBarWidget::SetProgressBarColor()
{
	Health->SetProgressBarColor(FLinearColor::Red);
	Mana->SetProgressBarColor(FLinearColor::Blue);
}
