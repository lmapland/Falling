// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHUDOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void UHUDOverlay::SetMeters(int32 Meters)
{
	if (MetersText)
	{
		MetersText->SetText(FText::FromString(FString::Printf(TEXT("%i m"), Meters)));
	}
}