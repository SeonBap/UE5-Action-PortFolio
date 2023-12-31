#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UImage;

UCLASS()
class UE5_ACTION_PORTFOLIO_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetHPInfo(float _HP, float _MaxHP);
	UFUNCTION(BlueprintCallable)
	void SetHealthBarOnOff(bool _Value);
	
protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UImage* HPBar;
	UImage* MaxHPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility HealthBarOnOff;
};
