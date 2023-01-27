// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDOverlay.generated.h"

/**
 * 
 */
UCLASS()
class FALLING_API UHUDOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetStaminaBarPercent(float Percent);
	void SetMeters(int32 Meters);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MetersText;
};
