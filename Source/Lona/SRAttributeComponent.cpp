// Fill out your copyright notice in the Description page of Project Settings.


#include "SRAttributeComponent.h"

USRAttributeComponent::USRAttributeComponent()
{
	HealthMax = 100.0f;
	Health = HealthMax;
}


void USRAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

float USRAttributeComponent::GetHealth() const
{
	return Health;
}

float USRAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USRAttributeComponent::ApplyHealthChange(AActor* InstigateActor, float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	Delta = Health - OldHealth;

	if(Delta != 0)
	{
		OnHealthChanged.Broadcast(InstigateActor, this, Health, Delta);
	}

	return Delta != 0;
}
