// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "StaminaBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class FALLING_API UStaminaBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetStaminaPercent(float Percent);


private:
	UPROPERTY()
	class UStaminaBar* StaminaBarWidget;
};
