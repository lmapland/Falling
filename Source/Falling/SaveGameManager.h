// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameManager.generated.h"

class UFallingSaveGame;
class USaveGameMetaData;

/*
* An instance of this class will be owned by the Game Instance
* This class relies heavily on the CurrentSaveSlot variable to know which save game slot it is interacting with
* If the user picks to start a new game, this class will choose the next available slot and set that in this class and return it to the GI
* If the user loads an existing game, the GI will set that variable and then pass it to getsavegame(), and this class will set the var
*/
UCLASS()
class FALLING_API USaveGameManager : public UObject
{
	GENERATED_BODY()
	
public:
	USaveGameManager();

	UFallingSaveGame* SaveNewGame(FString GameName); // create

	UFallingSaveGame* GetSaveGame(int32 UserIndex); // read

	UFUNCTION(BlueprintCallable)
	void UpdateSaveGame(UFallingSaveGame* Game); // update

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetMetaDataRecord(int32 Index);

private:
	void UpdateMetaData(UFallingSaveGame* Game);
	void AddMetaDataRecord(UFallingSaveGame* Game);

	/* The game we are using right now: 0 if no game is in use (user selection screen when the game first starts) */
	int32 CurrentSaveSlot = 0;

	/* UserIndex where a New game can be saved */
	int32 NextOpenSaveSlot = 1;
	
	USaveGameMetaData* MetaDataInstance;

	/* copy of the currently running save game */
	UFallingSaveGame* CurrentSave;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 NumSaveGames() const { return NextOpenSaveSlot - 1; }
};
