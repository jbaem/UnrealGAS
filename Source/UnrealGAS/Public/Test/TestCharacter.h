#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"

#include "TestCharacter.generated.h"

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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "PJB|Input")
	TObjectPtr<class UInputAction> MouseLookAction;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PJB")
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;
};
