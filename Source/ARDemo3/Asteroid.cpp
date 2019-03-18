#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
    // Setup meshes and textures
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid Mesh"));
    RootComponent = Mesh;
    AssignMaterials(Mesh);
    
    // Loads particle effects for later use
    static ConstructorHelpers::FObjectFinder<UParticleSystem> HitSystem(TEXT("ParticleSystem'/Game/AsteroidsFromPhotogrammetry/Effects/P_Asteroid_Hit.P_Asteroid_Hit'"));
    if(HitSystem.Succeeded()){
        HitEffect = HitSystem.Object;
    }
    
    // Loads sound effects
    HitSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, TEXT("SoundCue'/Game/AsteroidsFromPhotogrammetry/Sounds/Cues/A_Hit_Cue.A_Hit_Cue'")));
    ExplosionSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, TEXT("SoundCue'/Game/AsteroidsFromPhotogrammetry/Sounds/Wavs/A_Explosion_2_Cue.A_Explosion_2_Cue'")));
    
    // Number of hits to take before death
    health = 3;
}


// Assigns random mesh to spawned asteroid
void AAsteroid::AssignMaterials(UStaticMeshComponent* MyMesh)
{
    int index = FMath::RandRange(1, 9);
    
    FString meshPath = FString::Printf(TEXT("StaticMesh'/Game/AsteroidsFromPhotogrammetry/Meshes/S_Asteroid_%d.S_Asteroid_%d'"), index, index);
    
    UStaticMesh* MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *meshPath));
    
    if(MeshAsset != nullptr){
        MyMesh->SetStaticMesh(MeshAsset);
        MyMesh->SetSimulatePhysics(true);
        MyMesh->SetEnableGravity(false);
        MyMesh->SetNotifyRigidBodyCollision(true);
        MyMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
        MyMesh->SetLinearDamping(0.f);
    }
}


// Updates internal state after a collision
void AAsteroid::TakeProjectileDamage(FVector hitLocation, FVector normal)
{
    this->health -= 1;
    
    // Play hit effects
    if(HitSound != nullptr){
        UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, hitLocation);
    }
    
    if(this->health <= 0){
        // Play explosion sound
        if(ExplosionSound != nullptr){
            UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
        }
        
        // Destroy self to free memory
        Destroy();
        
    } else{
        Mesh->SetLinearDamping(1.8f);
        Mesh->AddImpulse(normal * 3000.f, FName(TEXT("None")), true);
        Mesh->AddAngularImpulseInRadians((normal - GetActorForwardVector()), FName(TEXT("None")), true);
    }
}


// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
    Super::BeginPlay();
    
    // Initial direction for asteroid to travel
    float xTrajectory = FMath::RandRange(.1f, 5.f);
    float yTrajectory = FMath::RandRange(.1f, 5.f);
    float zTrajectory = FMath::RandRange(.1f, 5.f);
    FVector trajectory = FVector(xTrajectory, yTrajectory, zTrajectory);
    
    // Initial spin for asteroid
    float pitch = FMath::RandRange(.1f, 1.f);
    float yaw = FMath::RandRange(.1f, 1.f);
    float roll = FMath::RandRange(.1f, 1.f);
    FVector spin = FVector(pitch, yaw, roll);
    
    Mesh->AddImpulse(trajectory, FName(TEXT("None")), true);
    Mesh->AddAngularImpulseInRadians(spin, FName(TEXT("None")), true);
}
