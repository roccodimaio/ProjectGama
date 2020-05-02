// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "BasicEnemy.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SetRootComponent(SpawningBox);

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent(); // Returns the dimensions of the box
	FVector Origin = SpawningBox->GetComponentLocation(); // Returns the center point of the box
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent); // Returns random point within the box

	return Point;
}

void ASpawnVolume::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld(); 
		FActorSpawnParameters SpawnParms; 


		if (World)
		{
			ABasicEnemy*  EnemySpawned = World->SpawnActor<ABasicEnemy>(ToSpawn, Location, FRotator(0.0f), SpawnParms);
		}
	}
}



