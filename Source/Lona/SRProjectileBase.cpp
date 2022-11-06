// Fill out your copyright notice in the Description page of Project Settings.


#include "SRProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASRProjectileBase::ASRProjectileBase()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionProfileName("Projectile");
	RootComponent = SphereCollision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");
	ParticleComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetAutoActivate(true);

	NiagaraParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraParticleComponent"));
	NiagaraParticleComponent->SetupAttachment(RootComponent);
	NiagaraParticleComponent->SetAutoActivate(true);

	DamageAmount = 5.0f;
}

void ASRProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereCollision->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ASRProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentHit.AddDynamic(this, &ASRProjectileBase::OnActorHit);
}

void ASRProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit!!!"));
	HitExplode();
}

void ASRProjectileBase::HitExplode_Implementation()
{
	if(HitEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	}
	
	Destroy();
}
