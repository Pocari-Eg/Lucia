// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FAttributeDebuff.generated.h"


USTRUCT(Atomic, BluePrintType)
struct FAttributeDebuff
{
	GENERATED_USTRUCT_BODY()
public:
	//ȭ�� ����� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnCycle; // ȭ�� ������ �޴� ƽ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnDamage; // ȭ�� ������ ��� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnTime; // ȭ�� ���ӽð�
	float BurnCycleTimer; // ȭ�� ������ ƽ ���� ƽ �Լ����� �����ϴ� ��
	float BurnTimer; // ȭ�� ���ӽð� ���� ƽ �Լ����� �����ϴ� ��

	//ħ�� ����� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloodingTime; // ħ������ ���ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloodingDebuffSpeedReductionValue; // �ӵ� ���� ��ġ
	float FloodingTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkReduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkTime;
	float SparkTimer;
	
	/*
	//���� ����� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShockTime;
	float ShockTimer;

	
	//���� ����� ��ø ȿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TransitionRange;

	//Assemble ȿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleRange; // Assemble ȿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleTime; // Assemble ȿ�� ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleSpeed; // Assemble ȿ�� �������� ��
	float AssembleTimer; // ���ӽð� ��� ����

	//Chain ȿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChainRange; // Chain ȿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChainSpeed; // Chain ȿ�� ���̼ӵ�
	*/
public:
	//���Һ� ����� ��ø 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int FireDebuffStack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int WaterDebuffStack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ThunderDebuffStack;
};


