// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponBase.h"


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

	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(GetRootComponent());
												   
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


	

	MinDamageRandMultiplier = 1;
	MaxDamageRandMultiplier = 3;

	//*****************************************************************************************************************************************/
	// Player Stats
	Name = FString("Mecal");
	StartMaxHealth = 1200;
	Health = 800.0f;
	MaxHealth = 1000.0f;
	Mana = 250.0f;
	MaxMana = 300.0f;
	Stamina = 400.0f;
	MaxStamina = 400.0f;
	MeleeStrenth = 10;
	MaxMeleeStrength = 99;
	RangeStrength = 10;
	MaxRangeStrength = 99;
	Intelligence = 10;
	MaxIntelligence = 99;
	Defense = 15;
	MaxDefense = 99;
	ManaGateLevel = 1;
	MaxManaGateLevel = 5;
	Lars = 0;
	Level = 1;
	MaxLevel = 40;
	ExperienceToNextLevel = 100.0f;
	CurrentExperience = 25.0f;

	HealthDisplay = FString::FromInt(int32(Health));

	//*****************************************************************************************************************************************/

	// Variables for calculating damage
	DamageTaken = 0;
	DamageDivider = 12; 
	
	// Variables for sprinting
	RunningSpeed = 650.0f;
	SprintingSpeed = 950.0f;
	bSprintKeyDown = false; 

	// Initalize ENUMS
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

	// Variables for managing Stamina
	StaminaDrainRate = 10.0f;
	StaminaRecoveryRate = 5.0f; 
	MinSprintStamina = 100.0f; 

	bActionButtonDown = false; 
	bIsWeaponEquipped = false;
	EquippedWeapon = nullptr;


}


// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = StartMaxHealth;
	Health = MaxHealth;
	HealthDisplay = FString::FromInt(int32(Health));

}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// HealthDisplay = FString::FromInt(int32(Health));

	// How much Stamina should change in this frame
	float DeltaStamina = StaminaDrainRate * DeltaTime;
	float DeltaRegenStamina = StaminaRecoveryRate * DeltaTime;

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:

		if (bSprintKeyDown)
		{
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				StaminaStatus = EStaminaStatus::ESS_BelowMinimum;
				Stamina -= DeltaStamina;
			}
			else
			{
				Stamina -= DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
		}
		else
		{
			if (Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina; 
			}
			else
			{
				Stamina += DeltaRegenStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		
		if (bSprintKeyDown)
		{
			if (Stamina - DeltaStamina <= 0.0f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0.0f;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				Stamina -= DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			
		}
		else
		{
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaRegenStamina;
			}
			else
			{
				Stamina += DeltaRegenStamina; 
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}

		break;
	case EStaminaStatus::ESS_Exhausted:

		if (bSprintKeyDown)
		{
			Stamina = 0.0f;
		}
		else
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			Stamina += DeltaRegenStamina; 
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);

		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:

		if (Stamina + DeltaRegenStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaRegenStamina;
		}
		else
		{
			Stamina += DeltaRegenStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);

		break;
	default:
		break;
	}

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);  

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); // Inherited from Character class
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); // Inherited from Character class

	PlayerInputComponent->BindAction("ActionButton", IE_Pressed, this, &AMain::ActionButtonDown);
	PlayerInputComponent->BindAction("ActionButton", IE_Released, this, &AMain::ActionButtonUp); 

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::SprintKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMain::SprintKeyUp);


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

void AMain::ActionButtonDown()
{
	bActionButtonDown = true; 
	if (ActiveOverlappingItem)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(ActiveOverlappingItem); 

		if (Weapon)
		{
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr); 
		}
	}
}

void AMain::ActionButtonUp()
{
	bActionButtonDown = false;
}

void AMain::DecrementHealth(int32 EnemyDamage, int32 EnemyPhysicalStrength, int32 EnemyManaStrength, int32 EnemyLevel, bool PhysicalAttack)
{
	int32 Random = FMath::RandRange(MinDamageRandMultiplier, MaxDamageRandMultiplier);


	UE_LOG(LogTemp, Warning, TEXT("Random Modifier %i "), Random);

	if (PhysicalAttack)
	{
		DamageTaken = ((EnemyDamage * Random) - Defense) * (1 + EnemyLevel * (EnemyLevel + EnemyPhysicalStrength) / DamageDivider);

		UE_LOG(LogTemp, Warning, TEXT("Physical Damange Taken %i "), DamageTaken);
	}
	else
	{
		DamageTaken = ((EnemyDamage * Random) - Defense) * (1 + EnemyLevel * (EnemyLevel + EnemyManaStrength) / DamageDivider);

		UE_LOG(LogTemp, Warning, TEXT("Physical Damange Taken %i "), DamageTaken);
	}

	if (Health - DamageTaken <= 0)
	{
		Health = 0; 
		HealthDisplay = FString::FromInt(int32(Health));
		Die();
	}
	else
	{
		Health -= DamageTaken; 
		HealthDisplay = FString::FromInt(int32(Health));
	}

}

void AMain::Die()
{
}

void AMain::IncrementLars(int32 Amount)
{
	Lars += Amount; 
}

void AMain::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status; 

	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed; 
	}

}

void AMain::SprintKeyDown()
{
	bSprintKeyDown = true; 
}

void AMain::SprintKeyUp()
{
	bSprintKeyDown = false; 
}

void AMain::ShowPickUpLocations()
{
	/**for (int32 i = 0; i < PickUpLocations.Num(); i++)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, PickUpLocations[i], 25.0f, 12, FLinearColor::Green, 10.0f, 2.0f);
	} */

	
	for (auto Location : PickUpLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.0f, 12, FLinearColor::Green, 10.0f, 2.0f);
	}
}

void AMain::SetEquipWeapon(AWeaponBase* WeaponToSet)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	EquippedWeapon = WeaponToSet;
	bIsWeaponEquipped = true; 
	
}
