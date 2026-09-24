\# Exercice 1 — La fenêtre nue



\## Nombre de lignes



Le programme contient 17 lignes de code, en comptant les lignes vides.



\## Correspondance avec le chapitre



1\. `#include "NKWindow/NKWindow.h"` : permet d'utiliser les fonctionnalités de la fenêtre.

2\. `#include "NKWindow/NKMain.h"` : fournit le point d'entrée `nkmain`.

3\. `int nkmain(const NkEntryState \&state)` : point d'entrée du programme.

4\. `NkWindowConfig cfg;` : crée la configuration de la fenêtre.

5\. `cfg.title = "Ma fenetre";` : définit le titre de la fenêtre.

6\. `cfg.width = 1280;` : définit sa largeur.

7\. `cfg.height = 720;` : définit sa hauteur.

8\. `NkWindow window(cfg);` : crée la fenêtre avec cette configuration.

9\. `if (!window.IsOpen())` : vérifie si la fenêtre a été correctement créée.

10\. `logger.Error(...)` : affiche un message si la création échoue.

11\. `return -1;` : arrête le programme en cas d'échec.

12\. `while (window.IsOpen())` : maintient le programme en fonctionnement tant que la fenêtre est ouverte.

13\. `return 0;` : termine proprement le programme.



Le programme correspond au plus petit programme présenté dans le chapitre : il configure une fenêtre, la crée, vérifie sa création, la maintient ouverte et se termine proprement.



