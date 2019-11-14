// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "BallProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"

// Sets default values
AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	//FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));	
	
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

}

	void AGun::OnFire()
	{
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				
					const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

					//Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// spawn the projectile at the muzzle
					World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				
			}
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation1P != nullptr && AnimInstance1P != nullptr)
		{
			// Get the animation object for the arms mesh
			AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);

			if (FireAnimation3P != nullptr && AnimInstance3P != nullptr)
			{
				AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
			}
		}
	}
