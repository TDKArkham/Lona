// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRProjectileBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class LONA_API ASRProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRProjectileBase();
	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* NiagaraParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UNiagaraSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float DamageAmount;
	
public:
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HitExplode();
};
