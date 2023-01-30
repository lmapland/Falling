// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FallingSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FRegularSaveGame
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 UserIndex;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString CreatedDate;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 LevelsCompleted;
	/* this is the list of all levels in the gameand the word that represents their state to the user
	 * <1, "Completed>,<2, "Open">,<3, "Not Available">; stuff like that.
	 * It allows levels to be completed out of order, like level 4 might be the bonus challenge level that the user has Open.
	 * So the user has completed 4 levels, but they could be levels 1,2,3,5 or 1,2,3,4
	 * Might be better to store an int for status, though. 0 is Not Available, 1 is completed, 2 is Open.
	*/
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	TMap<int32, FString> LevelMap;
};

/**
 * 
 */
UCLASS()
class FALLING_API UFallingSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFallingSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRegularSaveGame SaveGameData;

	/*
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 UserIndex = -1;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString CreatedDate = TEXT("");

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 LevelsCompleted = 0;

	
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	TMap<int32, FString> LevelMap;
	*/
};
