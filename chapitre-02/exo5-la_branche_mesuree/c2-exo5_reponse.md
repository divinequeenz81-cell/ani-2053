\# Exercice 5 — La branche mesurée



\## Mesure initiale



Avant la création des trois nouveaux commits, la taille du répertoire `.git` a été mesurée avec PowerShell.



La taille initiale obtenue était de \*\*59,26 Ko\*\*.



\## Création de la branche



Une nouvelle branche appelée `ma-branche` a été créée avec :



```text

git switch -c ma-branche

```



La branche ne constitue pas une copie complète du dépôt. Elle correspond à une référence vers un commit et son coût en stockage est donc très faible par rapport à une copie des fichiers du projet.



\## Les trois commits



Trois commits ont ensuite été réalisés sur `ma-branche` :



```text

ed9c846 Ajouter setting\_eleven

89cc14e Ajouter setting\_twelve

b873207 Ajouter setting\_thirteen

```



Chaque commit a ajouté une nouvelle ligne dans `config.txt`.



Le dernier état du fichier contient donc successivement :



```text

setting\_eleven = 110

setting\_twelve = 120

setting\_thirteen = 130

```



\## Mesure finale



Après les trois commits, la taille du répertoire `.git` a été mesurée à nouveau.



La taille finale obtenue était de \*\*62,55 Ko\*\*.



L'augmentation mesurée est donc :



\*\*62,55 Ko − 59,26 Ko = 3,29 Ko\*\*



Le dépôt a ainsi gagné environ \*\*3,29 Ko\*\* dans son répertoire `.git`.



\## Explication



La création de la branche elle-même ne duplique pas les fichiers du dépôt. Une branche est essentiellement une référence permettant à Git de désigner un commit.



L'augmentation de taille observée provient principalement des nouveaux objets Git nécessaires pour représenter les nouveaux états du projet et les trois commits. Git peut réutiliser des objets déjà présents lorsqu'ils sont identiques, ce qui évite de recopier inutilement les mêmes données.



La taille observée n'est donc pas simplement la somme de la taille des lignes ajoutées à `config.txt`. Elle correspond à l'évolution du stockage interne de Git et dépend notamment des objets déjà présents dans le dépôt.



\## Conclusion



L'expérience montre qu'une branche Git est très légère et ne constitue pas une copie indépendante du projet. En revanche, les nouveaux commits peuvent augmenter la taille du répertoire `.git`, car Git doit conserver les informations nécessaires pour représenter les nouveaux états et leur historique.



Dans cette expérience, trois commits sur `ma-branche` ont fait passer la taille mesurée de \*\*59,26 Ko à 62,55 Ko\*\*, soit une augmentation de \*\*3,29 Ko\*\*.



