// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyMoveingCube.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "VolumeTrigger.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API AVolumeTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVolumeTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UBoxComponent* TriggerVolume;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere)
		TArray<AMyMoveingCube*> MyCubeArr; // 플랫폼이 조종할 큐브를 담을 Array, 엔진 내에서 디테일 패널을 통해 추가할 수 있음
};
