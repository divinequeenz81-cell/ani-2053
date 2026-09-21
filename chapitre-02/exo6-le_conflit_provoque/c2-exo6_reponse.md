\# Exercice 6 — Le conflit provoqué



\## Objectif



L'objectif était de provoquer un conflit Git en utilisant deux clones du même dépôt, en modifiant la même ligne du même fichier, puis en résolvant le conflit.



\## 1. Préparation



Un deuxième clone du dépôt a été créé avec la commande :



```powershell

git clone https://github.com/divinequeenz81-cell/ani-2053.git ani-2053-conflit

```



Le fichier utilisé pour provoquer le conflit était :



```text

chapitre-02/exo6-le\_conflit\_provoque/conflit.txt

```



Son contenu initial était :



```text

message initial

```



\## 2. Deux modifications différentes



Deux clones ont été utilisés pour modifier la même ligne du fichier `conflit.txt`.



Le premier clone a créé le commit :



```text

5807fcd Modification depuis clone B

```



Le deuxième clone a créé le commit :



```text

b41b35c Modification depuis clone A

```



Les deux commits modifiaient la même partie du même fichier.



\## 3. Refus du push



Lorsque le clone local a essayé d'envoyer sa modification avec :



```powershell

git push origin main

```



Git a refusé l'opération avec le message :



```text

! \[rejected]        main -> main (fetch first)



error: failed to push some refs to 'https://github.com/divinequeenz81-cell/ani-2053.git'



hint: Updates were rejected because the remote contains work that you do not

have locally.

```



Le dépôt distant contenait donc une modification qui n'était pas présente dans le clone local.



\## 4. Apparition du conflit



La tentative de récupération des modifications avec :



```powershell

git pull origin main

```



a indiqué qu'il existait des fichiers non fusionnés :



```text

error: Pulling is not possible because you have unmerged files.

hint: Fix them up in the work tree, and then use 'git add/rm <file>'

hint: as appropriate to mark resolution and make a commit.

fatal: Exiting because of an unresolved conflict.

```



Le conflit a ensuite été résolu manuellement dans `conflit.txt`.



Le `git status` indiquait alors :



```text

On branch main

Your branch and 'origin/main' have diverged,

and have 1 and 1 different commits each, respectively.



All conflicts fixed but you are still merging.

&nbsp; (use "git commit" to conclude merge)



Changes to be committed:

&nbsp;       modified:   chapitre-02/exo6-le\_conflit\_provoque/conflit.txt

```



\## 5. Commit de résolution



Après avoir résolu le conflit, un commit de fusion a été créé :



```text

6d0b419 Résolution du conflit entre les deux clones

```



L'historique obtenu était :



```text

\*   6d0b419 (HEAD -> main) Résolution du conflit entre les deux clones

|\\

| \* b41b35c (origin/main, origin/HEAD) Modification depuis clone A

\* | 5807fcd Modification depuis clone B

|/

\* 693c76d Préparation du fichier de conflit

```



Le commit `6d0b419` relie donc les deux historiques qui avaient divergé.



\## 6. Push final



Après la résolution, la commande :



```powershell

git push origin main

```



a réussi :



```text

To https://github.com/divinequeenz81-cell/ani-2053.git

&nbsp;  b41b35c..6d0b419  main -> main

```



Le conflit a donc été correctement résolu et la résolution a été envoyée sur le dépôt distant.



\## Conclusion



Cette manipulation montre le fonctionnement d'un conflit Git.



Le premier push a été refusé parce que le dépôt distant avait reçu un commit différent. Les deux historiques ont alors divergé. Comme les deux modifications concernaient la même partie du même fichier, Git n'a pas pu effectuer automatiquement la fusion.



La résolution manuelle du fichier a permis de créer le commit de fusion `6d0b419`. Le push final a ensuite réussi, ce qui confirme que les deux historiques ont été intégrés dans la branche `main`.



