// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "MenuWidget.h"	
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"
#include "EnemyActor.h"

void AShootingGameModeBase::BeginPlay() {

	Super::BeginPlay();

	

	if (mainWidget != nullptr) {
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);


		if (mainUI != nullptr) {
			mainUI->AddToViewport();
			PrintScore();
			PrintHealth();
		}

	}





}


void AShootingGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. float 변수에 DeltaTime 누적 (스톱워치 역할)
	curTime += DeltaTime;

	if (curTime <= 30.0f)
	{
		gameLevel = 1;

		
	}
	else if (curTime <= 50.0f) {
		
		gameLevel = 2;
	}
	else {
		gameLevel = 3;

	}
}



void AShootingGameModeBase::AddScore(int32 point) {
	currentScore += point;
	PrintScore();
}


void AShootingGameModeBase::PrintScore() {

	if (mainUI != nullptr) {

		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}

}

void AShootingGameModeBase::PrintHealth() {
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (mainUI != nullptr) {

		int32 curHp = PlayerPawn->GetCurrentHealth();
		mainUI->healthData->SetText(FText::AsNumber(curHp));
	}

}

void AShootingGameModeBase::ShowMenu() {

	if (menuWidget != nullptr) {

		menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

		if (menuUI != nullptr) {
			menuUI->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);


			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);




		}


	}



}