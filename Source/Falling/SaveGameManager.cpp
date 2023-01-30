// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "FallingSaveGame.h"
#include "SaveGameMetaData.h"


USaveGameManager::USaveGameManager()
{
	/* Used to clear the MetaData
	if (MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::LoadGameFromSlot(TEXT("MetaData"), 0)))
	{
		MetaDataInstance->MetaData.UserIndexes.Empty();
		MetaDataInstance->MetaData.UserNames.Empty();
		UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0);
	} */
	

	if (MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::LoadGameFromSlot(TEXT("MetaData"), 0)))
	{
		NextOpenSaveSlot = MetaDataInstance->MetaData.UserIndexes.Num() + 1;
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager(): Meta Data exists; loading it; has %i records"), NextOpenSaveSlot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager(): Meta Data doesn't exist; creating a new one"));
		MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::CreateSaveGameObject(USaveGameMetaData::StaticClass()));

		if (MetaDataInstance)
		{
			UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager() Trying to load the MetaDataInstance but something went wrong"));
		}
	}
}

// saves and loads game
UFallingSaveGame* USaveGameManager::SaveNewGame(FString GameName)
{
	if (UFallingSaveGame* SaveGameInstance = Cast<UFallingSaveGame>(UGameplayStatics::CreateSaveGameObject(UFallingSaveGame::StaticClass())))
	{
		// Add data to our new SGI
		SaveGameInstance->SaveGameData.UserIndex = NextOpenSaveSlot;
		SaveGameInstance->SaveGameData.SaveSlotName = GameName;
		// TODO get the CreatedDate and save that as well

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveGameData.SaveSlotName, SaveGameInstance->SaveGameData.UserIndex);
		AddMetaDataRecord(SaveGameInstance);
		CurrentSave = SaveGameInstance;
		NextOpenSaveSlot++;

		return SaveGameInstance;
	}

	UE_LOG(LogTemp, Warning, TEXT("In SaveNewGame(): Couldn't create a save game object"));
	return nullptr;
}

// Assume we're being passed the real UserIndex, aka, a 1-based value
UFallingSaveGame* USaveGameManager::GetSaveGame(int32 UserIndex)
{
	// bounds checking
	/*if (UserIndex > MetaDataInstance->Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("In GetSaveGame(): Requested game to load is out of bounds of MetaDataInstance arrays. Requested: %i | Max array size: %i"), UserIndex, MetaDataInstance->Num());
		return nullptr;
	}*/

	// load the current save game and return it
	TArray<FString> CurrentRecord = GetMetaDataRecord(UserIndex - 1);
	if (CurrentRecord.Num() > 0)
	{
		if (UFallingSaveGame* SaveGameInstance = Cast<UFallingSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentRecord[1], UserIndex)))
		{
			return SaveGameInstance;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::GetSaveGame(): Something went wrong getting the saved game"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::GetSaveGame(): Something went wrong in MetaData::GetRecord()"));
	}

	return nullptr;
}

// We assume here that the game to update is the currently loaded game. If this is a false assumption the code will need to change
void USaveGameManager::UpdateSaveGame(UFallingSaveGame* Game)
{
	// bounds checking
	/*if (CurrentSaveSlot > MetaDataInstance->Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::UpdateSaveGame(): Requested saved game is out of bounds of MetaDataInstance arrays. Requested: %i | Max array size: %i"), CurrentSaveSlot, MetaDataInstance->Num());
		return;
	}*/

	/*
	// load the current save game based on CurrentSaveSlot
	CurrentSave = Game;
	//CurrentSave->UserIndex = Game->UserIndex;
	//CurrentSave->SaveSlotName = Game->SaveSlotName;
	//CurrentSave->CreatedDate = Game->CreatedDate;
	//CurrentSave->LevelsCompleted = Game->LevelsCompleted;
	// go through elements of Game and update them
	if (!UGameplayStatics::SaveGameToSlot(Game, CurrentSave->SaveSlotName, CurrentSave->UserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("In UpdateSaveGame(): Something went wrong updating the save game"));
	}

	UpdateMetaData(Game);
	*/
}

// This is called from the UserWidget so it will input a 0-based array. No conversion necessary
TArray<FString> USaveGameManager::GetMetaDataRecord(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("There are %i records"), NumSaveGames());
	TArray<FString> ReturnArray;
	if (Index >= MetaDataInstance->MetaData.UserIndexes.Num()) return ReturnArray;
	FString UIndex("");
	UIndex.AppendInt(MetaDataInstance->MetaData.UserIndexes[Index]);

	ReturnArray.Add(UIndex);
	ReturnArray.Add(MetaDataInstance->MetaData.UserNames[Index]);
	//ReturnArray.Add(MetaDataInstance->MetaData.CreatedDate[OurIndex]);
	//ReturnArray.Add(MetaDataInstance->MetaData.LevelsCompletedString[OurIndex]);

	return ReturnArray;
}

void USaveGameManager::UpdateMetaData(UFallingSaveGame* Game)
{
	/*
	if (MetaDataInstance)
	{

		UE_LOG(LogTemp, Warning, TEXT("In USaveGameMetaData::UpdateRecord()"));
		// update the info that it needs
		UserIndexes[Game->UserIndex - 1] = Game->UserIndex;
		UserNames[Game->UserIndex - 1] = &Game->SaveSlotName;
		//LevelsCompleted[OurIndex] = Game->LevelsCompleted;
		//FString CompletedString = FString(TEXT("Completed %i Levels"), LevelsCompleted[OurIndex]);
		//LevelsCompletedString[OurIndex] = &CompletedString;

		// TODO does this work?
		MetaDataInstance->MetaData.UserNames = UserNames;
		MetaDataInstance->MetaData.UserIndexes = UserIndexes;
		if (!UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::UpdateMetaData(): Something went wrong saving the metadata"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::UpdateMetaData(): Something went wrong updating the meta data"));
	}
	*/
}

void USaveGameManager::AddMetaDataRecord(UFallingSaveGame* Game)
{
	if (MetaDataInstance)
	{
		MetaDataInstance->MetaData.UserNames.Add(Game->SaveGameData.SaveSlotName);
		MetaDataInstance->MetaData.UserIndexes.Add(Game->SaveGameData.UserIndex);

		if (!UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Something went wrong saving the metadata"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Successfully saved the metadata; loading new one now"));
			MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::LoadGameFromSlot(TEXT("MetaData"), 0));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Something went wrong updating the meta data"));
	}
}
