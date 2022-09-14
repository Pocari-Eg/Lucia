// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ScriptDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FScriptData : public FTableRowBase {

	GENERATED_BODY();
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	int32 Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	int32 Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	FText Img;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	int32 Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	float R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	float G;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	float B;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	int32 Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script");
	FString String;

};
UCLASS()
class STARRYTAIL_API UScriptDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
