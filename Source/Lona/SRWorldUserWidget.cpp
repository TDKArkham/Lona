// Fill out your copyright notice in the Description page of Project Settings.


#include "SRWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USRWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D ScreenPosition;
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PC)
	{
		PC->GetMousePosition(ScreenPosition.X, ScreenPosition.Y);
		float ScreenScale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= ScreenScale;
		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
