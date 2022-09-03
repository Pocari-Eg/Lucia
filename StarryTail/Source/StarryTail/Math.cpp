// Fill out your copyright notice in the Description page of Project Settings.


#include "Math.h"

Math::Math()
{
}

Math::~Math()
{
}
 FQuat Math::VectorA2BRotation(FVector VectorA, FVector VectorB)
{
	VectorA.Normalize();
	VectorB.Normalize();
	
	float dot = FVector::DotProduct(VectorA, VectorB);
	float fRadian = FMath::Acos(dot);
	
	if (PI - fRadian < 0.01f) {
		VectorA.X += 0.01f;
		VectorA.Y += 0.01f;
		VectorA.Z += 0.01f;
	}
	FVector vCross = FVector::CrossProduct(VectorA, VectorB);
	
	vCross.Normalize();
	
	float fTheta = FMath::Sin(fRadian/2.0f);
	
	float x = vCross.X * fTheta;
	float y = vCross.Y * fTheta;
	float z = vCross.Z * fTheta;
	float w = FMath::Cos(fRadian / 2.0f);
	
		return FQuat(x, y, z, w);
}
