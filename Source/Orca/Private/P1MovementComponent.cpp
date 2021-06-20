// Fill out your copyright notice in the Description page of Project Settings.


#include "P1MovementComponent.h"

// The overridden version of this method 
void UP1MovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Only run this method if everything is valid and movement is possible.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;

	FVector frameMovement = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 500.0f;

	if (!frameMovement.IsNearlyZero())
	{
		FHitResult hit;
		SafeMoveUpdatedComponent(frameMovement, UpdatedComponent->GetComponentRotation(), true, hit);

		// Stop moving on collision.
		if (hit.IsValidBlockingHit())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit detected"));
			StopMovementImmediately();
		}
	}
}