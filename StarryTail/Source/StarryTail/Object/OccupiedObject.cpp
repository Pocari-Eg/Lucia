// Fill out your copyright notice in the Description page of Project Settings.


#include "OccupiedObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AOccupiedObject::AOccupiedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//초기값 세팅
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

	//HP Bar UI 설정 
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
	InEnemyCount = 0;
	DeOccupyNum = 4.0f;
	EnemyOccupyTime = 3.0f;

}

// Called when the game starts or when spawned
void AOccupiedObject::BeginPlay()
{
	Super::BeginPlay();
	//점령지 관련 트리거 델리게이트
	Area->OnComponentBeginOverlap.AddDynamic(this, &AOccupiedObject::OnBeginOverlap);
	Area->OnComponentEndOverlap.AddDynamic(this, &AOccupiedObject::OnEndOverlap);

	//점령 바 띄우기
	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget(0.0f);
		OccupyBar->SetColor(FLinearColor::Yellow);
	}

}

void AOccupiedObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//점령지에 들어온게 플레이어라면
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		//점령지에 이미 몬스터가 있다면 몬스터 점령 해제
		if (IsInEnemy)
		{
			GetWorldTimerManager().ClearTimer(EnemyTimerHandle);

		}
		//현재 점령이 완료 되지 않으면
		if (CurrentOccupy < MaxOccupy) {

			//플레이어 속성과 점령지 속성 비교
			STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
			IsInPlayer = true;
			Player = Cast<AIreneCharacter>(OtherActor);
			CompareAttribute();
			Player->FOnAttributeChange.AddUObject(this, &AOccupiedObject::CompareAttribute);
		}
	}
	//점령지에 들어온게 적이면
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
		//적 카운트 증가
		InEnemyCount++;
		STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
		//적이 점령지에 들어옴을 저장
		IsInEnemy = true;
		if (IsInPlayer == false) {
			//안에 플레이어가 없다면 점령 시작
			GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);
		}
	}

}

//점령지에서 무언가 나가면
void AOccupiedObject::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//나간 물체가 플레이어라면 
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		//점령 해제 
		STARRYLOG(Error, TEXT("AreaOut :  %s"), *OtherComp->GetCollisionProfileName().ToString());
		IsInPlayer = false;
		Player = Cast<AIreneCharacter>(OtherActor);
		//델리게이트 해제
		if (Player->FOnAttributeChange.IsBound() == true) {
			Player->FOnAttributeChange.Clear();
		}
		Player = nullptr;
		IsOccupying = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		if (IsInEnemy == true)
		{
			//점령지에 적이 남아 있다면 점령 빼앗김
			GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);

		}
	}
	//나간 물체가 적이라면 
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
		// 적이 0보다 많이 있었으면 적 카운트 --;
		if (InEnemyCount > 0)
		{
			InEnemyCount--;

			//0이하라묜
			if (InEnemyCount <= 0)
			{
				//점령지에 몬스터가 없음
				IsInEnemy = false;
				InEnemyCount = 0;
				//점령 빼앗는 시간 초기화
				CurrentEnemyTime = EnemyOccupyTime;
				//점령 종료
				GetWorldTimerManager().ClearTimer(EnemyTimerHandle);
			}
		}			
	}
}


void AOccupiedObject::CompareAttribute()
{
	//일단 현재 플레이어 점령 상태 초기화
	GetWorldTimerManager().ClearTimer(TimerHandle);
	if (IsInPlayer == true)
	{	
		PlayerAttribute = Player->GetAttribute();

		//플레이어 속성과 점령지 속성이 동일하면 점령 시작
		if (PlayerAttribute == AreaAttribute)
		{
			IsOccupying = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::Occupying, 1.0f, true, 0.0f);
		}
		else {
			//점령 속성이 다르다면 점령을 종료하고
			//상성 속성으로 존재하면 점령수치 하락
			IsOccupying = false;
			switch (AreaAttribute)
			{
			case EAttributeKeyword::e_Fire:
				if (PlayerAttribute == EAttributeKeyword::e_Water)
				{
					STARRYLOG_S(Error);
					GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);
					
				}
				break;
			case EAttributeKeyword::e_Water:
				if (PlayerAttribute == EAttributeKeyword::e_Thunder)
				{
					GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);

				}
				break;
			case EAttributeKeyword::e_Thunder:
				if (PlayerAttribute == EAttributeKeyword::e_Fire)
				{
					GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);

				}
				break;
			default:
				break;
			}
		}
	}
}

void AOccupiedObject::Occupying()
{
	//현재 점령 수치가 목표 점령수치보다 작으면 점령
	if (CurrentOccupy < MaxOccupy)
	{
		CurrentOccupy += OccupyNum;
	}
	else {
		//아니면 점령중을 종료하고 점령상태로 변경
		GetWorldTimerManager().ClearTimer(TimerHandle);
			IsOccupying = false;
			IsOccupied = true;
			CurrentOccupy = MaxOccupy;
			//짐벌 오브젝트에 점령 했음을 알림
			OnOccupy.Broadcast();
	}

	//점령 게이지 갱신
	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
	}
}

void AOccupiedObject::DeOccupying()
{
	
	//만약 플레이어가 상성 속성이라면 
	if (IsInPlayer==true) {
		STARRYLOG_S(Error);
		//현재 점령 수치가 0보다 크면 점령 수치 하락
		if (CurrentOccupy > 0) {
			CurrentOccupy -= DeOccupyNum;
			auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
			if (OccupyBar != nullptr)
			{
				OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
			}
			//점령 수치가 OccupyCancelNum보다 작아지면 점령 취소
			if (CurrentOccupy < OccupyCancelNum && IsOccupied == true)
			{
				IsOccupied = false;
				OnOccupy.Broadcast();
			}
		}
		else {
			CurrentOccupy = 0;
		}
	}
	else {
		if (CurrentEnemyTime > 0)
		{
			CurrentEnemyTime--;
		}
		else {
			if (CurrentOccupy > 0) {
				CurrentOccupy -= EnemyOccupyNum;
				auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
				if (OccupyBar != nullptr)
				{
					OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
				}
				if (CurrentOccupy < OccupyCancelNum && IsOccupied == true)
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
}

// Called every frame
void AOccupiedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(OccupyBarWidget->GetComponentTransform().GetLocation(),
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	OccupyBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
}

