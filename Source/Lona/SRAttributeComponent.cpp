// Fill out your copyright notice in the Description page of Project Settings.


#include "SRAttributeComponent.h"

USRAttributeComponent::USRAttributeComponent()
{
	HealthMax = 100.0f;
	MagicPoolMax = 50;
	
}


void USRAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = HealthMax;
	MagicPool = MagicPoolMax;
}

float USRAttributeComponent::GetHealth() const
{
	return Health;
}

float USRAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USRAttributeComponent::GetIsAlive() const
{
	return Health > 0.0f;
}

USRAttributeComponent* USRAttributeComponent::GetAttributeComponent(AActor* TargetActor)
{
	if (TargetActor)
	{
		return Cast<USRAttributeComponent>(TargetActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}

bool USRAttributeComponent::ApplyHealthChange(AActor* InstigateActor, float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	Delta = Health - OldHealth;

	if (Delta != 0)
	{
		OnHealthChanged.Broadcast(InstigateActor, this, Health, Delta);
	}

	return Delta != 0;
}

int32 USRAttributeComponent::GetMagicPool() const
{
	return MagicPool;
}

int32 USRAttributeComponent::GetMagicPoolMax() const
{
	return MagicPoolMax;
}

bool USRAttributeComponent::ApplyMagicPoolChange(float Delta)
{
	float OldPool = MagicPool;
	MagicPool = FMath::Clamp(MagicPool + Delta, 0.0f, MagicPoolMax);
	Delta = MagicPool - OldPool;

	if (Delta != 0)
	{
		OnMagicPoolChanged.Broadcast(nullptr, this, MagicPool, Delta);
	}

	return Delta != 0;
}
