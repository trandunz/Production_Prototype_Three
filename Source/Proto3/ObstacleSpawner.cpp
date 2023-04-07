// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Obstacle.h"

#include "Ai/NavigationSystemBase.h"
#include "NavigationSystem.h"

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

void AObstacleSpawner::SpawnObstacle(int _num)
{
	if (Obstacles.Num() < maxObstacles && ObstaclePrefabs.Num() > 0)
	{
		int num = FMath::RandRange(0, ObstaclePrefabs.Num() - 1);
		if (ObstaclePrefabs[num])
		{
			int x = FMath::RandRange(-100, 100);
			int y = FMath::RandRange(10, 50);
			int z = FMath::RandRange(-100, 100);
			Obstacles[_num] = GetWorld()->SpawnActor<AObstacle>(ObstaclePrefabs[num], FVector(x, y, z), FRotator());
			currentObstacleCount += 1;
		}
	}
}

void AObstacleSpawner::CleanUpObstacles()
{
	for (auto element : Obstacles)
	{
		if (element)
		{
			if (element->GetDistanceFromPlayer() > 50)
			{
				int num = -1;
				for (int i = 0; i < maxObstacles; i++)
				{
					if (Obstacles[i] == element)
					{
						num = i;
					}
				}
				element->Destroy();
				Obstacles[num] = nullptr;
				SpawnObstacle(num);
			}
		}
	}
}

void AObstacleSpawner::SpawnStarterObstacles()
{
	if (spawnBeforeLoad)
	{
		if (UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
		{
			for (int i = 0; i < maxObstacles; i++)
			{
				FNavLocation Result;
				navSys->GetRandomPoint(Result);
				FVector finalLocation = Result.Location;
				finalLocation.Z -= 40.0f;
				int num = FMath::RandRange(0, ObstaclePrefabs.Num() - 1);
				Obstacles[i] = GetWorld()->SpawnActor<AObstacle>(ObstaclePrefabs[num], finalLocation, FRotator());
			}
		}
	}
	else
	{
		if (UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
		{
			for (int i = 0; i < spawnBeforeLoadCount; i++)
			{
				FNavLocation Result;
				navSys->GetRandomPoint(Result);
				FVector finalLocation = Result.Location;
				finalLocation.Z -= 40.0f;
				int num = FMath::RandRange(0, ObstaclePrefabs.Num() - 1);
				Obstacles[i] = GetWorld()->SpawnActor<AObstacle>(ObstaclePrefabs[num], finalLocation, FRotator());
				currentObstacleCount += 1;
			}
		}
	}
}

void AObstacleSpawner::SpawnObstaclesDuringPlay()
{
	if (UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
	{
		FNavLocation Result;
		navSys->GetRandomPoint(Result);
		FVector finalLocation = Result.Location;
		finalLocation.Z -= 40.0f;
		int num = FMath::RandRange(0, ObstaclePrefabs.Num() - 1);
		Obstacles[currentObstacleCount] = GetWorld()->SpawnActor<AObstacle>(ObstaclePrefabs[num], finalLocation, FRotator());
		currentObstacleCount += 1;
	}
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	Obstacles.SetNum(maxObstacles);

	for (auto element : Obstacles)
	{
		element = nullptr;
	}

	SpawnStarterObstacles();
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!spawnBeforeLoad && currentObstacleCount != maxObstacles)
	{
		SpawnObstaclesDuringPlay();
	}

}

