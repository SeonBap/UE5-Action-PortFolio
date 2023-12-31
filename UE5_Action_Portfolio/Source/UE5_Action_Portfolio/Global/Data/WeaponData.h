#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Global/Enums.h"
#include "PaperSprite.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct UE5_ACTION_PORTFOLIO_API FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UPaperSprite* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USkeletalMesh* WeaponMesh;
};
