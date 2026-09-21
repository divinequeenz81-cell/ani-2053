\# Exercice 4 — Le commit partiel



\## Objectif



Deux modifications sans rapport ont été effectuées dans le même fichier `config.txt` :



\* `setting\_one` a été modifié de `10` à `99` ;

\* `setting\_ten` a été modifié de `100` à `999`.



L'objectif était de créer deux commits séparés, chacun ne contenant qu'une seule de ces modifications.



\## Première modification



La première modification a été réalisée avec :



```text

setting\_one = 10

```



devenu :



```text

setting\_one = 99

```



Après les deux modifications, la commande suivante a permis de sélectionner uniquement le premier changement :



```text

git add -p config.txt

```



Pour le bloc concernant `setting\_one`, la réponse `y` a été utilisée. Pour le bloc concernant `setting\_ten`, la réponse `n` a été utilisée.



La vérification avec :



```text

git diff --cached

```



montrait uniquement la modification de `setting\_one`.



Le premier commit a ensuite été créé avec :



```text

git commit -m "Modification de setting\_one"

```



\## Deuxième modification



Après le premier commit, `git diff` montrait uniquement la modification restante :



```text

-setting\_ten = 100

+setting\_ten = 999

```



La commande :



```text

git add -p config.txt

```



a ensuite permis d'ajouter cette seconde modification à l'index.



Le deuxième commit a été créé avec :



```text

git commit -m "Modification de setting\_ten"

```



\## Vérification de l'historique



La commande :



```text

git log --oneline -3

```



a produit :



```text

aa87c9f Modification de setting\_ten

d556211 Modification de setting\_one

c534967 Ajout du fichier de configuration

```



Le premier commit de modification concerne donc uniquement `setting\_one`, tandis que le deuxième concerne uniquement `setting\_ten`.



Les deux changements, bien qu'ils aient été réalisés dans le même fichier, ont ainsi été séparés en deux commits indépendants grâce à `git add -p`.



\## Conclusion



`git add -p` permet de sélectionner seulement certaines parties des modifications présentes dans un fichier. Il est donc possible de créer des commits cohérents et indépendants même lorsque plusieurs changements ont été effectués dans le même fichier.



