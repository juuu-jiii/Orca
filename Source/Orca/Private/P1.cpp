// Fill out your copyright notice in the Description page of Project Settings.


#include "P1.h"
//#include "P1MovementComponent.h"
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
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));

	// Attach Static Mesh to root component.
	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playerMesh"));
	playerMesh->SetupAttachment(RootComponent);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArm->SetupAttachment(RootComponent);

	// Create and attach camera to springArm.
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);

	// Instantiate movementComponent, and set it to update the root component.
	/*movementComponent = CreateDefaultSubobject<UP1MovementComponent>(TEXT("movementComponent"));
	movementComponent->UpdatedComponent = RootComponent;*/

	//playerMesh->OnComponentBeginOverlap.Add(this, &AP1::UpdateCollision);

	// This pawn is controlled by the player.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AP1::BeginPlay()
{
	Super::BeginPlay();
	////playerMesh->OnComponentHit.AddDynamic(this, &AP1::HandleCollision);
	//playerMesh->OnComponentBeginOverlap.AddDynamic(this, &AP1::HandleCollision);

	//FHitResult hit;
	//hit.IsValidBlockingHit
	//camera->
	playerMesh->OnComponentBeginOverlap.AddDynamic(this, &AP1::HandleCollision);
	//this->ReceiveHit.AddDynamic(this, &AP1::HandleHit);
	//playerMesh->GetStaticMesh()->oncomponent
}

// Called every frame
void AP1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Reset to start a new Tick cycle from scratch.
	acceleration = FVector::ZeroVector;

	if (moving)
	{
		FVector NewLocation = GetActorLocation() + velocity * DeltaTime;
		SetActorLocation(NewLocation);
	}

	//if (OnActorBeginOverlap)
	//onactorbeginoverlap
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

// Override GetMovementComponent as defined in the .h.
//UPawnMovementComponent* AP1::GetMovementComponent() const 
//{
//	return movementComponent;
//}

//void AP1::ReceiveHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	GLog->Log(*OtherActor->GetName());
//}

void AP1::HandleCollision(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), OtherActor->Tags);

	UE_LOG(LogTemp, Warning, TEXT("Collision detected"));

	speed = 0;
	velocity = speed * GetActorForwardVector();
	moving = !moving;

	//if (OtherActor->ActorHasTag(TEXT("Wall")))
}

//void AP1::HandleHit(
//	class UPrimitiveComponent* MyComp,
//	AActor* Other,
//	class UPrimitiveComponent* OtherComp,
//	bool bSelfMoved,
//	FVector HitLocation,
//	FVector HitNormal,
//	FVector NormalImpulse,
//	const FHitResult& Hit)
//{
//	speed = 0;
//	velocity = speed * GetActorForwardVector();
//	moving = !moving;
//}

void AP1::Steer(int angle)
{
	// Keep track of speed so that it can be maintained after a turn has been made.
	speed = velocity.Size();

	// Steer the vehicle.
	FRotator rotation = GetActorRotation();
	// Negative rotation = left direction, and vice versa
	rotation.Yaw += angle;
	SetActorRotation(rotation);

	// Update the velocity with respect to the vehicle's forward vector.
	// Forward vector is based on object's local axes. It is where the object's 
	// local x-axis is pointing in terms of the global coordinate system.
	velocity = speed * GetActorForwardVector();

	//movementComponent->AddInputVector(velocity);
}

void AP1::Accelerate()
{
	if (/*movementComponent && movementComponent->UpdatedComponent == RootComponent && */!moving)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Accelerating"));
		
		//movementComponent->AddInputVector(GetActorForwardVector());
		speed = 500; // Speed: 500 Unreal Units
		velocity = speed * GetActorForwardVector();
		moving = !moving;
	}
}

void AP1::Brake()
{
	if (/*movementComponent && movementComponent->UpdatedComponent == RootComponent && */moving)
	{
		speed = 0;
		velocity = speed * GetActorForwardVector();
		//movementComponent->AddInputVector(velocity);
		moving = !moving;
	}
}

void AP1::SteerLeft()
{
	Steer(-90);
}

void AP1::SteerRight()
{
	Steer(90);
}

// TODO: fix collisions. player should not be able to move walls.
// How about you use the hit event and then instantaneously halt acceleration while
// the hit event is fired? Either way, hitting a wall results in an instant crash.
// TODO: maybe rebuild world, but first modify assets to support collision beforehand
// TODO: include an acceleration vector. Change accel to change vel to change pos
// FIXME: Accel is ignored for now, only changes in velocity are used.