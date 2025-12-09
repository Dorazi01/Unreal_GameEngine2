// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Delegates/Delegate.h"
#include "PlayerPawn.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;
class UArrowComponent;
class USoundBase;

struct FInputActionValue;


UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		class AActor* DamageCauser
	) override;

	float TakeHeal(float HealAmount);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, int32, NewHealth);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChangedDelegate;


	UFUNCTION(BlueprintPure)
	int32 GetCurrentHealth() const { return curHp; }

	//언리얼 권장 포인터 선언은 위쪽에 전역선언 후 사용

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UBoxComponent> boxComp;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> meshComp;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 500;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> imc_playerInput;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ia_horizontal;

	UPROPERTY(EditAnywhere)
	TObjectPtr <UInputAction> ia_vertical;


	UPROPERTY(EditAnywhere)
	TObjectPtr <UInputAction> ia_fire;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UArrowComponent> firePosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> fireSound;

private:

	float h;
	float v;

	int32 maxHp = 3;
	int32 curHp = 3;
	//유니티 뉴인풋 sendMessage 인자값과 동일함 FInputActionValue& value::

	void OnInputHorizontal(const FInputActionValue& value);
	void OnInputVertical(const FInputActionValue& value);

	void Fire();


};
