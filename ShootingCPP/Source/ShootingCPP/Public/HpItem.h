// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HpItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()

class SHOOTINGCPP_API AHpItem : public AActor
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	AHpItem();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> boxComp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshComp;


	//UPROPERTY(EditDefaultsOnly)
	//int32 traceRate = 50;

	UPROPERTY(EditDefaultsOnly)
	float moveSpeed = 800.0f;


	UFUNCTION()
	void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	private:
	FVector dir;

};
