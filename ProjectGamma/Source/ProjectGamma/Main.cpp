// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoomLength = 600.0f; 

	// Create Camera Boom (pulls towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent()); // Attacheds the CameraBoom to the root component
	CameraBoom->TargetArmLength = CameraBoomLength; // Camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(25.0f, 94.3f);

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamers"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attached FollowCamera to the CameraBoom on socket SocketName
	FollowCamera->bUsePawnControlRotation = false; // Camera will only follow camera boom, will not follow controller

	// Set our turn rates for input
	BaseTurnRate = 65.0f; 
	BaseLookUpRate = 65.0f; 

	// Prevent character from rotating by rotating the controller
	// Rotating the controller will only affect the camera
	bUseControllerRotationYaw = false; 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Access CharacterMovementComponent and modify
	GetCharacterMovement()->bOrientRotationToMovement = true; // Configure character to move in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // How quickly character will rotate to orientate itself in the direction of input
	GetCharacterMovement()->JumpZVelocity = 650.0f; // Velocity when jumping 
	GetCharacterMovement()->AirControl = 0.2f; // Control over character when in the air (1.0 = full control)



}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);  

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); // Inherited from Character class
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); // Inherited from Character class

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // Inherited from Pawn class
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput); // Inherited from Pawn class

	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate);

}

void AMain::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation(); // Provides direction the controller is facing
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); //Assign the Yaw of Rotation to YawRotation

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Direction we are looking at. Pull X axis (forward) of the controller from the rotation matrix based on the Yaw rotation

		AddMovementInput(Direction, Value); // Add movement input in the direction calculated above
	}
}

void AMain::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation(); // Provides direction the controller is facing
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); //Assign the Yaw of Rotation to YawRotation

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Direction we are looking at. Pull Y axis (right) of the controller from the rotation matrix based on the Yaw rotation

		AddMovementInput(Direction, Value);
	}
}

void AMain::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // Turn at: Rate (Between 0 and 1) * BaseTurnRate (65.0f) * time between frames (DeltaTime)
}

void AMain::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); // Look up/down at: Rate (Between 0 and 1) * BaseLookUpAtRate (65.0f) * time between frames (DeltaTime)
}

