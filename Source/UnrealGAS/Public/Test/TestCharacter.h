#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

#include "TestCharacter.generated.h"

class UResourceAttributeSet;

UCLASS()
class UNREALGAS_API ATestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATestCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return ASC;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
	void TestSetByCaller(float Amount);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PJB|Test")
	TSubclassOf<class UGameplayEffect> TestSetByCallerEffectClass;

	UFUNCTION(BlueprintCallable)
	void TestAddInfiniteEffect();
	UFUNCTION(BlueprintCallable)
	void TestRemoveInfiniteEffect();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PJB|Test")
	TSubclassOf<class UGameplayEffect> TestInfiniteEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void TestApplyHaste();

	UFUNCTION(BlueprintCallable)
	void TestLineTrace();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PJB|Test")
	TSubclassOf<class UGameplayEffect> TestHitEffectClass = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = "PJB")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category = "PJB")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category = "PJB")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category = "PJB")
	virtual void DoJumpEnd();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

private:
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	void OnManaChanged(const FOnAttributeChangeData& Data);
	void OnMaxManaChanged(const FOnAttributeChangeData& Data);
	
	void OnAbility1Press();
	void OnAbility2Press();
	void OnAbility3Press();
	void OnAbility3Release();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<class USpringArmComponent> CameraBoom = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<class UCameraComponent> FollowCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<class UWidgetComponent> BarWidget = nullptr;

	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> MouseLookAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> Ability1Action;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> Ability2Action;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> Ability3Action;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;

	UPROPERTY()
	TObjectPtr<class UResourceAttributeSet> Resource = nullptr;
	UPROPERTY()
	TObjectPtr<class UStatusAttributeSet> Status = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability")
	TSubclassOf<class UGameplayAbility> HasteClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability")
	TSubclassOf<class UGameplayAbility> SuperJumpClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PJB|Ability")
	TSubclassOf<class UGameplayAbility> ChargingJumpClass = nullptr;

private:
	FGameplayTag Tag_EffectDamage;
	FActiveGameplayEffectHandle TestInfiniteEffectHandle;
};
