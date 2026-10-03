# Exercice 1 — La fenêtre nue

## Objectif

Créer une fenêtre vide avec NkCanvasApp, sans aucun dessin à l'intérieur.

## Configuration de la fenêtre

Dans OnInit(), la fenêtre est configurée avec :

- Titre : Exercice 1 - La fenetre nue
- Largeur : 960
- Hauteur : 540
- Fenêtre redimensionnable : oui
- Fenêtre centrée : oui

## Rendu

La méthode OnRender() ne dessine aucun élément. La fenêtre reste donc vide.

## Point d'entrée

Le programme utilise nkmain() et lance l'application avec :

renderer::NkCanvasApp::Run<MonExercice>(state)

## Résultat

La fenêtre s'ouvre correctement avec une surface noire et vide. L'exercice est fonctionnel.
