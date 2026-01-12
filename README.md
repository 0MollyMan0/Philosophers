# Philosophers

In this project, I will learn the basics of threading a process. I will learn how to create threads and explore the use of mutexes

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