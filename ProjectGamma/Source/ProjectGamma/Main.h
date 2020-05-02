// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UCLASS()
class PROJECTGAMMA_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	// Subobjects

	/** Camera boom to position the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraBoomLength;
	
	/** Base turn rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate; 

	/** Base look up rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	/**
	/*
	/* PLayer Stats
	/*
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float MaxMana;

	// Used to determine Sprinting duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float MaxStamina;

	// Used to determine strength of melee attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 MeleeStrenth; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxMeleeStrength;

	// Used to determine strength of range attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 RangeStrength; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxRangeStrength;

	// Used to determine strength of mana attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Intelligence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxIntelligence; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Defense; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxDefense; 
	
	// Used to determine level of mana attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 ManaGateLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxManaGateLevel; 

	// Currency 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Lars; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxLevel; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerStats")
	float ExperienceToNextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float CurrentExperience; 

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

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
