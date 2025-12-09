// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"


class UMainWidget;

class UMenuWidget;

class APlayerPawn;

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddScore(int32 point);
	void PrintHealth();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> menuWidget;

	void ShowMenu();

	float curTime;

	int32 gameLevel;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



private:
	int32 currentScore = 0;
	
	TObjectPtr<UMainWidget> mainUI;


	TObjectPtr<UMenuWidget> menuUI;

	void PrintScore();

	

	

};
