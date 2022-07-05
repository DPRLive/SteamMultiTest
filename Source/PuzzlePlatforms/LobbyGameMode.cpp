// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameMapsSettings.h"
#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("PlayerLogin. Now : %d"), PlayerCount);

	if (PlayerCount >= 2)
	{
		GetWorldTimerManager().SetTimer(TimerHandler, this, &ALobbyGameMode::StartGame, 10);
	}
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;

	GameInstance->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AGameModeBase::bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzlePlatform/Maps/Game?listen");
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("PlayerLogout. Now : %d"), PlayerCount);
}

