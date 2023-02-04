// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "FallingSaveGame.h"
#include "SaveGameMetaData.h"
#include "Misc/DateTime.h"


USaveGameManager::USaveGameManager()
{
	// Used to clear the MetaData
	/*if (MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::LoadGameFromSlot(TEXT("MetaData"), 0)))
	{
		MetaDataInstance->MetaData.UserIndexes.Empty();
		MetaDataInstance->MetaData.UserNames.Empty();
		MetaDataInstance->MetaData.CreatedDate.Empty();
		MetaDataInstance->MetaData.LevelsCompleted.Empty();
		MetaDataInstance->MetaData.LevelsCompletedString.Empty();
		UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0);
	}*/
	

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

/*
* When this function is called, we're not only saving and returning the requested FallingSaveGame
*  but setting it (in the FallingGameInstance) as the current game being played.
*/
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

/*
* Note that UserIndex is a 1-based value as it represents the slot the game is actually stored in.
* When this function is called, we're not only returning the requested FallingSaveGame but setting it
*  (in the FallingGameInstance) as the current game being played.
* TODO change the name of this function to LoadSaveGame
*/
UFallingSaveGame* USaveGameManager::GetSaveGame(int32 UserIndex)
{
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
	CurrentSave = Game;
	if (!UGameplayStatics::SaveGameToSlot(Game, CurrentSave->SaveGameData.SaveSlotName, CurrentSave->SaveGameData.UserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("In UpdateSaveGame(): Something went wrong updating the save game"));
	}

	UpdateMetaData(Game);
}

/*
* This is called from the UserWidget so it will input a 0-based array. No conversion necessary.
* This doesn't return the # of levels, just the associated string. It could, though, but right now
*  it doesn't need to.
*/
TArray<FString> USaveGameManager::GetMetaDataRecord(int32 Index)
{
	TArray<FString> ReturnArray;
	if (Index >= MetaDataInstance->MetaData.UserIndexes.Num()) return ReturnArray;
	FString UIndex("");
	UIndex.AppendInt(MetaDataInstance->MetaData.UserIndexes[Index]);

	//ReturnArray.Add(UIndex);
	ReturnArray.Add(FString(*UIndex));
	ReturnArray.Add(MetaDataInstance->MetaData.UserNames[Index]);
	ReturnArray.Add(MetaDataInstance->MetaData.CreatedDate[Index]);
	ReturnArray.Add(MetaDataInstance->MetaData.LevelsCompletedString[Index]);

	return ReturnArray;
}

/*
* Note: doesn't update the CreatedDate on the basis that the object is already created.
*/
void USaveGameManager::UpdateMetaData(UFallingSaveGame* Game)
{
	if (MetaDataInstance)
	{
		int32 Index = Game->SaveGameData.UserIndex - 1;
		MetaDataInstance->MetaData.UserNames[Index] = Game->SaveGameData.SaveSlotName;
		MetaDataInstance->MetaData.LevelsCompleted[Index] = Game->SaveGameData.LevelsCompleted;
		// TODO should probably be a function
		MetaDataInstance->MetaData.LevelsCompletedString[Index] = FString(TEXT("Completed %i Levels"), Game->SaveGameData.LevelsCompleted);

		if (!UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::UpdateMetaData(): Something went wrong saving the metadata"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::UpdateMetaData(): Something went wrong updating the meta data"));
	}
}

/*
* I've decided to get the DateTime and then store it as a string for no particular reason.
* If one wanted to store it as an FDateTime and ToString() it in the Getter function, that works too.
*/
void USaveGameManager::AddMetaDataRecord(UFallingSaveGame* Game)
{
	if (MetaDataInstance)
	{
		MetaDataInstance->MetaData.UserNames.Add(Game->SaveGameData.SaveSlotName);
		MetaDataInstance->MetaData.UserIndexes.Add(Game->SaveGameData.UserIndex);
		MetaDataInstance->MetaData.CreatedDate.Add(FDateTime::Today().ToString(TEXT("%Y-%m-%d")));
		MetaDataInstance->MetaData.LevelsCompleted.Add(0);
		MetaDataInstance->MetaData.LevelsCompletedString.Add(TEXT("Completed 0 Levels"));

		if (!UGameplayStatics::SaveGameToSlot(MetaDataInstance, TEXT("MetaData"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Something went wrong saving the metadata"));
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Successfully saved the metadata; loading new one now"));
			MetaDataInstance = Cast<USaveGameMetaData>(UGameplayStatics::LoadGameFromSlot(TEXT("MetaData"), 0));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In USaveGameManager::AddMetaDataRecord(): Something went wrong updating the meta data"));
	}
}
