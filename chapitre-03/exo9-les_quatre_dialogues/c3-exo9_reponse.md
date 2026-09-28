# Exercice 9 — Les quatre dialogues

## Travail réalisé

Les quatre dialogues natifs ont été utilisés :

1. Dialogue d'ouverture de fichier avec OpenFileDialog.
2. Dialogue d'enregistrement avec SaveFileDialog.
3. Dialogue de sélection de dossier avec OpenFolderDialog.
4. Dialogue de choix de couleur avec ColorPicker.

Pour chacun des dialogues, le résultat est vérifié avec la propriété confirmed.

Lorsque l'utilisateur valide, les informations sélectionnées sont affichées.

Lorsque l'utilisateur annule ou ferme le dialogue sans effectuer de sélection, le programme traite correctement l'annulation et continue son exécution sans planter.

## Vérification

Les quatre dialogues ont été testés en les annulant sans effectuer de sélection.

Résultat : les annulations sont correctement prises en compte et le programme continue normalement.
