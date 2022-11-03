# Clases principales

[Volver al anterior](02_assets_import.md)

## Log

Lo primero que haremos, para recordar nuestro proceso de compilación, es crear una categoría de log nueva para nuestro juego.

Crearemos un fichero `Source/CowboyCore/Log.h` con este contenido:

```cpp
#pragma once

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCowboyCore, All, All);
```

Y un fichero `Source/CowboyCore/Log.cpp`:

```cpp
#include "Log.h"

DEFINE_LOG_CATEGORY(LogCowboyCore);
```

Esto ha definido una nueva categoría de logging llamada `LogCowboyCore`, que podremos usar para agrupar los mensajes específicos de nuestro juego.

### Actualizar mensajes de log

Ahora que tenemos nuestra categoría de log, modificaremos el fichero `Source/CowboyCore/CowboyCore.cpp`:


```diff
 #include "CowboyCore.h"
 #include "Modules/ModuleManager.h"
+#include "Log.h"

 void FCowboyCore::StartupModule()
 {
-       UE_LOG(LogTemp, Warning, TEXT("CowboyCore module starting up"));
+       UE_LOG(LogCowboyCore, Warning, TEXT("CowboyCore module starting up"));

 }
 
 void FCowboyCore::ShutdownModule()
 {
-       UE_LOG(LogTemp, Warning, TEXT("CowboyCore module shutting down"));
+       UE_LOG(LogCowboyCore, Warning, TEXT("CowboyCore module shutting down"));
```

Finalmente, podemos compilar y reabrir el editor con:

```sh
$ build && editor
```

