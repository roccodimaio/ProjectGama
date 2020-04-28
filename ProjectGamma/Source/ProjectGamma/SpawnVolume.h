// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class PROJECTGAMMA_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;

	/** Create drop down menu in blueprint populated with class BasicEnemy and all classes derived from BasicEnemy 
		Allows the population of a variable with a Unreal Engine blueprint such as BasicEnemy_BP */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ABasicEnemy> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Random point(vector) within the SpawningBox to spawn */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawnPoint();
};
