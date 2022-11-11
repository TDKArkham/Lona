// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckWithinAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class LONA_API UBTService_CheckWithinAttackRange : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector KeySelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AttackRange;
};
