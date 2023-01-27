// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaBarComponent.h"
#include "StaminaBar.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"

void UStaminaBarComponent::SetStaminaPercent(float Percent)
{
	if (StaminaBarWidget == nullptr)
	{
		StaminaBarWidget = Cast<UStaminaBar>(GetUserWidgetObject());
	}

	if (StaminaBarWidget && StaminaBarWidget->StaminaBar)
	{
		if (Percent < 0.f) Percent = 0.f;
		if (Percent > 100.f) Percent = 100.f;

		StaminaBarWidget->StaminaBar->SetPercent(Percent);
	}
}