// Fill out your copyright notice in the Description page of Project Settings.


#include "SandSailPlayer.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ASandSailPlayer::ASandSailPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mast = CreateDefaultSubobject<UStaticMeshComponent>("Mast");
	Mast->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 
}

// Called when the game starts or when spawned
void ASandSailPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void ASandSailPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Dt = DeltaTime;
	MastRotation = FMath::Lerp(MastRotation, 0.0f, Dt * 10.0f);
	Mast->SetRelativeRotation(FRotator{0,MastRotation,0});
}

void ASandSailPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// get forward vector
		const FVector ForwardDirection = GetActorForwardVector();
	
		// get right vector 
		const FVector RightDirection =  GetActorRightVector();

		if (MovementVector.X > 0)
		{
			MastRotation = FMath::Lerp(MastRotation, 90.0f, Dt * 15.0f);
		}
		else if (MovementVector.X < 0)
		{
			MastRotation = FMath::Lerp(MastRotation, -90.f, Dt * 15.0f);
		}
		// add movement
		if (MovementVector.Y > 0)
			Mesh->AddForce(Mesh->GetForwardVector() * 10000.0f);
		else if (MovementVector.Y < 0)
			Mesh->AddForce(Mesh->GetForwardVector() * -5000.0f);
	}
}

void ASandSailPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
	}
}

// Called to bind functionality to input
void ASandSailPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASandSailPlayer::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASandSailPlayer::Look);

	}
}

