// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FallingHUD.generated.h"

class UHUDOverlay;

/**
 * 
 */
UCLASS()
class FALLING_API AFallingHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Falling)
	TSubclassOf<UHUDOverlay> HUDOverlayClass;

	UPROPERTY()
	UHUDOverlay* HUDOverlay;

public:
	FORCEINLINE UHUDOverlay* GetHUDOverlay() const { return HUDOverlay; }
};
