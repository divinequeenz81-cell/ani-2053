# Exercice 6 - Les deux erreurs de dependance

## Preparation

Pour observer un vrai effet, MonEssai a d'abord ete modifie pour dependre
reellement de NKMath : ajout de #include "NKMath/NkFunctions.h" et d'un
appel a nkentseu::math::NkSqrt(4.0f) dans main.cpp, avec dans
MonEssai.jenga :

    includedirs(["%{wks.location}/Kernel/Foundation/NKMath/src"])
    dependson(["NKMath"])
    links(["NKMath"])

Avec les deux presents, la construction reussit (6/6 projets construits,
MonEssai lie sans erreur).

## Test 1 - Retrait de dependson (links conserve)

Commande : jenga build --project MonEssai --config Debug

Message obtenu :

Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]

Found 1 source file(s)
[1/1] Compiled: main.cpp
Linking...

Compilation Error: Link Failed
C:/msys64/ucrt64/bin/ld: cannot find -lNKMath: No such file or directory
clang++: error: linker command failed with exit code 1

Build Failed - Errors: 1

## Test 2 - Retrait de links (dependson remis)

Commande : jenga build --project MonEssai --config Debug

Message obtenu :

Build Order (6 projects):
  1. NKPlatform [STATIC_LIB]
  2. NKCore [STATIC_LIB] (depends: NKPlatform)
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform)
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform)
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)
  6. MonEssai [CONSOLE_APP] (depends: NKMath)

[1/1] Compiled: main.cpp
Linking...
Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

Build Successful - aucune erreur, aucun avertissement.

## Ce qui distingue les deux messages

Le premier cas (sans dependson) echoue a l'edition de liens : le linker
(ld, via clang++) ne trouve pas la bibliotheque NKMath.lib, avec le
message exact "cannot find -lNKMath". C'est coherent avec le chapitre
(section 1.5.5) : dependson garantit que NKMath est construit avant
MonEssai. Sans lui, l'ordre de construction affiche (Build Order)
ne contient meme plus NKMath du tout - Jenga ne sait plus qu'il doit
s'en preoccuper, et le lien echoue faute d'un fichier .lib a jour ou
disponible.

Le deuxieme cas (sans links) surprend : la construction reussit sans
aucun message d'erreur ni d'avertissement, alors que le chapitre
presente links comme la declaration necessaire pour "ajouter une
bibliotheque a l'edition de liens" (section 1.5.5), separement de
dependson qui ne garantirait que l'ordre. Observation faite ici : un
dependson vers une bibliotheque statique du meme workspace semble
suffire, dans cette version de Jenga, a ce que le linker la trouve et
resolve le symbole NkSqrt - sans qu'un links explicite soit necessaire.

## Conclusion

Les deux retraits ne produisent donc pas des erreurs symetriques : le
retrait de dependson casse la construction avec un message clair et
explicite (bibliotheque introuvable au lien), tandis que le retrait de
links, dans ce depot et cette configuration, ne casse rien de visible.
Ce resultat differe de la distinction stricte presentee dans le
chapitre entre dependson (ordre seulement) et links (edition de liens
seulement) - un exemple concret de ce que le chapitre appelle
"attraper l'auteur en faute" : le comportement reel d'un outil peut
s'ecarter de sa description theorique, et seule l'experimentation
directe le revele.
