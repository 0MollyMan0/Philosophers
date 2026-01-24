*This project has been created as part of the 42 curriculum by anfouger.*

EN 🇬🇧

# Philosophers

In this project, I will learn the basics of threading a process. I will learn how to create threads and explore the use of mutexes.

## Description

The **Philosophers** project is a concurrency problem based on the classic *Dining Philosophers Problem*.  
Its goal is to introduce and deepen the understanding of **multithreading**, **synchronization**, and **shared resource management** using **POSIX threads (pthreads)** in C.

In this project, several philosophers sit around a table. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must hold two forks (shared resources), which introduces potential issues such as **race conditions** and **deadlocks**.

The challenge is to ensure that:
- No philosopher starves.
- No deadlock occurs.
- Shared resources are accessed safely.
- The simulation stops correctly when a philosopher dies or when all philosophers have eaten a required number of meals.

## Instructions

### Compilation

Compile the program using `make`:

```bash
make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

#### Arguments

- `number_of_philosophers`: Number of philosophers and forks.

- `time_to_die`: Time (ms) a philosopher can survive without eating.

- `time_to_eat`: Time (ms) spent eating.

- `time_to_sleep`: Time (ms) spent sleeping.

- `number_of_meals` (optional): Number of meals each philosopher must eat before the simulation ends.

If omitted, the simulation runs until a philosopher dies.

#### Example

```bash
./philo 5 800 200 200 7
```

## Technical Choices

### Global Data Structure (`t_data`)

```c
typedef struct s_data
{
	long            nb_philo;
	long            time_sleep;
	long            time_die;
	long            time_eat;
	long            must_eat;
	long            is_running;
	pthread_mutex_t *fork_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t run_mutex;
} t_data;
```

`t_data` centralizes all shared configuration and state:

- Timing parameters and philosopher count.

- `is_running` acts as a global simulation flag.

- `fork_mutex` is an array of mutexes, one per fork.

- `print_mutex` ensures ordered and readable output.

- `run_mutex` protects access to `is_running`.

This structure is shared by all philosophers and the monitor.

### Philosopher Structure (`t_philo`)

```c
typedef struct s_philo
{
	long            id;
	long            last_meal;
	long            nb_meal;
	t_data          *data;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t nb_meal_mutex;
} t_philo;
```
Each philosopher owns:

- Its unique `id`.

- Meal-related state (`last_meal`, `nb_meal`).

- Pointers to its left and right forks.

- A pointer to the shared `t_data`.

Two mutexes protect philosopher-specific data:

- `meal_mutex` guards `last_meal`.

- `nb_meal_mutex` guards `nb_meal`.

This separation avoids unnecessary contention and ensures safe concurrent reads by the monitor.

---

### Monitor Structure (`t_monitor`)

```c
typedef struct s_monitor
{
	t_data  *data;
	t_philo *philo;
} t_monitor;
```

The monitor is a dedicated thread responsible for:

- Detecting philosopher death (time since last meal).

- Stopping the simulation when all philosophers have eaten enough.

- Updating `is_running` in a thread-safe way.

The monitor is the **single authority** that decides when the simulation ends.

---

### Synchronization Strategy

- Forks are protected by mutexes to avoid simultaneous access.

- Output is serialized using `print_mutex`.

- The simulation state (`is_running`) is protected by `run_mutex`.

- Philosophers check `is_running` frequently to stop immediately when required.

- Even and odd philosophers pick up forks in opposite order to prevent deadlocks.

## Concepts
---
### What is a CPU?
---
The CPU (Central Processing Unit) is a **hardware component** that allows **machine instructions to be executed**.

An example of a machine instruction is:

- adding two numbers together

- loading a value from memory

- writing a value to memory

- jumping to another instruction

---
### What is a core?
---
A core is a part of the CPU capable of:

- reading an instruction

- executing it

- moving on to the next one

👉 A core executes **ONE** sequence of instructions at a time.

A core can execute a thread.

### How many threads can a core execute?

#### Physically

At any given moment:

- a core executes a single thread

- a single instruction counter

- a single set of active registers

#### Logically

The core **alternates** between multiple threads.

Therefore:

- 1 core → N possible threads

- but only 1 active at a time

#### Special case: Hyper-Threading

Some cores can execute:

- 2 hardware threads (SMT)

But that's not relevant here.

---
### What is a thread?
---
A thread is an execution context consisting of:

- an instruction counter

- registers

- a stack

👉 This is what a core executes.

### What is an instruction pointer?

An instruction pointer is:

- a special CPU register

- that contains the **address of the next instruction to be executed**

Example:
```ini
RIP = 0x40102A
```

The CPU does the following:

1. reads the instruction at this address

2. executes it

3. increments RIP

➡️ Without an instruction pointer, **the CPU does not know what to execute**

### What is a CPU register?

Registers are:

- very small memories

- located in the CPU

- extremely **fast**

They contain:

- **temporary** values

- parameters

- **intermediate results**

Example:
```c
int a = b + c;
```

In reality:

- `b` → register

- `c` → register

- addition

- result → register

- then written to memory

👉 **Each thread has its own registers**

### What is the stack?

The stack is a **memory area** used to store:

- **local** variables

- function parameters

- return addresses

Example:
```c
void f(void)
{
    int x = 42;
}
```

`x` is on the stack

when `f` ends → `x` disappears

👉 Each thread has **its own stack**

👉 Two threads **never have the same stack**

---
### What is a mutex?
---

A mutex is a **synchronization** object provided by the system that ensures that only one thread at a time executes a given section of code.

A `pthread_mutex_t` is:

- a data structure

- shared between threads

- managed partly in user space, partly by the kernel

It contains (conceptually):

- a state: **free/locked**

- the identity of the owning thread

- possibly a **queue** of blocked threads

### In practice

When a thread calls:

```c
pthread_mutex_lock(&m);
```

One of the following two cases occurs:

#### Case 1 - Mutex free

- the thread **acquires the mutex**

- **continues** immediately

#### Case 2 - Mutex already taken

- the thread is **blocked by the kernel**

- it no longer executes **any instructions**

- it **waits** for the mutex to be **released**

When a thread releases a mutex:

```c
pthread_mutex_unlock(&m);
```

- the mutex is **released**

- a blocked thread is **woken up** (if present)

---
### What is atomicity?
---

“Atomicity is a property used in concurrent programming to designate an operation or set of operations in a program that execute entirely without being interrupted before they are completed. An operation that verifies this property is called ”atomic,“ (...)”

Source: [Atomicity (computing) - Wikipedia FR](https://fr.wikipedia.org/wiki/Atomicit%C3%A9_(informatique))

An atomic operation can also be atomic if synchronization mechanisms protected by mutual exclusion are implemented.

## Resources

- [Dining Philosophers Problem - Wikipedia EN](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

- [Deadlock - Wikipedia EN](https://en.wikipedia.org/wiki/Deadlock)

- [Race Condition - Wikipedia EN](https://en.wikipedia.org/wiki/Race_condition)

- [Mutex - Wikipedia EN](https://en.wikipedia.org/wiki/Mutual_exclusion)

FR 🇫🇷

# Philosophers

Dans le cadre de ce projet, j'apprendrai les bases du threading d'un processus. J'apprendrai à créer des threads et j'explorerai l'utilisation des mutex.

## Description

Le projet **Philosophers** est un problème de concurrence basé sur le classique *problème des philosophes qui dînent*.  
Son objectif est d'introduire et d'approfondir la compréhension du **multithreading**, de la **synchronisation** et de la **gestion des ressources partagées** à l'aide des **threads POSIX (pthreads)** en C.

Dans ce projet, plusieurs philosophes sont assis autour d'une table. Chaque philosophe alterne entre réfléchir, manger et dormir. Pour manger, un philosophe doit tenir deux fourchettes (ressources partagées), ce qui introduit des problèmes potentiels tels que les **conditions de concurrence** et les **blocages**.

Le défi consiste à garantir que :
- Aucun philosophe ne meurt de faim.
- Aucun blocage ne se produit.
- Les ressources partagées sont accessibles en toute sécurité.
- La simulation s'arrête correctement lorsqu'un philosophe meurt ou lorsque tous les philosophes ont mangé le nombre de repas requis.

## Instructions

### Compilation

Compilez le programme à l'aide de `make` :

```bash
make
```

### Exécution

```bash
./philo nombre_de_philosophes temps_pour_mourir temps_pour_manger temps_pour_dormir [nombre_de_repas]
```

#### Arguments

- `number_of_philosophers` : nombre de philosophes et de fourchettes.

- `time_to_die` : temps (en ms) pendant lequel un philosophe peut survivre sans manger.

- `time_to_eat` : temps (en ms) passé à manger.

- `temps_pour_dormir` : temps (en ms) passé à dormir.

- `nombre_de_repas` (facultatif) : nombre de repas que chaque philosophe doit manger avant la fin de la simulation.

Si cette option est omise, la simulation se poursuit jusqu'à ce qu'un philosophe meure.

#### Exemple

```bash
./philo 5 800 200 200 7
```

## Choix techniques

### Structure de données globale (`t_data`)

```c
typedef struct s_data
{
    long            nb_philo;
    long            time_sleep;
    long            time_die;
    long            time_eat;
    long            must_eat;
	long            is_running;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t run_mutex;
} t_data;
```

`t_data` centralise toutes les configurations et tous les états partagés :

- Paramètres de synchronisation et nombre de philosophes.

- `is_running` agit comme un indicateur de simulation global.

- `fork_mutex` est un tableau de mutex, un par fork.

- `print_mutex` garantit une sortie ordonnée et lisible.

- `run_mutex` protège l'accès à `is_running`.

Cette structure est partagée par tous les philosophes et le moniteur.

### Structure Philosophe (`t_philo`)

```c
typedef struct s_philo
{
    long            id;
    long            last_meal;
    long            nb_meal;
    t_data          *data;
    pthread_mutex_t *fork_l;
    pthread_mutex_t *fork_r;
	pthread_mutex_t meal_mutex;
    pthread_mutex_t nb_meal_mutex;
} t_philo;
```
Chaque philosophe possède :

- Son identifiant unique `id`.

- Son état lié au repas (`last_meal`, `nb_meal`).

- Des pointeurs vers ses fourchettes gauche et droite.

- Un pointeur vers le `t_data` partagé.

Deux mutex protègent les données spécifiques au philosophe :

- `meal_mutex` protège `last_meal`.

- `nb_meal_mutex` protège `nb_meal`.

Cette séparation évite les conflits inutiles et garantit la sécurité des lectures simultanées par le moniteur.

---

### Structure du moniteur (`t_monitor`)

```c
typedef struct s_monitor
{
    t_data  *data;
    t_philo *philo;
} t_monitor;
```

Le moniteur est un thread dédié chargé de :

- Détecter la mort d'un philosophe (temps écoulé depuis le dernier repas).

- Arrêter la simulation lorsque tous les philosophes ont suffisamment mangé.

- Mettre à jour `is_running` de manière sécurisée pour les threads.

Le moniteur est la **seule autorité** qui décide quand la simulation se termine.

---
### Stratégie de synchronisation

- Les fourches sont protégées par des mutex afin d'éviter tout accès simultané.

- La sortie est sérialisée à l'aide de `print_mutex`.

- L'état de la simulation (`is_running`) est protégé par `run_mutex`.

- Les philosophes vérifient fréquemment `is_running` afin de s'arrêter immédiatement si nécessaire.

- Les philosophes pairs et impairs prennent les fourchettes dans un ordre opposé afin d'éviter les blocages.

## Notions
---
### C'est quoi un CPU ?
---
Le CPU (Central Processing Unit) est un **composant materiel** qui permet d'**exécuter des instructions machine**

Une instruction machine, c’est par exemple :

- additionner deux nombres

- charger une valeur depuis la mémoire

- écrire une valeur en mémoire

- sauter à une autre instruction

---
### C'est quoi un coeur ?
---
Un cœur est une partie du CPU capable de :

- lire une instruction

- l’exécuter

- passer à la suivante

👉 Un cœur exécute **UNE** suite d’instructions à la fois

Un coeur peut executer un thread.

### Combien de threads un cœur peut exécuter ?

#### Physiquement

À un instant précis :

- un cœur exécute un seul thread

- un seul compteur d’instruction

- un seul ensemble de registres actifs

#### Logiquement

Le cœur **alterne** entre plusieurs threads.

Donc :

- 1 cœur → N threads possibles

- mais 1 seul actif à la fois

#### Cas particulier : Hyper-Threading

Certains cœurs peuvent exécuter :

- 2 threads matériels (SMT)

Mais ca ne nous interrese pas ici.

---
### C'est quoi un thread ?
---
Un thread est un contexte d’exécution composé de :

- un compteur d’instruction

- des registres

- une stack

👉 C’est ce qu’un cœur exécute

### C'est quoi un compteur d’instruction ?

Un compteur d’instruction (Instruction Pointer) c’est :

- un registre spécial du CPU

- qui contient l’**adresse de la prochaine instruction à exécuter**

Exemple :
```ini
RIP = 0x40102A
```

Le CPU fait :

1. lit l’instruction à cette adresse

2. l’exécute

3. incrémente RIP

➡️ Sans compteur d’instruction, **le CPU ne sait pas quoi exécuter**

### C'est quoi un registre CPU ?

Les registres sont :

- de toutes petites mémoires

- dans le CPU

- extrêmement **rapides**

Ils contiennent :

- des valeurs **temporaires**

- des paramètres

- des **résultats intermédiaires**

Exemple :
```c
int a = b + c;
```

En réalité :

- `b` → registre

- `c` → registre

- addition

- résultat → registre

- puis écrit en mémoire

👉 **Chaque thread a ses propres registres**

### C'est quoi la stack ?

La stack est une **zone mémoire** qui sert à stocker :

- variables **locales**

- paramètres de fonctions

- adresses de retour

Exemple :
```c
void f(void)
{
    int x = 42;
}
```

`x` est sur la stack

quand `f` se termine → `x` disparaît

👉 Chaque thread a **sa propre stack**

👉 Deux threads n’ont **jamais la même stack**

---
### C'est quoi un mutex ?
---

Un mutex est un objet de **synchronisation** fourni par le système qui permet de **garantir qu’un seul thread à la fois** exécute une section de code donnée.

Un `pthread_mutex_t` est :

- une structure de données

- partagée entre threads

- gérée en partie en user-space, en partie par le kernel

Il contient (conceptuellement) :

- un état : **libre / verrouillé**

- l’identité du thread propriétaire

- éventuellement une **file d’attente** de threads bloqués

### En pratique

Quand un thread appelle :

```c
pthread_mutex_lock(&m);
```

Il se passe exactement l’un des deux cas suivants :

#### Cas 1 - Mutex libre

- le thread **prend le mutex**

- **continue** immédiatement

#### Cas 2 - Mutex déjà pris

- le thread est **bloqué par le kernel**

- il n’exécute plus **aucune instruction**

- il **attend** que le mutex soit **libéré**

Quand un thread libere un mutex :

```c
pthread_mutex_unlock(&m);
```

- le mutex est **libéré**

- un thread bloqué est **réveillé** (si présent)

---
### C'est quoi l'atomicité ?
---

"`L'atomicité est une propriété utilisée en programmation concurrente pour désigner une opération ou un ensemble d'opérations d'un programme qui s'exécutent entièrement sans pouvoir être interrompues avant la fin de leur déroulement. Une opération qui vérifie cette propriété est qualifiée d'« atomique », (...)`"

Source: [Atomicité (informatique) - Wikipedia FR](https://fr.wikipedia.org/wiki/Atomicit%C3%A9_(informatique))

Une opération atomique peut aussi l'être si des mécanismes de synchronisation protégés par une exclusion mutuelle sont mis en place.

## Resources

- [Dîner des philosophes - Wikipedia FR](https://fr.wikipedia.org/wiki/D%C3%AEner_des_philosophes)

- [Interblocage (Deadblock)- Wikipedia FR](https://fr.wikipedia.org/wiki/Interblocage)

- [Situation de compétition (Race Condition) - Wikipedia FR](https://fr.wikipedia.org/wiki/Situation_de_comp%C3%A9tition)

- [Exclusion mutuelle- Wikipedia FR](https://fr.wikipedia.org/wiki/Exclusion_mutuelle)