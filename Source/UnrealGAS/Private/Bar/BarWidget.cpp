#include "Bar/BarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBarWidget::UpdateCurrent_Implementation(float Value)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	BackgroundProgressBar->SetPercent(MaxValue > 0 ? Value / MaxValue : 0.0f);
}

void UBarWidget::UpdateMax_Implementation(float Value)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	MaxValue = Value;
}

void UBarWidget::SetProgressBarColor(FLinearColor LinearColor)
{
	BackgroundProgressBar->SetFillColorAndOpacity(LinearColor);
}
