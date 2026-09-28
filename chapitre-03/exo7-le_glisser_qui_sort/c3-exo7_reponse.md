# Exercice 7 — Le glisser qui sort

## Sans capture

Le glisser commence dans la fenêtre avec un bouton de la souris maintenu.
Lorsque le pointeur sort de la fenêtre, les mouvements de souris ne sont plus suivis normalement par la fenêtre.
Le glisser ne peut donc plus continuer correctement.

## Avec capture

Le glisser commence également dans la fenêtre avec un bouton de la souris maintenu.
La fenêtre capture ensuite la souris avec `CaptureMouse()`.
Même lorsque le pointeur sort de la fenêtre, les mouvements continuent d'être reçus.
Le glisser peut donc continuer jusqu'au relâchement du bouton.

## Différence du point de vue de l'utilisateur

Sans capture, sortir de la fenêtre interrompt ou perturbe le glisser.
Avec capture, le glisser reste actif même lorsque le pointeur se trouve à l'extérieur de la fenêtre, jusqu'au relâchement du bouton.
