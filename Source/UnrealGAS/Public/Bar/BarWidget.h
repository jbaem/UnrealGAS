#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/Resource.h"

#include "BarWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class UNREALGAS_API UBarWidget : public UUserWidget, public IResource
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCurrent_Implementation(float Value) override;
	virtual void UpdateMax_Implementation(float Value) override;

	UFUNCTION(BlueprintCallable, Category = "PJB")
	void SetProgressBarColor(FLinearColor LinearColor);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BackgroundProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Current = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Max = nullptr;

private:
	float MaxValue = 1.0f;
};
