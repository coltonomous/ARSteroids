#include "Projectile.h"
#include "Asteroid.h"


// Sets default values
AProjectile::AProjectile()
{
    // Setup mesh for actor
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = SphereMesh;
    AssignMaterials(SphereMesh);
    
    // Setup collision detection for actor
    collider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    collider->SetSphereRadius(50.f);
    collider->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
    collider->SetupAttachment(SphereMesh);
    collider->SetCollisionProfileName(TEXT("BlockAll"));
    collider->SetNotifyRigidBodyCollision(true);
    
    // Use a ProjectileMovementComponent to govern this projectile's movement
    projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    projectileMovement->UpdatedComponent = RootComponent;
    projectileMovement->InitialSpeed = 10000.f;
    projectileMovement->MaxSpeed = 10000.f;
    projectileMovement->bRotationFollowsVelocity = true;
    projectileMovement->ProjectileGravityScale = 0;
    
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionSystem(TEXT("ParticleSystem'/Game/AsteroidsFromPhotogrammetry/Effects/P_Asteroid-Exploded.P_Asteroid-Exploded'"));
    if(ExplosionSystem.Succeeded()){
        ExplosionEffect = ExplosionSystem.Object;
    }
    
    // Assign sound effects
    FireSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, TEXT("SoundCue'/Game/AsteroidsFromPhotogrammetry/Sounds/Cues/A_Laser_Cue.A_Laser_Cue'")));
    
    // Die after 8 seconds by default
    InitialLifeSpan = 8.0f;
}


// Assigns material to projectile mesh
void AProjectile::AssignMaterials(UStaticMeshComponent* MyMesh)
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    
    if(ProjectileMesh.Succeeded())
    {
        MyMesh->SetStaticMesh(ProjectileMesh.Object);
        MyMesh->SetCollisionProfileName(TEXT("OverlapAll"));
        
        UMaterial* ProjectileMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("Material'/Game/AsteroidsFromPhotogrammetry/Materials/M_Projectile.M_Projectile'")));
        
        if(ProjectileMaterial != nullptr){
            UMaterialInstanceDynamic* DynamicProjectileMaterial = UMaterialInstanceDynamic::Create(ProjectileMaterial, MyMesh);
            MyMesh->SetMaterial(0, DynamicProjectileMaterial);
        }
    }
}


// Collision detection with other components
void AProjectile::OnProjectileHit(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& hit)
{
    FVector hitLocation = GetActorLocation();
    FVector direction = projectileMovement->Velocity;
    
    // If projectile hits something besides itself
    if(otherActor != nullptr && otherActor != this && otherComp != nullptr){
        
        // Play hit effects
        UParticleSystemComponent* hitReference = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, hitLocation);
        hitReference->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
        
        Destroy();
        
        // If that thing is an asteroid
        if (AAsteroid* Asteroid = Cast<AAsteroid>(otherActor))
        {
            Asteroid->TakeProjectileDamage(hitLocation, NormalImpulse);
        }
    }
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    // Play laser sound on start
    if(FireSound != nullptr){
        UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
    }
}
