EN 🇬🇧

# Philosophers

In this project, I will learn the basics of threading a process. I will learn how to create threads and explore the use of mutexes.

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

Source: [Atomicity (computing) - Wikipedia](https://fr.wikipedia.org/wiki/Atomicit%C3%A9_(informatique))

An atomic operation can also be atomic if synchronization mechanisms protected by mutual exclusion are implemented.

FR 🇫🇷

# Philosophers

Dans le cadre de ce projet, j'apprendrai les bases du threading d'un processus. J'apprendrai à créer des threads et j'explorerai l'utilisation des mutex.

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

Source: [Atomicité (informatique) - Wikipedia](https://fr.wikipedia.org/wiki/Atomicit%C3%A9_(informatique))

Une opération atomique peut aussi l'être si des mécanismes de synchronisation protégés par une exclusion mutuelle sont mis en place.