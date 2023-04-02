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
#include "Blueprint/UserWidget.h"
#include "Controllers/ProtoPlayerController.h"
#include "Widgets/GameHUD.h"
#include "Components/WindDirectionalSourceComponent.h"

// Sets default values
ASandSailPlayer::ASandSailPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mast = CreateDefaultSubobject<UStaticMeshComponent>("Mast");
	Mast->SetupAttachment(RootComponent);
	SailSkele = CreateDefaultSubobject<USkeletalMeshComponent>("SailSkele");
	SailSkele->SetupAttachment(Mast);
	WindDirection = CreateDefaultSubobject<UWindDirectionalSourceComponent>("Wind");
	WindDirection->SetupAttachment(Mast);
	
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

	SetupGameHUDComponent();
}

// Called every frame
void ASandSailPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Dt = DeltaTime;
	MastRotation = FMath::Lerp(MastRotation, 0.0f, Dt);
	Mast->SetRelativeRotation(FRotator{0,MastRotation,0});
	FRotator rotation = Mesh->GetComponentRotation();
	rotation.Yaw = FMath::Lerp(rotation.Yaw, rotation.Yaw + MastRotation, Dt * 2);
	Mesh->SetWorldRotation(rotation);
	Mast->SetRelativeScale3D({SailLength, 1.0f, 1.0f});

	WindDirection->SetSpeed(FMath::Lerp(0.0f, 18.0f, SailLength));
	
	if ((GetVelocity() + ((Mesh->GetForwardVector() * 10000.0f * SailLength) * DeltaTime)).Length() <= MaxSpeed)
		Mesh->AddForce(Mesh->GetForwardVector() * 10000.0f * SailLength);
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
			MastRotation = FMath::Lerp(MastRotation, 90.0f, Dt);
		}
		else if (MovementVector.X < 0)
		{
			MastRotation = FMath::Lerp(MastRotation, -90.f, Dt);
		}
		// add movement
		if (MovementVector.Y > 0)
		{
			SailLength = FMath::Clamp(SailLength + Dt, 0.1f, 1.0f);
			//Mesh->AddForce(Mesh->GetForwardVector() * 10000.0f);
		}
		else if (MovementVector.Y < 0)
		{
			SailLength = FMath::Clamp(SailLength - Dt, 0.1f, 1.0f);
			//Mesh->AddForce(Mesh->GetForwardVector() * -5000.0f);
		}
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

void ASandSailPlayer::Pause()
{
	if (GameHUD)
	{
		GameHUD->EnableDisableMenu();
	}
}

void ASandSailPlayer::SetupGameHUDComponent()
{
	if (auto* playerController = Cast<AProtoPlayerController>(Controller))
	{
		if (GameHUDPrefab && GameHUD == nullptr)
		{
			GameHUD = CreateWidget<UGameHUD>(playerController, GameHUDPrefab);
			GameHUD->AddToViewport();
			playerController->SetInputMode(FInputModeGameOnly{});
		}
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
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ASandSailPlayer::Pause);
	}
}

