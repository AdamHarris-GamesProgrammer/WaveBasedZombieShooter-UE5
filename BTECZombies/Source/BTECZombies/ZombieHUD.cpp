// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieHUD.h"

void AZombieHUD::DrawHUD()
{
	Super::DrawHUD();

	if (_pCrosshairTexture) {
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		FVector2D CrossHairDrawPosition(Center.X - (_pCrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (_pCrosshairTexture->GetSurfaceHeight() * 0.5f));

		FCanvasTileItem TileItem(CrossHairDrawPosition, _pCrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
