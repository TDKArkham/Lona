// Fill out your copyright notice in the Description page of Project Settings.


#include "SRProjectile_Bullet.h"

#include "SideRunnerCharacter.h"
#include "SRAttributeComponent.h"
#include "Components/SphereComponent.h"

void ASRProjectile_Bullet::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASRProjectile_Bullet::OnBeginOverlap);
}

void ASRProjectile_Bullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		USRAttributeComponent* Target = USRAttributeComponent::GetAttributeComponent(OtherActor);
		if(Target && Target->ApplyHealthChange(GetInstigator(), -DamageAmount))
		{
			HitExplode();
		}
	}
}
