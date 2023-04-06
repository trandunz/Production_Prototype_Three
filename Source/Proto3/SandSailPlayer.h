// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandSailPlayer.generated.h"

UCLASS()
class PROTO3_API ASandSailPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandSailPlayer();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void Pause();

	void SetupGameHUDComponent();

	void CheckForMonuments();

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;
	
public:
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mast;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SailSkele;

	UPROPERTY(EditAnywhere)
	class UWindDirectionalSourceComponent* WindDirection;

	UPROPERTY()
	class UArrowComponent* ArrowComponent;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere)
	float MastRotation {-90.0f};

	UPROPERTY(VisibleAnywhere)
	float Dt{};

	UPROPERTY(VisibleAnywhere)
	float SailLength{0.1};

	UPROPERTY(EditAnywhere)
	float MaxSpeed{1600};

public:
	UPROPERTY(EditAnywhere, Category= UI)
	TSubclassOf<class UGameHUD> GameHUDPrefab;
	UPROPERTY(VisibleAnywhere, Category= UI)
	UGameHUD* GameHUD{nullptr};
};
