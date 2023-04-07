// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class AObstacle;
UCLASS()
class PROTO3_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	UPROPERTY(EditAnywhere)
	bool spawnBeforeLoad = false;

	UPROPERTY(EditAnywhere)
	int32 spawnBeforeLoadCount = 200;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AObstacle>> ObstaclePrefabs;

	UPROPERTY(VisibleAnywhere)
	TArray<AObstacle*> Obstacles;

	UPROPERTY(EditAnywhere)
	int32 maxObstacles = 10;

	UPROPERTY(VisibleAnywhere)
	int32 currentObstacleCount = 0;

	
	void SpawnObstacle(int _num);
	void CleanUpObstacles();
	void SpawnStarterObstacles();

	void SpawnObstaclesDuringPlay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