> Si tenemos el editor abierto, podemos usar la funcionalidad de [Live Coding](https://docs.unrealengine.com/5.0/en-US/using-live-coding-to-recompile-unreal-engine-applications-at-runtime/) con las teclas <kbd>ctrl</kbd> + <kbd>alt</kbd> + <kbd>F11</kbd>.

Dentro del editor, también podemos ver los logs y filtrarlos por categoría. Ahora veremos la categoría que hemos creado:

![Log category](images/03_main_classes/log_category.jpg)

Y si solo seleccionamos nuestra categoría, veremos el mensaje filtrado:

![Log category filtered](images/03_main_classes/log_category_filtered.jpg)

## Rider

Ahora que ya conocemos todo el flujo básico para compilar y ejecutar nuestro juego con Unreal Engine, y entendemos que no es magia cómo funciona por debajom, podemos dar un paso más allá y utilizar un IDE que nos permita ser mucho más productivos y evitar tener que ejecutar todos esos comandos por nuestra cuenta.

Podríamos usar Visual Studio, pero ya que con la cuenta de correo de UniOvi podemos usar los productos de JetBrains, [Rider](https://www.jetbrains.com/rider/) es una mejor opción con diferencia, ya que tiene un soporte específico para Unreal Engine.

Lo único que necesitamos, es generar una solución para nuestro proyecto y abrirla con Rider:

<img src="images/03_main_classes/generate_solution.jpg" width=300 />
<img src="images/03_main_classes/open_with_rider.jpg" width=300 />

La primera vez que abramos el proyecto, nos mencionará si queremos instalar [Rider Link](https://www.jetbrains.com/help/rider/Unreal_Engine__UnrealLink_RiderLink.html), aceptaremos:

<img src="images/03_main_classes/rider_link.jpg" width=300 />


### Conceptos importantes

Una vez abierta la solución con Rider, veremos las siguientes partes:

![Rider](images/03_main_classes/rider.jpg)

1. **Explorador de proyectos**: aquí veremos tanto nuestro juego, como el código de UE si lo hemos seleccionado para descargar en el Epic Games Launcher.

    <img src="images/03_main_classes/engine_options.jpg" width=200 /><img src="images/03_main_classes/source_code.jpg" width=300 />

    Desde aquí, con el botón derecho, también podríamos crear directamente nuestras clases:

    <img src="images/03_main_classes/create_class.jpg" width=300 />

2. **Target para hacer el build**: Como vimos anteriormente, hay diferentes tipos de Targets para los que hacer el build de nuestro proyecto, aquí podemos seleccionar cual queremos de manera sencilla:
    
    <img src="images/03_main_classes/target_rider.jpg" width=200 />

3. **Botones de run y debug**: Estos botones nos permitirán hacer los pasos de `build` y `editor` que antes hacíamos a mano. Además, si le damos al botón de debug, también podremos poner breakpoints en nuestro código de C++ (o en el del editor si estamos con el target Debug o Development y tenemos los símbolos de debug instalados).
4. **Herencia en Blueprints**: Rider es suficientemente listo para indicarnos cuándo hay Blueprints herendando de una clase de C++, o usando un método o una propiedad, y nos lo indicará aquí.

## Cowboy

Primero crearemos la clase base de nuestro vaquero. Para ello crearemos una clase de Unreal Engine que herede de Character:

<img src="images/03_main_classes/cowboy_class.jpg" width=200 />


> Nota: Rider nos adaptará el nombre de la clase (que no el del fichero) a los prefijos correspondientes dependiendo de la clase que heredemos. En este caso: `ACowboyPlayer`.


De momento, el contenido de `CowboyPlayer.h` será el siguiente:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CowboyPlayer.generated.h"

UCLASS()
class COWBOYCORE_API ACowboyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACowboyPlayer();
};
```

Varios puntos a entender de una clase de C++ con Unreal Engine:
1. Cuando tenemos una clase que hereda de `UObject`, se le creará una cabecera autogenerada cuando Unreal Build Tool haga su proceso. Esa cabecera tendrá el nombre del fichero con un `generated` en medio. Aunque la primera vez no exista, es necesario incluirla sí o sí. En nuestro caso es `CowboyPlayer.generated.h`.
2. La directiva `UCLASS()` permite indicar a UnrealHeaderTool que genere todo el código necesario para nuestra clase. Además aquí podríamos indicar un montón de especificadores, como por ejemplo que la clase sea Abstracta y no pueda ser instanciada directamente. Puedes leer más sobre los [especificadores aquí](https://benui.ca/unreal/uclass/).
3. También necesitamos la directiva `COWBOYCORE_API` entre `class` y `ACowboyPlayer` específica de nuestro módulo, para que esta clase sea _exportable_. 
4. La directiva `GENERATED_BODY()` es obligatorio añadirla porque creará constructores y todo el cuerpo que Unreal Engine necesita de una clase. En algunos sitios podrás ver que alguien usa `GENERATED_UCLASS_BODY()` en su lugar, pero es mejor usar siempre `GENERATED_BODY()` como regla general.


Y el código de su unidad de compilación `CowboyPlayer.cpp`:

```cpp
#include "CowboyPlayer.h"

ACowboyPlayer::ACowboyPlayer()
{
}
```

Por el momento esta clase no tendrá lógica, pero la implementaremos después.

### Blueprint

Si ahora le damos al botón de _Run_ dentro de Rider, podremos levantar el editor y pasar a crear el Blueprint que heredará de esta clase de C++ para nuestro Vaquero.

Crearemos un Blueprint que herede de esta clase, llamado BP_CowboyPlayer:

![Create Blueprint Cowboy](images/03_main_classes/create_blueprint_cowboy.gif)

En este Blueprint, añadiremos la malla esqueletal que habíamos importado anteriormente:

![Add skeletal mesh](images/03_main_classes/add_sk_mesh_cowboy.gif)

También crearemos un Spring Arm y una Cámara, para que indicar cómo se va a visualizar nuestro actor:


![Add camera](images/03_main_classes/add_camera.gif)

Finalmente crearemos un Blueprint que herede de `AGameModeBase`, para indicar las clases por defecto que se usarán en nuestro juego, como hemos visto en teoría. En nuestro caso solo será el `Default Pawn` por nuestro Cowboy. También actualizaremos la configuración general para usar este Blueprint por defecto en todos los niveles:

![Create GameMode](images/03_main_classes/create_gamemode.gif)



> Esta clase podríamos crearla en C++, o crear una base de GameMode en C++ y luego heredar en Blueprint. Pero como en este juego no tendremos lógica complicada de reglas de juego, podemos evitarlo. Además, como queremos indicar que el `Default Pawn` es un asset de Blueprint, si lo indicaramos en C++ habría que _"hardcodear"_ el path de ese Blueprint y no es buena práctica. Para esos casos, lo normal es crear una clase de C++ con una propiedad de `TSubclassOf<>`, heredarla en Blueprint e indicar en el Blueprint la referencia. Veremos un ejemplo más abajo.

Podemos comprobar en el fichero `Config/DefaultEngine.ini` como se ha añadido esta configuración:

```diff
 [/Script/EngineSettings.GameMapsSettings]
 EditorStartupMap=/Game/MainLevel.MainLevel
 GameDefaultMap=/Game/MainLevel.MainLevel
+GlobalDefaultGameMode=/Game/BP_MainGameMode.BP_MainGameMode_C
```

## Enemigo

Como hemos visto en teoría, existen los `APawn` y los `AController`. Los primeros se encargan de reprensentar a un objecto _con vida_ de nuestro juego y los segundos se encargan de _controlarlo_, como si fuera su cerebro. En el caso del `AController` existen dos subclases: `AAIController` y `APlayerController`.

Los `APawn` (o `ACharacter` ya que heredan de ellos), cuando son controlados por un `ULocalPlayer` se les crea una `APlayerController` usando la clase indicada en el `AGameModeBase` del nivel (o del proyecto).
Cuando un `APawn` no es controlado por un jugador, se presupone que tiene que ser controlado por una inteligencia artificial, por lo que (dependiendo de la propiedad [`APawn::AutoPossessAI`](https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Classes/GameFramework/Pawn.h#L105-L111)) se le creará un `AAIController` según la clase indicada en la propiedad [`APawn::AIControllerClass`](https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Classes/GameFramework/Pawn.h#L117-L119).

> Nota: Vemos como la propiedad `APawn::AIControllerClass` es una `UPROPERTY` y del tipo `TSubclassOf<AController>`. Lo que en el Blueprint se reflejará como on _Dropdown_ de clases que hereden de `AController`:
>
> <img src="images/03_main_classes/controller_class.jpg" width=500 />


Dicho esto, crearemos un `APawn` para nuestro enemigo base y un `AAIController` para la lógica de ese enemigo.

### AI Controller

Comos vamos a crear usar el módulo de AI, necesitamos incluir en nuestras dependencias, así que en el fichero `Source/CowboyCore/CowboyCore.Build.cs` añadiremos el módulo `AIModule` a la lista de `PublicDependencyModuleNames`:

```diff
     {
         PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

-        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
+        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "AIModule" });
         PrivateDependencyModuleNames.AddRange(new string[] { });
     }
 }
