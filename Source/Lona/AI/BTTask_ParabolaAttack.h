// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ParabolaAttack.generated.h"

class ASRProjectile_EnemyParabola;
/**
 * 
 */
UCLASS()
class LONA_API UBTTask_ParabolaAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<ASRProjectile_EnemyParabola> ParabolaProjectile;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
