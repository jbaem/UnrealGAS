#include "Test/TestCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/WidgetComponent.h"
#include "Interface/TwinResource.h"

#include "AbilitySystemComponent.h"
#include "GAS/ResourceAttributeSet.h"
#include "GAS/StatusAttributeSet.h"
#include "GAS/GASEnums.h"

ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TwinResourceBarComp"));
	BarWidget->SetupAttachment(RootComponent);
	
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	Resource = CreateDefaultSubobject<UResourceAttributeSet>(TEXT("Resource"));
	Status = CreateDefaultSubobject<UStatusAttributeSet>(TEXT("Status"));
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		if (HasteClass)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(HasteClass, 1, static_cast<int32>(EAbilityInputID::HASTE), this));
		}

		FOnGameplayAttributeValueChange& OnHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetHealthAttribute());
		OnHealthChange.AddUObject(this, &ATestCharacter::OnHealthChanged);

		FOnGameplayAttributeValueChange& OnMaxHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetMaxHealthAttribute());
		OnMaxHealthChange.AddUObject(this, &ATestCharacter::OnMaxHealthChanged);

		FOnGameplayAttributeValueChange& OnManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetManaAttribute());
		OnManaChange.AddUObject(this, &ATestCharacter::OnManaChanged);

		FOnGameplayAttributeValueChange& OnMaxManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetMaxManaAttribute());
		OnMaxManaChange.AddUObject(this, &ATestCharacter::OnMaxManaChanged);
	}
	if (Resource)
	{
		if (BarWidget && BarWidget->GetWidget())
		{
			if (BarWidget->GetWidget()->Implements<UTwinResource>())
			{
				ITwinResource::Execute_UpdateMaxHealth(BarWidget->GetWidget(), Resource->GetMaxHealth());
				ITwinResource::Execute_UpdateCurrentHealth(BarWidget->GetWidget(), Resource->GetHealth());
				
				ITwinResource::Execute_UpdateMaxMana(BarWidget->GetWidget(), Resource->GetMaxMana());
				ITwinResource::Execute_UpdateCurrentMana(BarWidget->GetWidget(), Resource->GetMana());
			}
		}
	}

	Tag_EffectDamage = FGameplayTag::RequestGameplayTag(FName("Effect.Damage"));
}

void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
	
		EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Started, this, &ATestCharacter::OnAbility1Press);
	}
}

void ATestCharacter::TestSetByCaller(float Amount)
{
	if (ASC)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(TestSetByCallerEffectClass, 0.f, EffectContext);
		if(SpecHandle.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(Tag_EffectDamage, Amount);
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

			float FinalMag = SpecHandle.Data->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Effect.Damage")));
		}
	}
}

void ATestCharacter::TestAddInfiniteEffect()
{
	if(TestInfiniteEffectClass && ASC)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddInstigator(this, this);
		
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(TestInfiniteEffectClass, 0.f, EffectContext);
		if(SpecHandle.IsValid())
		{
			TestInfiniteEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ATestCharacter::TestRemoveInfiniteEffect()
{
	if(TestInfiniteEffectHandle.IsValid() && ASC)
	{
		ASC->RemoveActiveGameplayEffect(TestInfiniteEffectHandle);
	}
}

void ATestCharacter::TestApplyHaste()
{
	if (ASC)
	{
		ASC->TryActivateAbilityByClass(HasteClass);
	}
}

void ATestCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void ATestCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATestCharacter::DoMove(float Right, float Forward)
{
	if (!GetController())
	{
		return;
	}

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, Forward);
	AddMovementInput(RightDirection, Right);
}

void ATestCharacter::DoLook(float Yaw, float Pitch)
{
	if (!GetController())
	{
		return;
	}

	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void ATestCharacter::DoJumpStart()
{
	Jump();
}
void ATestCharacter::DoJumpEnd()
{
	StopJumping();
}

void ATestCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	//UE_LOG(LogTemp, Log, TEXT("On Health Changed: OldValue=%f, NewValue=%f"), Data.OldValue, Data.NewValue);
	ITwinResource::Execute_UpdateCurrentHealth(BarWidget->GetWidget(), Resource->GetHealth());
}

void ATestCharacter::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	ITwinResource::Execute_UpdateMaxHealth(BarWidget->GetWidget(), Resource->GetMaxHealth());
	ITwinResource::Execute_UpdateCurrentHealth(BarWidget->GetWidget(), Resource->GetHealth());
}

void ATestCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
	ITwinResource::Execute_UpdateCurrentMana(BarWidget->GetWidget(), Resource->GetMana());
}

void ATestCharacter::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
	ITwinResource::Execute_UpdateMaxMana(BarWidget->GetWidget(), Resource->GetMaxMana());
	ITwinResource::Execute_UpdateCurrentMana(BarWidget->GetWidget(), Resource->GetMana());
}

void ATestCharacter::OnAbility1Press()
{
	if (ASC)
	{
		ASC->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::HASTE));
	}
}
