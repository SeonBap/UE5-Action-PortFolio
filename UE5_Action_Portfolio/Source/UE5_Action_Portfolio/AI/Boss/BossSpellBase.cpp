#include "AI/Boss/BossSpellBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABossSpellBase::ABossSpellBase()
{
	PrimaryActorTick.bCanEverTick = true;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
}

void ABossSpellBase::SetDeathCheck(bool _Value)
{
	DeathCheck = _Value;
}

bool ABossSpellBase::GetDeathCheck()
{
	return DeathCheck;
}

void ABossSpellBase::SetSpeed(float _Value)
{
	Speed = _Value;
}

float ABossSpellBase::GetSpeed()
{
	return Speed;
}

void ABossSpellBase::SetCurController(AController* _Controller)
{
	if (false == IsValid(_Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
		return;
	}

	CurController = _Controller;
}

AController* ABossSpellBase::GetCurController()
{
	return CurController;
}

UNiagaraComponent* ABossSpellBase::GetNiagaraComponent()
{
	return NiagaraComponent;
}

void ABossSpellBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABossSpellBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == GetDeathCheck())
	{
		DeathTime -= DeltaTime;
	}

	if (0.0f >= DeathTime)
	{
		Destroy();
		return;
	}
}

