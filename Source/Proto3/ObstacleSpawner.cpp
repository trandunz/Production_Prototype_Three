// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Obstacle.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Obstacles.SetNum(maxObstacles);

    for (auto element : Obstacles)
    {
	    element = nullptr;
    }
}

void AObstacleSpawner::SpawnObstacle()
{
	if (Obstacles.Num() < maxObstacles && ObstaclePrefabs.Num() > 0)
	{
		int num = FMath::RandRange(0, ObstaclePrefabs.Num() - 1);
	}
}

void AObstacleSpawner::CleanUpObstacles()
{
	
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

