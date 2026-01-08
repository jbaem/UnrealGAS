#include "TestZone/TestZone.h"

#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

ATestZone::ATestZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

void ATestZone::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATestZone::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ATestZone::OnEndOverlap);
}

void ATestZone::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ATestZone::OnEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (ASC)
	{
		if (ActiveEffectHandle.Contains(ASC))
		{
			ASC->RemoveActiveGameplayEffect(ActiveEffectHandle[ASC]);
			ActiveEffectHandle.Remove(ASC);
		}
	}
}

