// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingGameInstance.h"
#include "SaveGameManager.h"
#include "FallingSaveGame.h"

/*
* This GameInstance gets instantiated on editor startup
* I specifically hold off instantiating the SaveGameManager because creating it in the contructor was causing undefined behavior
*/
UFallingGameInstance::UFallingGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::UFallingGameInstance(): Instantiating"));
}

USaveGameManager* UFallingGameInstance::GetSaveManager()
{
	UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::GetSaveManager(): About to return the SaveManager"));
	if (!SaveManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::GetSaveManager(): SaveManager is not initialized; setting it up now"));
		SetupSaveManager();
	}
	return SaveManager;
}

void UFallingGameInstance::SaveNewGame(FString GameName)
{
	if (!SaveManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::SaveNewGame(): SaveManager is not initialized; setting it up now"));
		SetupSaveManager();
	}

	CurrentSave = SaveManager->SaveNewGame(GameName);
}

void UFallingGameInstance::GetSaveGame(int32 UserIndex)
{
	if (!SaveManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::GetSaveGame(): SaveManager is not initialized; setting it up now"));
		SetupSaveManager();
	}

	CurrentSave = SaveManager->GetSaveGame(UserIndex);
}

void UFallingGameInstance::SetupSaveManager()
{
	UE_LOG(LogTemp, Warning, TEXT("In UFallingGameInstance::SetupSaveManager(): About to initialize the SaveManager"));
	SaveManager = NewObject<USaveGameManager>(USaveGameManager::StaticClass());
}

FString UFallingGameInstance::GetUserName()
{
	return CurrentSave->SaveGameData.SaveSlotName;
}
