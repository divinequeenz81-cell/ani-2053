\# Exercice 4 — Le fichier de projet annoté



\## Module choisi : NKCanvas



Fichier : `Kernel/Runtime/NKCanvas/NKCanvas.jenga`

Ce module n'a pas été montré dans le chapitre (le chapitre annonce

seulement qu'il sera détaillé au chapitre 5 : fenêtre, boucle,

primitives).



---



\## En-tête et imports



```python

from Jenga import \*

from jengaconfig import \*



import os

import shutil

import subprocess

```



\- `from Jenga import \*` : import standard vu dans le chapitre (section 1.3), donne accès aux fonctions du DSL (project, files, filter...).

\- `from jengaconfig import \*` : import du raccourci maison du dépôt (section 1.7), donne accès à `nkentseudependson` et aux constantes globales (TC\_WINDOWS, WANT\_VULKAN...).

\- `import os`, `import shutil`, `import subprocess` : imports Python standards. \*\*?\*\* Le chapitre dit qu'un `.jenga` est "tout ce que vous savez faire en Python", mais ne montre jamais d'import de bibliothèque standard dans un vrai fichier — ici c'est utilisé concrètement pour lire une variable d'environnement (`os.getenv`).



---



\## Variables calculées avant le projet



```python

\_HAS\_LIBDECOR = PkgExists("libdecor-0")

\_WAYLAND\_LINKS = \[...]

\_WAYLAND\_TEST\_LINKS = \[...]

\_WAYLAND\_DEFINES = \[...]

if \_HAS\_LIBDECOR:

&nbsp;   \_WAYLAND\_LINKS.append("decor-0")

&nbsp;   ...

```



\- \*\*?\*\* `PkgExists("libdecor-0")` : fonction qui teste si un paquet système est présent sur la machine qui construit. Ce n'est pas une fonction du chapitre ; elle vient probablement de `jengaconfig`, mais son fonctionnement exact n'est pas expliqué.

\- Le `if \_HAS\_LIBDECOR:` est un exemple concret de ce que le chapitre annonçait en théorie (section 1.5.8/1.3) : "toute la puissance de Python est disponible" — ici une vraie condition Python modifie la configuration selon ce qui est installé sur la machine, avant même que `project()` ne soit appelé.



```python

\_VK\_ON  = f"NKENTSEU\_ENABLE\_VULKAN\_BACKEND={1 if WANT\_VULKAN else 0}"

\_VK\_OFF = "NKENTSEU\_ENABLE\_VULKAN\_BACKEND=0"

```



\- \*\*?\*\* `WANT\_VULKAN` : variable globale, vient probablement de `jengaconfig` ou `config/graphics.jenga` (mentionné plus loin). Pas expliquée dans le chapitre.

\- Ligne Python pure (f-string) utilisée pour construire une macro de préprocesseur qui variera selon la plateforme (0 ou 1).



---



\## `with project("NKCanvas")` : le projet



```python

with project("NKCanvas"):

&nbsp;   language("C++")

&nbsp;   cppdialect("C++17")

&nbsp;   location(".")

```



\- Type de projet : \*\*pas de `staticlib()`/`consoleapp()` explicite ici\*\*, comme pour NKMath dans le chapitre (section 1.6) — le type vient du registre partagé via `nkentseudependson(..., selfexport="NKCanvas", ...)` plus bas.

\- `language`, `cppdialect`, `location` : identiques à ce que montre le chapitre (section 1.5.1/1.5.3).



---



\## Dépendances (nkentseudependson)



```python

\_canvasDeps = \["NKWindow", "NKFont", "NKImage", "NKStream", "NKTime", "NKGlad", "NKThreading"]

...

if USE\_CANVAS\_NKUI:

&nbsp;   \_canvasDeps.append("NKUI")

&nbsp;   \_canvasDefines.append("NK\_CANVAS\_WITH\_NKUI=1")

nkentseudependson(

&nbsp;   \_canvasDeps,

&nbsp;   selfexport="NKCanvas",

&nbsp;   extra\_includes=\["src"] + (\[VULKAN\_INCLUDE] if VULKAN\_INCLUDE else \[]),

&nbsp;   extra\_defines=\_canvasDefines,

)

```



