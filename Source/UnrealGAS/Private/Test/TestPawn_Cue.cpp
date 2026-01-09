#include "Test/TestPawn_Cue.h"

#include "AbilitySystemComponent.h"

ATestPawn_Cue::ATestPawn_Cue()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void ATestPawn_Cue::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);
	}
}

void ATestPawn_Cue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestPawn_Cue::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

