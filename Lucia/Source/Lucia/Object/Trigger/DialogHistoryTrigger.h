// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogHistoryTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndPlaySequence);

UENUM(BlueprintType)
enum class EConditions : uint8
{
	RightAway, PushInteraction
};

UCLASS()
class LUCIA_API ADialogHistoryTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	//충돌 트리거
	UPROPERTY(EditAnywhere, Category = Trigger)
		class UBoxComponent* Trigger;
	//메쉬
	UPROPERTY(EditAnywhere, Category = Trigger)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Dialog)
		TArray<FString> DalogIndex;

	UPROPERTY(BlueprintAssignable)
	FEndPlaySequence PlaySeq;

	UPROPERTY(EditAnyWhere)
	EConditions _condition;

	bool IsAlready;

private:
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> Dialogue_C;
	UPROPERTY(EditAnyWhere)
	class UDataTable* ScriptData;

	class UDialogHistoryWidget_D* makeDialogue;

	FString Start_, End_;

public:
	ADialogHistoryTrigger();

	UFUNCTION(BlueprintCallable)
	void SetDefaultObject(FString Start, FString End);

	//충돌 체크
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;


};
