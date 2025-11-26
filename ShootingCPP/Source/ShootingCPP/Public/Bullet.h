// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;

//추후 확인
//DECLARE_DYNAMIC_DELEGATE(FOnsad);

UCLASS()
class SHOOTINGCPP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> boxComp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> explosionFX;

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
