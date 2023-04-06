// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	if(GetOwner())
	{
		GetOwner()->SetRootComponent(mesh);
	}
}

float AObstacle::GetDistanceFromPlayer()
{
	if (auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		return FVector::Distance(GetActorLocation(), character->GetActorLocation());
	}
	return 10000;
	
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

