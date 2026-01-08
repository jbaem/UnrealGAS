#include "Bar/BarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBarWidget::UpdateCurrent_Implementation(float Value)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	CurrentValue = Value;
	BackgroundProgressBar->SetPercent(ValuesToPercent());
}

void UBarWidget::UpdateMax_Implementation(float Value)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	MaxValue = Value;
	BackgroundProgressBar->SetPercent(ValuesToPercent());
}

void UBarWidget::SetProgressBarColor(FLinearColor LinearColor)
{
	BackgroundProgressBar->SetFillColorAndOpacity(LinearColor);
}

float UBarWidget::ValuesToPercent()
{
	return MaxValue > 0 ? CurrentValue / MaxValue : 0.0f;
}