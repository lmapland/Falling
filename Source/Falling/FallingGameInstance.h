// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FallingGameInstance.generated.h"

class USaveGameManager;
class UFallingSaveGame;

UCLASS()
class FALLING_API UFallingGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFallingGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetupSaveManager();

	UFUNCTION(BlueprintCallable)
	USaveGameManager* GetSaveManager();

	UFUNCTION(BlueprintCallable)
	void SaveNewGame(FString GameName);

	UFUNCTION(BlueprintCallable)
	void GetSaveGame(int32 UserIndex);

private:
	USaveGameManager* SaveManager;
	UFallingSaveGame* CurrentSave;
};
