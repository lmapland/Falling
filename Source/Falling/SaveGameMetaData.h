// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameMetaData.generated.h"

USTRUCT(BlueprintType)
struct FSavedGameMetaData
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	TArray<int32> UserIndexes;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	TArray<FString> UserNames;
	/*UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FRotator Rotation;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString WeaponName;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	bool NeedsReload;*/
};

/**
 * 
 */
UCLASS()
class FALLING_API USaveGameMetaData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FSavedGameMetaData MetaData;

};
