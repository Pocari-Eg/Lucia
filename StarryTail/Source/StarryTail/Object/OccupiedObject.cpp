// Fill out your copyright notice in the Description page of Project Settings.


#include "OccupiedObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AOccupiedObject::AOccupiedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<USphereComponent>(TEXT("AREA"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Area;

	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	Area->SetCollisionProfileName("Trigger");
	Area->SetSphereRadius(240.0f);
	IsInPlayer = false;
	IsOccupied = false;
	IsOccupying = false;
	Player = nullptr;
	CurrentOccupy = 0;

	//HP Bar UI ¼³Á¤ 
	OccupyBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	OccupyBarWidget->SetupAttachment(Mesh);
	OccupyBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	OccupyBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	OccupyBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_HPBar.BP_HPBar_C"));

	if (UI_HPBARWIDGET.Succeeded()) {

		OccupyBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		OccupyBarWidget->SetDrawSize(FVector2D(150, 50.0f));
	}
	
	CurrentEnemyTime = EnemyOccupyTime;

	MaxOccupy = 100;
	OccupyNum = 14;
	EnemyOccupyNum = 6.5f;
	OccupyCancelNum = 50.0f;
}

// Called when the game starts or when spawned
void AOccupiedObject::BeginPlay()
{
	Super::BeginPlay();
	Area->OnComponentBeginOverlap.AddDynamic(this, &AOccupiedObject::OnBeginOverlap);
	Area->OnComponentEndOverlap.AddDynamic(this, &AOccupiedObject::OnEndOverlap);

	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget(0.0f);
		OccupyBar->SetColor(FLinearColor::Yellow);
	}

}

void AOccupiedObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		if (CurrentOccupy < MaxOccupy) {

			if (IsInEnemy)
			{
				GetWorldTimerManager().ClearTimer(EnemyTimerHandle);

			}
			STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
			IsInPlayer = true;
			Player = Cast<AIreneCharacter>(OtherActor);
			CompareAttribute();
			Player->FOnAttributeChange.AddUObject(this, &AOccupiedObject::CompareAttribute);
		}
	}
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
		
		STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
		IsInEnemy = true;
		if (IsInPlayer == false) {
			GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);
		}
	}
}

void AOccupiedObject::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetCollisionProfileName() == "Player")
	{


			STARRYLOG(Error, TEXT("AreaOut :  %s"), *OtherComp->GetCollisionProfileName().ToString());
			IsInPlayer = false;
			Player = Cast<AIreneCharacter>(OtherActor);
			if (Player->FOnAttributeChange.IsBound()==true) {
				Player->FOnAttributeChange.Clear();
			}
			Player = nullptr;
			IsOccupying = false;
			GetWorldTimerManager().ClearTimer(TimerHandle);
			if (IsInEnemy == true)
			{
				GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);

			}
		

	}
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
	  IsInEnemy = false;
	  CurrentEnemyTime = EnemyOccupyTime;
	  GetWorldTimerManager().ClearTimer(EnemyTimerHandle);

	}
}

void AOccupiedObject::CompareAttribute()
{
	if (IsInPlayer == true)
	{	
		PlayerAttribute = Player->GetAttribute();
		PlayerAttribute == AreaAttribute ? IsOccupying = true : IsOccupying = false;
	}
	else {
	}

	if (IsOccupying == true)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::Occupying, 1.0f, true, 0.0f);
	}
	else {
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AOccupiedObject::Occupying()
{

	if (CurrentOccupy < MaxOccupy)
	{
		CurrentOccupy += OccupyNum;
	}
	else {
		GetWorldTimerManager().ClearTimer(TimerHandle);
			IsOccupying = false;
			IsOccupied = true;
			CurrentOccupy = MaxOccupy;
			OnOccupy.Broadcast();
	}


	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget(((float)CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f :(float) CurrentOccupy / (float)MaxOccupy);
	}
	

}

void AOccupiedObject::DeOccupying()
{
	if (CurrentEnemyTime > 0)
	{
		CurrentEnemyTime--;
	}
	else {
		if (CurrentOccupy >= 0+EnemyOccupyNum) {
			CurrentOccupy -= EnemyOccupyNum;
			auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
			if (OccupyBar != nullptr)
			{
				OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
			}
			if (CurrentOccupy < OccupyCancelNum&&IsOccupied==true)
			{
				IsOccupied = false;
				OnOccupy.Broadcast();

			}
		}
		else {

			CurrentOccupy = 0;
		}
	

	}
}

// Called every frame
void AOccupiedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(OccupyBarWidget->GetComponentTransform().GetLocation(),
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	OccupyBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
}

