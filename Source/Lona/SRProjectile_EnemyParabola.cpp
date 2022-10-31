// Fill out your copyright notice in the Description page of Project Settings.


#include "SRProjectile_EnemyParabola.h"

#include "AI/SRAICharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASRProjectile_EnemyParabola::ASRProjectile_EnemyParabola()
{
	
}

void ASRProjectile_EnemyParabola::BeginPlay()
{
	Super::BeginPlay();
	
	//ProjectileMovement->Velocity = GetInitVelocity();
}
