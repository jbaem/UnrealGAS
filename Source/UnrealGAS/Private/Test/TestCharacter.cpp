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

#include "AbilitySystemComponent.h"
#include "GAS/StatusAttributeSet.h"

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


	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	Status = CreateDefaultSubobject<UStatusAttributeSet>(TEXT("Status"));
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		FOnGameplayAttributeValueChange& OnHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UStatusAttributeSet::GetHealthAttribute());
		OnHealthChange.AddUObject(this, &ATestCharacter::OnHealthChanged);
	}
	if (Status)
	{
		Status->SetHealth(100.0f);
	}
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
	UE_LOG(LogTemp, Log, TEXT("On Health Changed: OldValue=%f, NewValue=%f"), Data.OldValue, Data.NewValue);

}

