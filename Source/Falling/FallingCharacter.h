// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FallingCharacter.generated.h"

UCLASS(config=Game)
class AFallingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AFallingCharacter();
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void Boost();
	void StopBoost();

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/* Various values that can be adjusted to change how the character plays */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float MaxWalk = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float MaxWalkBoost = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float Stamina = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float MaxStamina = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float StaminaRegenRate = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
	float StaminaUsageRate = 6.f;


private:
	void UpdateStamina(float Value);
	void InitializeHUDOverlay();

	bool bBoostIsActive = false;

	FTimerHandle InitilizationTimer;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	class UHUDOverlay* HUDOverlay;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetBoostIsActive() { return bBoostIsActive; }
};

