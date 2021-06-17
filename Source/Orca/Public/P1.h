// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "P1.generated.h"

UCLASS()
class ORCA_API AP1 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Static Mesh asset - must be set as EditAnywhere in the .h, and NOT the .cpp
	// This is visible in the Editor, so setup can be done there.
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* playerMesh;

	// Camera
	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	// Reference to custom Pawn Movement Component

	// Override GetMovementComponent() to return the custom Pawn Movement
	// Component.

	// Steering method
	void Steer(int angle);

	// Handle input the Pawn will receive.
	void Accelerate();
	void Brake();
	void SteerLeft();
	void SteerRight();

private:
	// Variables controlling Pawn movement
	FVector position;
	FVector velocity;
	FVector acceleration;
	float speed;
	
	// Keep track of whether player is moving. Cap velocity regardless of number
	// of up key presses.
	bool moving;
};

// FIXME: Forward acceleration is ignored for now. Accel only used for turning.