```

Añadiremos una clase que herede de actor (luego le cambiaremos la herencia) que se llame `AIEnemyController`:

<img src="images/03_main_classes/enemy_controller.jpg" width=300 />

El cuerpo de `Source/CowboyCore/AIEnemyController.h` será:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CowboyPlayer.h"
#include "AIEnemyController.generated.h"

UCLASS()
class COWBOYCORE_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	ACowboyPlayer* TargetPlayer;

	void FollowPlayer();
	void OnMovementProcessed(UPathFollowingComponent* Component, FVector& Velocity);
	void OnFollowCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
```

Diseccionando el código anterior:

1. Extendemos el método `BeginPlay` para inicializar una variable y unos Delegates. Este método será llamado cuando empiece el juego o se haga Spawn de este actor. Es importante inicializar estos valores aquí y no el constructor, ya que como vimos en teoría, el constructor es llamado cuando se crea el [CDO](https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Objects/) de esta clase, no cuando comienzamos a jugar.
2. Extendemos el método `OnPosses`, que es llamado cuando un `AController` empieza a _poseer_ a un `APawn`. Aquí le diremos, que cuando empiece a ser _poseído_, que empiece a seguir al jugador.
3. Declaramos un miembro interno llamado `TargetPlayer`. Aunque sea un miembro privado y no lo vayamos a exponer a un Blueprint, debemos añadirle el macro `UPROPERTY`, ya que al ser un puntero el _recolector de basura_ de UE podría eliminarlo de memoria sin entender que está siendo referenciado.
4. Declaramos una funcion `FollowPlayer`, donde indicaremos la lógica para cómo seguir al jugador.
5. Declaramos una función `OnMovementProcessed` que va a ser enlazada a un `Delegate` del componente [`UPathFollowingComponent` que tiene la clase `AIController`](https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/AIModule/Classes/AIController.h#L128). Esta función se va a llamar cada vez que se procese un nuevo movimiento.
6. Declaramos otra función `OnFollowCompleted` que enlazaremos a otro Delegate y nos indicará cuándo se ha terminado de ejecutar el seguimiento.

> [Los Delegates](https://docs.unrealengine.com/5.0/en-US/delegates-and-lamba-functions-in-unreal-engine/) son como _callbacks_ (similar a los Event Dispatchers en Blueprint), en los que se declara qué parámetros va a recibir una función y se les pueden enlazar funciones (una o varias, si son MulticastDelegates). Esto nos permite desacoplar código y ayudar a la modularidad de otras partes de nuestro juego. En el caso anterior, enlazaremos [estos delegates](https://github.com/EpicGames/UnrealEngine/blob/46544fa5e0aa9e6740c19b44b0628b72e7bbd5ce/Engine/Source/Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h#L216-L229).

Y el cuerpo de `Source/CowboyCore/AIEnemyController.cpp` será:

```cpp
#include "AIEnemyController.h"
#include "Kismet/GameplayStatics.h"

void AAIEnemyController::BeginPlay()
{
	Super::BeginPlay();

	TargetPlayer = Cast<ACowboyPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACowboyPlayer::StaticClass()));

	GetPathFollowingComponent()->PostProcessMove.BindUObject(this, &ThisClass::OnMovementProcessed);
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::OnFollowCompleted);
	FollowPlayer();
}

void AAIEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	FollowPlayer();
}

void AAIEnemyController::FollowPlayer()
{
	if (TargetPlayer && GetPawn())
	{
		MoveToActor(TargetPlayer, -1.f, false);
	}
}

void AAIEnemyController::OnMovementProcessed(UPathFollowingComponent* Component, FVector& Velocity)
{
	FVector Direction = Velocity;
	Direction.Z = 0.f;
	GetPawn()->SetActorRotation(Direction.Rotation());
}

void AAIEnemyController::OnFollowCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	FollowPlayer();
}
```

Diseccionado el código anterior:
1. En `BeginPlay`:
    1. Usamos la clase `UGameplayStatics` para buscar la instancia en el nivel que hereda de la clase `ACowboyPlayer` y lo guardamos en la propiedad `TargetPlayer`.
    2. Enlazamos al delegate `PostProcessMove` nuestra función `OnMovementProcessed`.
    3. Enlazamos al delegate `OnRequestFinished` nuestra función `OnFollowCompleted`.
    > Aquí estamos usando [`ThisClass`](https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h#L1639-L1646). Es un alias a la clase actual que UE nos provee (al igual que `Super`), podríamos usar `&AAIEnemyController::OnFollowCompleted`, pero es más verboso.
    4. Llamamos a `FollowPlayer` para iniciar el seguimiento.
2. En `OnPosses` llamamos a `FollowPlayer` para inciar el seguimiento. Cuando el actor **no** está situado en el nivel desde el inicio (es decir, cuando hacemos un Spawn), `BeginPlay` se llamará antes que `OnPosses`, por lo que no tenemos un `Pawn` poseído y el `MoveToActor` no funcionará, por eso tenemos que llamarlo aquí también.
3. En `FollowPlayer` comprobamos que tenemos una referencia **válida** de nuestro _target_ y que estamos poseyendo a un peón, e invocamos el metodo `AAIController::MoveToActor`, diciéndole que el `AcceptanceRadius` sea el mínimo por defecto y que no se pare cuando haga _overlap_.
4. En `OnMovementProcessed` usamos el componente de `Velocity` en el plano horizontal y decimos que actualice la orientación de nuestro actor hacia donde apunta su velocidad. Es decir, que mire hacia donde estamos yendo.
5. En `OnFollowCompleted` volvemos a llamar otra vez a `FollowPlayer`, para que siga persiguiendo a nuestro jugador indefinidamente, aunque choquemos con él una vez.

> El Delegate `OnRequestFinished` se invocará cuando no podamos hacer un movimiento porque estemos bloquedos, fuera de la navegación, o porque ya hayamos llegado a destino.

### Enemy

Ahora crearemos una clase que herede de `APawn` y la llamaremos `Enemy`.

Como la lógica de nuestro enemigo es muy simple, esta clase solo tendrá lo siguiente.

En `Source/CowboyCore/Enemy.h` solo existirá un constructor y un componente `UFloatingPawnMovement` para moverse:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class COWBOYCORE_API AEnemy : public APawn
{
	GENERATED_BODY()

protected:
	AEnemy();

public:
	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement;
};
```

En la unidad de compilación `Source/CowboyCore/Enemy.cpp`:

```cpp
#include "Enemy.h"
#include "AIEnemyController.h"

AEnemy::AEnemy()
{
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	AIControllerClass = AAIEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
```

Aquí solo creamos el componente llamando a la función `CreateDefaultSubobject`, le decimos que clase queremos para nuestro `AIController` y le indicamos que queremos que siempre se cree un `AIController` cuando se coloque en el nivel o cuando se haga un Spawn dinámicamente.

> Podemos recompilar el proyecto en cualquier momento con <kbd>ctrl</kbd> + <kbd>alt</kbd> + <kbd>F11</kbd>. Si por algún casual tuvieramos un error de archivos temporales (a veces los Blueprint no se recompilan correctamente), podríamos probar a parar el editor y volver a lanzarlo.

#### Cactus

Finalmente, vamos a crear una clase de Blueprint llamada `BP_Cactus` que herede de `Enemy`:

![Create BP Cactus](images/03_main_classes/create_bp_cactus.gif)

Dentro de este Blueprint:
1. Crearemos una cápsula para gestionar las colisiones y usarla como base.
2. Añadiremos una malla estática sin colisiones con nuestro cactus.
3. Y le diremos que la velocidad máxima de nuestro `FloatingPawnMovement` sea de `300`.


![BP Cactus](images/03_main_classes/bp_cactus.gif)


> Cuando la IA hace la navegación, tomará el lado más grande de nuestra colisión como referencia, por lo que necesitamos que sobresalga de la capsula, si no el lado más estrecho del Cactus nunca llegaría a alcanzar a nuestro jugador.

### Navigation path

Dentro del editor, aprovecharemos para colocar un Nav Mesh Volume, que indicará a nuestro enemigo por dónde se puede mover y un Player Start, que indicará dónde se tiene que hacer Spawn de nuestro vaquero:

![Add nav mesh](images/03_main_classes/add_nav_mesh.gif)

## Generador de enemigos

Ahora crearemos un Actor que nos genere enemigos automáticamente dentro de un área que le indiquemos visualmente, también le daremos varias propiedas para que sea configurable manualmente mediante Blueprint.

> Esta clase usará el concepto de [Timers](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Timers/), funcionan similar a los [timers de blueprint](https://docs.unrealengine.com/4.26/en-US/InteractiveExperiences/UseTimers/).

Crearemos una clase `EnemySpawner` que herede de `AActor`. El cuerpo de su cabecera (`Source/CowboyCore/EnemySpawner.h`) será:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class COWBOYCORE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/* Area within where enemies will be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	UBoxComponent* SpawningArea;
	
	/* Class of enemies to be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	TSubclassOf<AEnemy> EnemyClass = AEnemy::StaticClass();

	/* Time in seconds between enemy spawns */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	float SpawnRate = 1.f;

	/* Amount of enemies to be spawned. If -1, infinite enemies will be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	int32 NumberOfEnemiesToSpawn = -1;


private:
	int32 TotalEnemiesSpawned = 0;

	void SpawnEnemy();
	
	FTimerHandle SpawnEnemyHandle; 
};
```

En esta cabecera vemos los siguientes elementos:
1. El constructor y el método `BeginPlay` sobreescrito.
2. Una serie de propiedades públicas, etiquetadas con el macro `UPROPERTY`. Estas propiedades tienen el especificador [`EditAnywhere`](https://benui.ca/unreal/uproperty/#editanywhere) que nos permitirá editar el valor de esta propiedad tanto en los _defaults_ del Blueprint, como en una instancia colocada en el nivel. También tienen el especificador de categoría, que nos agrupará en el editor las propiedades bajo el mismo título `"Enemy Spawner"`. Estas propiedades son:
    1. `SpawningArea`: Un `UBoxComponent` que nos servirá como referencia para indicar el área donde pueden aparecer enemigos.
    2. `EnemyClass`: La clase que utilizaremos para instanciar nuevos enemigos. Al usar `TSubclassOf<AEnemy>`, esta propiedad solo aceptará clases que hereden de `AEnemy`. La ventaja de guardar esto como propiedad es que podremos crear varios Spawners de diferentes enemigos solo cambiando el valor de esta propiedad en el editor. Por defecto le damos el valor de la clase `AEnemy`.
    3. `SpawnRate`: Cada cuanto queremos que se generen nuevos enemigos.
    4. `NumberOfEnemiesToSpawn`: Cuántos enemigos vamos a hacer Spawn. Si es `-1` serán infinitos.
3. Luego tenemos una propiedad `TotalEnemiesSpawned` para mantener la cuenta de los enemigos que vamos creando.
4. La función `SpawnEnemy` en la que implementaremos la lógica que necesitemos para crear enemigos.
5. Finalmente tenemos la propiedad `SpawnEnemyHandle`, que nos servirá para guardar una referencia al último timer que hemos creado para invocar en el futuro a `SpawnEnemy`.

> Nota: cuando añadimos comentarios tipo JavaDoc en una `UPROPERTY`, ese comentario será interpretado por UE y se mostrará en el editor al hacer Hover:
>
> <img src="images/03_main_classes/comment.jpg" width=300 />


Y tendremos el siguiente código en `Source/CowboyCore/EnemySpawner.cpp`:

```cpp
#include "EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	SpawningArea = CreateDefaultSubobject<UBoxComponent>("SpawningArea");
	RootComponent = SpawningArea;
	SpawningArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	if (NumberOfEnemiesToSpawn != -1 && TotalEnemiesSpawned >= NumberOfEnemiesToSpawn)
	{
		return;
	}
	
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),
	                                                                   SpawningArea->GetScaledBoxExtent());
	RandomPoint.Z = GetActorLocation().Z;

	const FRotator RandomRotation = FRotator(0.f, FMath::FRand() * 360.f, 0.f);

	GetWorld()->SpawnActor<AEnemy>(EnemyClass, RandomPoint, RandomRotation);
	TotalEnemiesSpawned++;

	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyHandle, this, &ThisClass::SpawnEnemy, SpawnRate);
}
```

En este fichero hacemos lo siguiente:
1. En el constructor instanciamos un nuevo componente `UBoxCollision`, que indicamos que sea el componente raíz y finalmente le decimos que no nos interesa su colisión (solo lo usaremos como referencia visual).
2. En la función `BeginPlay` únicamente llamamos a `SpawnEnemy` por primera vez para que se empiece a llamar de continuo a sí misma.
3. Dentro de nuestra función `SpawnEnemy`:
    1. Comprobamos que no hemos llegado al límite de enemigos generados.
    2. Obtenemos un punto aleatorio dentro del área definida.
    3. Asignamos ese punto a la base de nuestro Actor (para que si hemso creado la caja muy alta, no nos salgan volando los enemigos).
    4. Para que no salgan todos los enemigos mirando al mismo lado, generamos una rotación aleatoria (únicamente en el eje Z).
    5. Hacemos Spawn de un nuevo enemigo en base a la clase definida en la propiedad `EnemyClass`. Esta función nos devuelve un puntero al objeto creado, por si lo necesitaramos.
    6. Aumentamos la cuenta de los enemigos creados.
    7. Encolamos una llamada de nuevo a `SpawnEnemy` con un timer, que será invocada en base al tiempo indicado en `SpawnRate` en segundos.

### Blueprint

Con la clase anterior como base, crearemos un nuevo Blueprint:

![Create BP Spawner](images/03_main_classes/create_bp_spawner.gif)

Indicaremos los valores por defecto que nos interesen:

![BP Spawner properties](images/03_main_classes/bp_spawner_properties.gif)

Y lo colocaremos en el nivel, ajustando su tamaño:

![Place BP Spawner](images/03_main_classes/place_bp_spawner.gif)

Si le damos al play veremos como nos persiguen los nuevos enemigos:

![Play follow](images/03_main_classes/follow_play.gif)

## Proyectiles

Ahora crearemos una clase que nos servirá para indicar la base de nuestros disparos.
Creamos una clase `Projectile` que herede de actor, y su cabecera será únicamente:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class COWBOYCORE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;
};
```

Solo le añadiremos un componente de movimiento de proyectil, que nos servirá para lanzarlo a una velocidad en específico.

Y el cuerpo de esta clase:

```cpp
#include "Projectile.h"

AProjectile::AProjectile()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}
```

### Blueprint

Extenderemos de esta clase y crearemos un fichero `BP_Projectile`:

Le añadiremos una caja básica como representación visual y ajustaremos su colisión para que hage overlap con todos los elementos:

Ajustaremos la velocidad inicial del proyectil y le quitamos la gravedad:

Y finalmente le diremos que tenga un _Life Span_ de 2 segundos, para que el actor se destruya pasado este tiempo:

## Shooting Component

Podríamos crear la lógica de disparo directamente dentro de la clase `CowboyPlayer`, pero eso implicaría que si quisieramos hacer enemigos que disparasen, tendríamos que duplicar la lógica.

De este modo, extraeremos esta lógica en un componente de disparo, el cual pueda ser "equipado" por cualquier tipo de actor.

Crearemos una clase `ShootingComponent` que herede de `ActorComponent`:

<img src="images/03_main_classes/shooting_component.jpg" width=300>

La cabecera de este componente será:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"

#include "ShootingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COWBOYCORE_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void Shoot();

	UPROPERTY(BlueprintAssignable)
	FOnShoot OnShoot;

	UPROPERTY(EditDefaultsOnly, Category = "Cowboy Shooting")
	float ShootingCooldownTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cowboy Shooting")
	TSubclassOf<AProjectile> ProjectileClass;

private:
	float LastShootingTime = 0.f;
	UPROPERTY()
	TArray<UArrowComponent*> ShootingArrows;
};
```

En esta cabecera vemos cosas nuevas que explicaremos a continuación:

1. La directiva `DECLARE_DYNAMIC_MULTICAST_DELEGATE` crea un nuevo **tipo** de Delegate personalizado para que nosostros podamos usar. Este delegate no tiene parámetros y le ponemos el nombre `FOnShoot` (por convención se suele poner el prefijo `F` y el nombre que queramos, como es un evento, suele ser común poner `On` delante de la acción).
2. A la directiva de `UCLASS` le pasamos los especificadores [`ClassGroup`](https://benui.ca/unreal/uclass/#classgroup) y [`BlueprintSpawnableComponent`](https://benui.ca/unreal/uclass/#blueprintspawnablecomponent). El último le dirá que puede aparecer en el Dropdown de componentes a añadir a un actor y el primero le dirá que aparecerá dentro de la categoría `Custom`:

    <img src="images/03_main_classes/shooting_component_dropdown.jpg" width=300>
3. Sobre escribimos `BeginPlay` y creamos una función pública `Shoot` que nos servirá para que el actor dueño del componente invoque nuestro disparo.
4. La propiedad `OnShoot` del tipo `FOnShoot` (el tipo de delegate creado antes) en realidad no es una propiedad al uso, si no un Evento asignable de Blueprint (debido al `BlueprintAssignable`) que veremos más adelante. Este evento se invocará cuando disparemos y nos servirá para controlar los efectos especiales (en este caso un sonido) después del disparo de manera visual por Blueprint.
5. Como no queremos disparar de manera indiscriminada, añadiremos un tiempo de _cooldown_ que podrá ser ajustado por la propiedad `ShootingCooldownTime`. Esta vez las propiedades usarán [`EditDefaultsOnly`](https://benui.ca/unreal/uproperty/#editdefaultsonly), porque solo queremos que se actualicen en el _Archetype_, es decir en la clase de Blueprint y no en las instancias del nivel, pero podríamos cambiar esto a `EditAnywhere` si fuera necesario.
6. `ProjectileClass` será la clase usada para hacer spawn del proyectil al disparar, esto nos permitirá modificar la clase del proyectil en tiempo de ejecución (por ejemplo si recogemos _power ups_) sin necesidad de duplicar lógica. Para que podamos modificar y leer el valor de esta variable en Blueprints, añadimos [`BlueprintReadWrite`](https://benui.ca/unreal/uproperty/#blueprintreadwrite).
7. Finalmente, tenemos dos propiedades privadas: `LastShootingTime` para saber cuándo fue el último disparo y `ShootingArrows` para mantener una lista de los puntos donde queremos lanzar disparos, que veremos a continuación.

El cuerpo de este componente sería de la siguiente manera:

```cpp
#include "ShootingComponent.h"

void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastShootingTime = GetWorld()->GetTimeSeconds() - ShootingCooldownTime;

	if (GetOwner())
	{
		const auto Arrows = GetOwner()->GetComponentsByTag(UArrowComponent::StaticClass(), FName("ShootingArrow"));
		for (const auto& Arrow : Arrows)
		{
			ShootingArrows.Add(Cast<UArrowComponent>(Arrow));
		}
	}
}

void UShootingComponent::Shoot()
{
	if (!ProjectileClass) return;

	if (LastShootingTime > GetWorld()->GetTimeSeconds() + ShootingCooldownTime) return;

	LastShootingTime = GetWorld()->GetTimeSeconds();

	for (const auto& Arrow : ShootingArrows)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		                                    Arrow->GetComponentLocation(),
		                                    Arrow->GetComponentRotation());
	}

	OnShoot.Broadcast();
}
```

Dentro del método `BeginPlay`:
1. Ajustamos el `LastShootingTime` al tiempo actual menos el cooldown indicado. De esta manera podremos disparar inmediatamente la primera vez.
2. Si todo es válido y estamos asignados a un actor, buscaremos todos los componentes del tipo `UArrowComponent` que estén etiquetados con el tag `"ShootingArrow"` (este tag es un `FName`, por eso hay que envolverlo en su constructor).
3. Finalmente, para cada uno de esos componentes encontrados, los añadiremos al array de flechas que teníamos como propiedad.

En el método `Shoot`:
1. Comprobaremos que tenemos una clase válida para _spawnear_.
2. Comprobamos que hemos pasado el tiempo de _cooldown_ para poder disparar.
3. Actualizamos el tiempo del último disparo
4. Por cada flecha que tiene nuestro actor, crearemos un proyectil nuevo usando la transformación de la flecha.
5. Finalmente llamamos a evento `OnShoot` para que quien esté suscrito reciba la notificación. 

### Actualizar Cowboy

Añadiremos el componente anterior creado a nuestro `CowboyPlayer`. Así que en `CowboyPlayer.h` haremos el siguiente cambio:

```diff
 #pragma once

 #include "CoreMinimal.h"
+#include "ShootingComponent.h"
 #include "GameFramework/Character.h"
 #include "CowboyPlayer.generated.h"

@@ -13,5 +14,7 @@ class COWBOYCORE_API ACowboyPlayer : public ACharacter

 public:
        ACowboyPlayer();

+       UPROPERTY(EditDefaultsOnly, Category = "Cowboy Shooting")
+       UShootingComponent* ShootingComponent;
 };
```

Y en `CowboyPlayer.cpp` el siguiente cambio:

```diff
 #include "CowboyPlayer.h"

 ACowboyPlayer::ACowboyPlayer()
 {
+       ShootingComponent = CreateDefaultSubobject<UShootingComponent>("ShootingComponent");
 }
```

Dentro del blueprint de `BP_Cowboy` crearemos unos componentes arrow, ajustaremos su posición y le añadiremos la etiqueta `ShootingArrow`:

![Add arrows](images/03_main_classes/add_arrows.gif)

Ajustaremos el shooting cooldown y la clase de proyectil:

![Set cooldown and projectile class](images/03_main_classes/set_cooldown.gif)

Y añadiremos un sonido de disparo cada vez que se llame al evento `OnShoot` (el delegate que hemos definido anteriormente):

![Add on shoot event](images/03_main_classes/on_shoot.gif)

## Siguiente

En el siguiente paso gestionaremos el input de nuestro juego, pero antes guardaremos y haremos commit de nuestro cambios en Git:

```sh
$ git add .
$ git commit -m "Add main classes"
```

[Ir al siguente](04_input_routing.md)