#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/TwinResource.h"

#include "TwinBarWidget.generated.h"

UCLASS()
class UNREALGAS_API UTwinBarWidget : public UUserWidget, public ITwinResource
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	virtual void UpdateCurrentHealth_Implementation(float Value) override;
	virtual void UpdateMaxHealth_Implementation(float Value) override;
	virtual void UpdateCurrentMana_Implementation(float Value) override;
	virtual void UpdateMaxMana_Implementation(float Value) override;

private:
	void SetProgressBarColor();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBarWidget> Health;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBarWidget> Mana;
};
