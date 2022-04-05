// Fill out your copyright notice in the Description page of Project Settings.


#include "OccupiedObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AOccupiedObject::AOccupiedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//�ʱⰪ ����
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

	//HP Bar UI ���� 
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
	//������ ���� Ʈ���� ��������Ʈ
	Area->OnComponentBeginOverlap.AddDynamic(this, &AOccupiedObject::OnBeginOverlap);
	Area->OnComponentEndOverlap.AddDynamic(this, &AOccupiedObject::OnEndOverlap);

	//���� �� ����
	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget(0.0f);
		OccupyBar->SetColor(FLinearColor::Yellow);
	}

}

void AOccupiedObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�������� ���°� �÷��̾���
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		//�������� �̹� ���Ͱ� �ִٸ� ���� ���� ����
		if (IsInEnemy)
		{
			GetWorldTimerManager().ClearTimer(EnemyTimerHandle);

		}
		//���� ������ �Ϸ� ���� ������
		if (CurrentOccupy < MaxOccupy) {

			//�÷��̾� �Ӽ��� ������ �Ӽ� ��
			STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
			IsInPlayer = true;
			Player = Cast<AIreneCharacter>(OtherActor);
			CompareAttribute();
			Player->FOnAttributeChange.AddUObject(this, &AOccupiedObject::CompareAttribute);
		}
	}
	//�������� ���°� ���̸�
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
		//�� ī��Ʈ ����
		InEnemyCount++;
		STARRYLOG(Error, TEXT("AreaIn :%s"), *OtherComp->GetCollisionProfileName().ToString());
		//���� �������� ������ ����
		IsInEnemy = true;
		if (IsInPlayer == false) {
			//�ȿ� �÷��̾ ���ٸ� ���� ����
			GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);
		}
	}

}

//���������� ���� ������
void AOccupiedObject::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//���� ��ü�� �÷��̾��� 
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		//���� ���� 
		STARRYLOG(Error, TEXT("AreaOut :  %s"), *OtherComp->GetCollisionProfileName().ToString());
		IsInPlayer = false;
		Player = Cast<AIreneCharacter>(OtherActor);
		//��������Ʈ ����
		if (Player->FOnAttributeChange.IsBound() == true) {
			Player->FOnAttributeChange.Clear();
		}
		Player = nullptr;
		IsOccupying = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		if (IsInEnemy == true)
		{
			//�������� ���� ���� �ִٸ� ���� ���ѱ�
			GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AOccupiedObject::DeOccupying, 1.0f, true, 0.0f);

		}
	}
	//���� ��ü�� ���̶�� 
	if (OtherComp->GetCollisionProfileName() == "Enemy")
	{
		// ���� 0���� ���� �־����� �� ī��Ʈ --;
		if (InEnemyCount > 0)
		{
			InEnemyCount--;

			//0���϶�
			if (InEnemyCount <= 0)
			{
				//�������� ���Ͱ� ����
				IsInEnemy = false;
				InEnemyCount = 0;
				//���� ���Ѵ� �ð� �ʱ�ȭ
				CurrentEnemyTime = EnemyOccupyTime;
				//���� ����
				GetWorldTimerManager().ClearTimer(EnemyTimerHandle);
			}
		}			
	}
}


void AOccupiedObject::CompareAttribute()
{
	//�ϴ� ���� �÷��̾� ���� ���� �ʱ�ȭ
	GetWorldTimerManager().ClearTimer(TimerHandle);
	if (IsInPlayer == true)
	{	
		PlayerAttribute = Player->GetAttribute();

		//�÷��̾� �Ӽ��� ������ �Ӽ��� �����ϸ� ���� ����
		if (PlayerAttribute == AreaAttribute)
		{
			IsOccupying = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AOccupiedObject::Occupying, 1.0f, true, 0.0f);
		}
		else {
			//���� �Ӽ��� �ٸ��ٸ� ������ �����ϰ�
			//�� �Ӽ����� �����ϸ� ���ɼ�ġ �϶�
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
	//���� ���� ��ġ�� ��ǥ ���ɼ�ġ���� ������ ����
	if (CurrentOccupy < MaxOccupy)
	{
		CurrentOccupy += OccupyNum;
	}
	else {
		//�ƴϸ� �������� �����ϰ� ���ɻ��·� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
			IsOccupying = false;
			IsOccupied = true;
			CurrentOccupy = MaxOccupy;
			//���� ������Ʈ�� ���� ������ �˸�
			OnOccupy.Broadcast();
	}

	//���� ������ ����
	auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
	if (OccupyBar != nullptr)
	{
		OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
	}
}

void AOccupiedObject::DeOccupying()
{
	
	//���� �÷��̾ �� �Ӽ��̶�� 
	if (IsInPlayer==true) {
		STARRYLOG_S(Error);
		//���� ���� ��ġ�� 0���� ũ�� ���� ��ġ �϶�
		if (CurrentOccupy > 0) {
			CurrentOccupy -= DeOccupyNum;
			auto OccupyBar = Cast<UHPBarWidget>(OccupyBarWidget->GetWidget());
			if (OccupyBar != nullptr)
			{
				OccupyBar->UpdateWidget((CurrentOccupy < KINDA_SMALL_NUMBER) ? 0.0f : CurrentOccupy / MaxOccupy);
			}
			//���� ��ġ�� OccupyCancelNum���� �۾����� ���� ���
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

