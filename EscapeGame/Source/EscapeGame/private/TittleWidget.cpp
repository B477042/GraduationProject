// Fill out your copyright notice in the Description page of Project Settings.


#include "TittleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTittleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	
}

void UTittleWidget::StartNew()
{
	EGLOG(Warning, TEXT("Click!"));
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());

	//GetWorld()->playercon

	FName LevelName = TEXT("/Game/MyFolder/Maps/Stage1");
	//FString LevelOption = TEXT("Class'/Script/EscapeGame.EscapeGameGameModeBase_C'");
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TrapMaking"));
	//FURL EGModeUrl(TEXT("Class'/Script/EscapeGame.EscapeGameGameModeBase_C'"));
	//EGLOG(Error,TEXT("furl : %s"),*EGModeUrl.)

	//GetWorld()->SetGameMode(EGModeUrl);
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	
	
}

void UTittleWidget::LoadGame()
{
	EGLOG(Warning, TEXT("Click!"));
}

void UTittleWidget::OpenOption()
{
	EGLOG(Warning, TEXT("Click!"));
}

void UTittleWidget::ExitGame()
{
	EGLOG(Warning, TEXT("Click!"));
}
