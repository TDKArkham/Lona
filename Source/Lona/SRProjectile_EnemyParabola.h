// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRProjectileBase.h"
#include "SRProjectile_EnemyParabola.generated.h"

/**
 * 
 */
UCLASS()
class LONA_API ASRProjectile_EnemyParabola : public ASRProjectileBase
{
	GENERATED_BODY()

public:
	ASRProjectile_EnemyParabola();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float FlyTime;
};