\- `nkentseudependson` : le raccourci du chapitre (section 1.7) — remplace `includedirs` + `links` + `dependson` + `defines` en un appel, avec résolution transitive.

\- Sept dépendances directes : `NKWindow`, `NKFont`, `NKImage`, `NKStream`, `NKTime`, `NKGlad`, `NKThreading`.

\- \*\*?\*\* `USE\_CANVAS\_NKUI` : drapeau conditionnel qui ajoute une huitième dépendance (`NKUI`) seulement si activé. Vient de `config/graphics.jenga` d'après le commentaire du fichier, mais ce fichier n'est pas lu ici.

\- \*\*?\*\* `VULKAN\_INCLUDE` : variable conditionnelle ajoutée aux chemins d'inclusion si elle existe. Pas expliquée dans le chapitre.

\- Le commentaire précise : "On ne linke PAS les deps NK (juste dependson)" — confirme la distinction `links` vs `dependson` vue en section 1.5.5 : ici, seul l'ordre de construction est garanti, pas l'édition de liens automatique pour ces sept modules.



---



\## Fichiers sources



```python

files(\[

&nbsp;   "src/NKCanvas/\*\*.cpp",

&nbsp;   "src/NKCanvas/\*\*.h",

])

```



\- Motif classique du chapitre (section 1.5.4) : `\*\*` descend dans tous les sous-dossiers.



```python

objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

```



\- Variables `%{...}` identiques à celles du chapitre (section 1.5.6).



---



\## Filtres par plateforme (le cœur du fichier)



Chaque bloc `with filter("system:XXX"):` correspond exactement au mécanisme du chapitre (section 1.5.7) : condition qui n'applique son contenu que si elle est vraie.



| Filtre | Ce qu'il fait |

|---|---|

| `system:Windows \&\& options:windows-runtime=uwp` | change objdir/targetdir pour un sous-dossier `-uwp` |

| `system:Windows \&\& !...uwp \&\& !Xbox...` | Windows desktop classique : toolchain, defines, `links(gdi32, user32, d3d11, d3d12, dxgi, dxguid, ...)` |

| `system:UWP \\|\\| ...` | branche UWP séparée, toolchain `xbox-clang` |

| `system:Linux \&\& options:linux-backend=xlib \\|\\| ...` | branche X11 (`links(X11, Xext, GL)`) |

| `system:Linux \&\& options:linux-backend=headless \\|\\| ...` | mode sans fenêtre |

| `system:Linux \&\& options:linux-backend=xcb` | branche XCB, chemins objdir/targetdir dédiés |

| `system:Linux \&\& options:linux-backend=wayland` | branche Wayland, utilise `\_WAYLAND\_LINKS` calculé plus haut |

| `system:macOS` | toolchain `clang-native`, \*\*`frameworks(\["Metal", "QuartzCore"])`\*\* |

| `system:Android` | toolchain `android-ndk`, `links(android, EGL, GLESv3, ...)` |

| `system:HarmonyOS` | \*\*`pchheader("")` / `pchsource("")`\*\* — désactive le header précompilé, exactement le même motif documenté pour Android dans le chapitre (section 1.6) |

| `system:iOS` | fichiers `.mm` ajoutés explicitement + \*\*`excludefiles(\[...])`\*\* pour retirer OpenGL/Vulkan |

| `system:Web` | toolchain `emscripten` |

| `system:XboxSeries \\|\\| system:XboxOne` | toolchain `xbox-clang` |



Points \*\*?\*\* dans cette section :

\- \*\*?\*\* `options:linux-backend=xlib`, `options:headless`, `options:windows-runtime=uwp` : la syntaxe `options:...` n'est jamais montrée dans le chapitre (qui ne montre que `system:...` et `config:...`). Ce sont visiblement des options personnalisées définies quelque part dans la configuration du dépôt.

\- \*\*?\*\* `frameworks(\[...])` : fonction spécifique à macOS/iOS, absente du tableau du chapitre (section 1.5.8).

\- \*\*?\*\* `excludefiles(\[...])` : jamais mentionnée dans le chapitre ; fait visiblement l'inverse de `files()`, pour retirer des fichiers déjà inclus par le motif global.

