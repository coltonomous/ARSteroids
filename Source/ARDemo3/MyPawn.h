#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Runtime/AugmentedReality/Public/ARBlueprintLibrary.h"
#include "Runtime/AugmentedReality/Public/ARSessionConfig.h"
#include "MyPawn.generated.h"


// This class defines the behavior of the player and camera, including the control inputs for
// mobile and keyboard + mouse.
UCLASS()
class ARDEMO3_API AMyPawn : public APawn
{
    // Required UE4 macro for unreal header code
    GENERATED_BODY()
    
public:
    // Sets default values for this pawn's properties
    AMyPawn();
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Camera look controls for both device and keyboard and mouse
    void LookUp(float);
    void RollRight(float);
    void LookRight(float); // For more normal feeling mouse controls for testing/debugging
    
    // Tap to fire
    void FireProjectile();
    
    class UCameraComponent* OurCamera;
    
    // Background track
    UPROPERTY()
    USoundBase* BackgroundTrack;
    
    UPROPERTY()
    UARSessionConfig* MyARSessionConfig;
};
