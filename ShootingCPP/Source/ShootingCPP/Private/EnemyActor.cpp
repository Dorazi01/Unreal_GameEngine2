// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "ShootingGameModeBase.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	meshComp->SetupAttachment(boxComp);

	boxComp->SetCollisionProfileName(TEXT("Enemy"));




}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();


	int32 drawResult = FMath::RandRange(1, 100);

	if (drawResult <= traceRate) {


		//월드 공간에 APlayerPawn클래스로 된 액터를 모두 검색한다?

		//Object.FindObjectsOfType<T>()와 똑같이 구현가능

		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player){

			if (player->GetName().Contains(TEXT("BP_PlayerPawn"))) {
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}

			
		}


	}
	else {
		dir = GetActorForwardVector();


	}

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);




}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);


}


void AEnemyActor::OnEnemyOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);

	if (player != nullptr) {
		OtherActor->Destroy();

		AShootingGameModeBase* currentGameMode = Cast<AShootingGameModeBase>(GetWorld()->GetAuthGameMode());


		if (currentGameMode != nullptr) {


			currentGameMode->ShowMenu();

		}

	}

	Destroy();
}
