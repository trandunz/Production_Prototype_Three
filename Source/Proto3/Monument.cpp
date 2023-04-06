// Fill out your copyright notice in the Description page of Project Settings.


#include "Monument.h"

// Sets default values
AMonument::AMonument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMonument::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