\- \*\*?\*\* `libdirs(\[VULKAN\_LIB])` : ajoute un dossier de bibliothèques, absent du tableau du chapitre.



---



\## Filtres de configuration



```python

with filter("config:Debug"):

&nbsp;   defines(\["\_DEBUG", "DEBUG"])

&nbsp;   optimize("Off")

&nbsp;   symbols(True)

with filter("config:Release"):

&nbsp;   defines(\["NDEBUG"])

&nbsp;   optimize("Speed")

&nbsp;   symbols(False)

```



\- Identique mot pour mot au motif du chapitre (section 1.5.7 et exemple NKMath section 1.6).



---



\## Bloc de tests



```python

with filter("(system:Linux || system:macOS || (system:Windows \&\& ...)) \&\& !system:Android \&\& !system:iOS \&\& !system:Web"):

&nbsp;   with test():

&nbsp;       testfiles(\["tests/\*\*.cpp"])

&nbsp;       links(\["NKCanvas", "NKWindow", "NKTime"])

&nbsp;       with filter("system:Linux \&\& options:linux-backend=wayland"):

&nbsp;           ...

&nbsp;       with filter("system:Linux \&\& options:linux-backend=xcb"):

&nbsp;           ...

&nbsp;       with filter("system:Linux \&\& options:linux-backend=xlib || ..."):

&nbsp;           ...

&nbsp;       with filter("system:Windows \&\& ..."):

&nbsp;           ...

```



\- `with test(): testfiles(\[...])` : motif du chapitre (section 1.5.9) — déclare une suite de tests attachée au projet.

\- \*\*Nouveau par rapport au chapitre :\*\* les tests ne sont activés que sur desktop (Linux/macOS/Windows non-UWP/non-Xbox), exclus explicitement d'Android/iOS/Web — logique, on ne lance pas une suite de tests sur ces cibles.

\- \*\*?\*\* Des filtres \*\*imbriqués à l'intérieur du bloc `test()`\*\* : le chapitre ne montre jamais de filtre dans un filtre. Ici, à l'intérieur de la suite de tests elle-même, on refiltre par backend Linux (wayland/xcb/xlib) pour ajouter les bons `links`. Le principe (condition qui restreint ce qui suit) reste le même qu'en section 1.5.7, seulement imbriqué.

\- `links(\["NKCanvas", "NKWindow", "NKTime"])` dans les tests : contrairement au corps du projet qui n'utilisait que `dependson` via `nkentseudependson`, ici les tests ont besoin d'une \*\*vraie édition de liens\*\* (`links`) avec NKCanvas et ses dépendances, car l'exécutable de test doit réellement résoudre les symboles — cohérent avec la distinction dependson/links de la section 1.5.5.



---



\## Récapitulatif



\- \*\*Type\*\* : bibliothèque, déterminée par le registre via `nkentseudependson(selfexport="NKCanvas")`, pas par un appel `staticlib()` explicite.

\- \*\*Sources\*\* : `src/NKCanvas/\*\*.cpp` et `\*\*.h`, avec des ajouts/exclusions spécifiques par plateforme (`.mm` sur macOS/iOS, exclusion d'OpenGL/Vulkan sur iOS).

\- \*\*Dépendances\*\* : 7 modules fixes + 1 optionnel (`NKUI`) selon un drapeau de configuration, gérés par `nkentseudependson`.

\- \*\*Filtres\*\* : un par plateforme (Windows, UWP, Linux×3 backends, macOS, Android, HarmonyOS, iOS, Web, Xbox), plus deux pour Debug/Release, plus des filtres imbriqués dans le bloc de tests.

\- \*\*Tests\*\* : activés seulement sur desktop, avec leurs propres filtres imbriqués par backend Linux.

\- \*\*Éléments non couverts par le chapitre\*\* (marqués `?` ci-dessus) : `PkgExists`, `WANT\_VULKAN`/`VULKAN\_INCLUDE`/`VULKAN\_LIB` (variables de config externes), la syntaxe `options:...` dans les filtres, `frameworks()`, `excludefiles()`, `libdirs()`, et les filtres imbriqués dans un bloc `test()`.

