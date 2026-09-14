\# Exercice 3 — Le module seul



\## Commande utilisée



jenga build --project NKMath --config Debug



\## Ordre de construction affiché par Jenga



Build Order (5 projects):

&nbsp; 1. NKPlatform \[STATIC\_LIB]

&nbsp; 2. NKCore \[STATIC\_LIB] (depends: NKPlatform)

&nbsp; 3. NKMemory \[STATIC\_LIB] (depends: NKCore, NKPlatform)

&nbsp; 4. NKContainers \[STATIC\_LIB] (depends: NKCore, NKMemory, NKPlatform)

&nbsp; 5. NKMath \[STATIC\_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)



\## Arbre (le premier construit en bas, NKMath en haut)



&nbsp;               NKMath

&nbsp;                 ↑

&nbsp;             NKContainers

&nbsp;                 ↑

&nbsp;              NKMemory

&nbsp;                 ↑

&nbsp;               NKCore

&nbsp;                 ↑

&nbsp;             NKPlatform



\## Ce que ça montre



L'ordre n'a pas été écrit à la main : il est calculé par Jenga à partir

des dependson déclarés dans chaque fichier .jenga (section 1.8.1 du

chapitre). Ici la chaîne est strictement linéaire : chaque module

dépend de tous les modules situés en dessous de lui, et d'aucun de

ceux situés au-dessus. NKPlatform est construit en premier car il ne

dépend de rien (le socle de la pile, section 1.10.1) ; NKMath est

construit en dernier car il dépend, directement ou indirectement, des

quatre autres. Cinq projets ont été construits en tout : NKPlatform,

NKCore, NKMemory, NKContainers, et NKMath lui-même.

