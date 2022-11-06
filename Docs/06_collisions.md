# Colisiones y seguimiento

[Volver al anterior](05_animations.md)

En esta última sección, implementaremos los eventos pertinentes para detectar las colisiones con las balas y los enemigos.

## Colisión de proyectiles

Nuestra clase de Blueprint `BP_Projectile` tiene un componente con su colisión indicada que haga `OverlapAllDynamic`. Podríamos comprobar la lógica de overlap tanto en el enemigo, como en el proyectil, pero ya que vamos destruir al enemigo, lo comprobaremos directamente en él. 

De este modo, dentro de la clase `AEnemy` escucharemos por los eventos de overlap, y en el caso que hagamos overlap con un proyectil, lo destruiremos.

Dentro de `Source/CowboyCore/Enemy.h` añadiremos lo siguiente:

```diff
 protected:
        AEnemy();

 public:
+       virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
+
        UPROPERTY(EditDefaultsOnly)
        UFloatingPawnMovement* FloatingPawnMovement;
 };
```

Y dentro de `Source/CowboyCore/Enemy.cpp` añadiremos lo siguiente:

```diff
+#include "Projectile.h"

AEnemy::AEnemy()
 {
        FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
        AIControllerClass = AAIEnemyController::StaticClass();
        AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
 }
+
+void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
+{
+       Super::NotifyActorBeginOverlap(OtherActor);
+
+       if (Cast<AProjectile>(OtherActor))
+       {
+               OtherActor->Destroy();
+               Destroy();
+       }
+}
```

En este caso estamos sobreescribiendo la función `NotifyActorBeginOverlap` y comprobando si el otro actor es un proyectil (si no lo fuera, el `Cast<AProjectile>` nos debería devolver `nullptr`, lo que es _similar_ a `false` dentro del if).

> Si compilamos con <kbd>ctrl</kbd> + <kbd>alt</kbd> + <kbd>F11</kbd> veremos que nuestros enemigos ahora desaparecen al dispararles.

## Perder la partida

Para poner una regla que permita comprobar si el enemigo ha impactado a nuestro jugador, ya que el enemigo tiene un `CapsuleCollision` con `BlockAllDynamic`, escucharemos por los eventos de `Hit` en nuestro vaquero y en el caso que un `AEnemy` colisione con nosotros, reiniciaremos el nivel actual.


Dentro de `Source/CowboyCore/CowboyPlayer.h` añadiremos lo siguiente:

```diff
  public:
 
        UPROPERTY(EditDefaultsOnly, Category = "Cowboy Shooting")
        UShootingComponent* ShootingComponent;
+       
+       virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
+               FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
 
 private:
        void MoveForward(float Value);
```

Y dentro de `Source/CowboyCore/CowboyPlayer.cpp` añadiremos lo siguiente:

```diff
#include "CowboyPlayer.h"
 
+#include "Enemy.h"
+#include "Kismet/GameplayStatics.h"
+
 ACowboyPlayer::ACowboyPlayer()
 {
        bUseControllerRotationYaw = false;
@@ -17,6 +20,18 @@ void ACowboyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputCompon    
        InputComponent->BindAction("Shoot", IE_Pressed, ShootingComponent, &UShootingComponent::Shoot); }
 
+void ACowboyPlayer::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
+                                                         bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
+                                                         const FHitResult& Hit)
+{
+       Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
+
+       if (Cast<AEnemy>(Other))
+       {
+               UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
+       }
+}
+
 void ACowboyPlayer::MoveForward(float Value)
 {
        const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
```

En este caso, comprobaremos que estamos haciendo `Hit` contra un `AEnemy` y en ese caso, usando el nombre del mundo actual (con `GetWorld()->GetName()`), reabrimos el nivel usando `UGameplayStatics::OpenLevel`.

## Final

Con todo esto tenemos nuestro juego _completo_. Hemos visto los diferentes tipos de elementos clave que nos permitirán implementar una amplia gama de juegos, cómo desarrollarlos en C++ extendiéndolos con Blueprint, y cómo buscar o aprender más sobre la API de Unreal Engine, ya que este es Open Source.

Para cerrar nuestro proyecto, haremos un último commit:

```sh
$ git add .
$ git commit -m "Add collisions"
```
