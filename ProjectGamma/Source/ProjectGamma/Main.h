// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

/** ENUM that holds the different movement status of Main */
UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA (DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhuastedRecovering"),
	ESS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class PROJECTGAMMA_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AWeaponBase* EquippedWeapon; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlappingItem;

	TArray<FVector> PickUpLocations; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EStaminaStatus StaminaStatus; 

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed; 

	bool bSprintKeyDown;

	// Subobjects

	/** Camera boom to position the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraBoomLength;
	
	/** Base turn rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate; 

	/** Base look up rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	/******************************************************************************************************************/
	/**
	/*
	/* PLayer Stats
	/*
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float StartMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float MaxMana;

	/** Used to determine Sprinting duration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float MaxStamina;

	/** Used to determine strength of melee attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 MeleeStrenth; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxMeleeStrength;

	/** Used to determine strength of range attacks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 RangeStrength; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxRangeStrength;

	/** Used to determine strength of mana attacks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Intelligence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxIntelligence; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Defense; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxDefense; 
	
	/** Used to determine level of mana attacks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 ManaGateLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxManaGateLevel; 

	/** Currency */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Lars; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxLevel; 

	/******************************************************************************************************************/

	/** How much total experience required to level up */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float ExperienceToNextLevel;

	/** Amount of experience towards next level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float CurrentExperience; 

	/** FString to display current healt to the HUD */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	FString HealthDisplay;

	/** The amount of damage taken from an attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTaken")
	int32 DamageTaken; 

	/** Minimum random number used to calculate damage taken from an attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTaken")
	int32 MinDamageRandMultiplier;

	/** Maximum random number used to calculate damage taken from an attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTaken")
	int32 MaxDamageRandMultiplier; 

	/** Number used to calculate damage taken from an attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTaken")
	int32 DamageDivider; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoveryRate; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina; 

	bool bActionButtonDown; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsWeaponEquipped; 


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Public Functions

	/* Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called via input to turn at a given rate 
	* @param Rate This is a normalized rate i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate This is a normalized rate i.e. 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	void ActionButtonDown();

	void ActionButtonUp(); 

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void DecrementHealth(int32 EnemyDamage, int32 EnemyPhysicalStrength, int32 EnemyManaStrength, int32 EnemyLevel, bool PhysicalAttack);

	void Die();

	void IncrementLars(int32 Amount);

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus Status);

	/** Pressed down to enable sprinting*/
	void SprintKeyDown();

	/** Released to stop sprinting */
	void SprintKeyUp();

	UFUNCTION(BlueprintCallable)
	void ShowPickUpLocations(); 

	void SetEquipWeapon(AWeaponBase* WeaponToSet);
	FORCEINLINE AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }
};
