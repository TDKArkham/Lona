// Fill out your copyright notice in the Description page of Project Settings.


#include "SRAIController.h"

void ASRAIController::BeginPlay()
{
	Super::BeginPlay();

	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
