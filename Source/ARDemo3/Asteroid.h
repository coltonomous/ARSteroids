#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Asteroid.generated.h"

// This class defines the behavior of asteroids. Asteroids are game objects generated at
// the start of the game and are destroyed when they take sufficient damage from the player.
UCLASS()
class ARDEMO3_API AAsteroid : public AActor
{
    // Required UE4 macro for unreal header code
    GENERATED_BODY()
    
public:
    
    // Sets default values for this actor's properties
    AAsteroid();
    
    float health; // So we can access from projectile for collisions
    
    // Updates asteroid's health, velocity, and rotation; called after collision
    void TakeProjectileDamage(FVector, FVector);
    
protected:
    
    // Master function for setting initial state; called when spawned
    virtual void BeginPlay() override;
    
    // Assigns random mesh to spawned actor; called on construction
    void AssignMaterials(UStaticMeshComponent*);
    
    UPROPERTY()
    UStaticMeshComponent* Mesh;
    
    UPROPERTY()
    UParticleSystem* HitEffect;
    
    UPROPERTY()
    USoundBase* HitSound;
    
    UPROPERTY()
    USoundBase* ExplosionSound;
};
