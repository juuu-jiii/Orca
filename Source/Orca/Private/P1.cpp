// Fill out your copyright notice in the Description page of Project Settings.


#include "P1.h"
#include "Math/Vector.h"
// #include custom Pawn Movement Component



// Sets default values
AP1::AP1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// You will need:
	// - Static Mesh Component (visual representation)
	// - Camera Component
	// 
	// - As for collision component, that will be added in the editor itself.
	// TODO: add collision component
	
	moving = false;

	// Create a dummy root component things can be attached to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Attach Static Mesh to root component.
	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playerMesh"));
	playerMesh->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);

	// This pawn is controlled by the player.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AP1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Reset to start a new Tick cycle from scratch.
	acceleration = FVector::ZeroVector;

	// todo: maybe alter movement based on fwd vector? Cuz it seems like that is changing
	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z);

	if (moving)
	{
		FVector NewLocation = GetActorLocation() + velocity * DeltaTime;
		SetActorLocation(NewLocation);
		//Rotat
	}
}

// Called to bind functionality to input
void AP1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Accelerate", IE_Pressed, this, &AP1::Accelerate);
	InputComponent->BindAction("Brake", IE_Pressed, this, &AP1::Brake);
	InputComponent->BindAction("SteerLeft", IE_Pressed, this, &AP1::SteerLeft);
	InputComponent->BindAction("SteerRight", IE_Pressed, this, &AP1::SteerRight);
}

void AP1::Accelerate()
{
	if (!moving)
	{
		velocity.X = 500.0f; // Speed: 500 Unreal Units
		moving = !moving;
	}
		//SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
}

void AP1::Brake()
{
	if (moving)
	{
		velocity.X = 0.0f;
		moving = !moving;
	}
}

void AP1::SteerLeft()
{
	// You need to alter the object's velocity as well. You can't just rotate like
	// that LOL

	FRotator rotation = GetActorRotation();
	rotation.Yaw -= 90; // Negative rotation = left direction
	SetActorRotation(rotation);

	// TODO: change velocity as well as rotation.
	// TODO: include an acceleration vector. Change accel to change vel to change pos

}

void AP1::SteerRight()
{
	FRotator rotation = GetActorRotation();
	rotation.Yaw += 90; // Positive rotation = right direction
	SetActorRotation(rotation);
}

