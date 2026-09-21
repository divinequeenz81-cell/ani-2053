\# Exercice 2 — Les trois endroits



\## Étape 1 — Après la modification



Le fichier `fichier1.txt` a été modifié avec la commande :



`Set-Content -Path fichier1.txt -Value "Deuxieme contenu"`



La commande `git status` a affiché :



```text

Changes not staged for commit:

&nbsp;       modified:   fichier1.txt



no changes added to commit

```



La modification existe dans l'espace de travail, mais elle n'est pas encore préparée pour le prochain commit.



\## Étape 2 — Après `git add`



La commande utilisée est :



`git add fichier1.txt`



Puis `git status` a affiché :



```text

Changes to be committed:

&nbsp;       modified:   fichier1.txt

```



La modification a été placée dans la zone de transit (index). Elle est maintenant prête à être enregistrée dans un commit.



\## Étape 3 — Après `git commit`



La commande utilisée est :



`git commit -m "Modification du contenu de fichier1"`



Le commit a été créé avec l'identifiant :



`80ad490`



Puis `git status` a affiché :



```text

nothing to commit, working tree clean

```



La modification est maintenant enregistrée dans l'historique Git et il n'y a plus de modification en attente.



\## Ce qui change entre les trois sorties



Après la modification, Git indique `Changes not staged for commit` : le fichier a changé dans l'espace de travail, mais la modification n'est pas encore dans l'index.



Après `git add`, Git indique `Changes to be committed` : la modification est maintenant dans l'index et sera incluse dans le prochain commit.



Après `git commit`, Git indique `nothing to commit, working tree clean` : la modification a été enregistrée dans l'historique et l'espace de travail est propre.



Ces trois états illustrent le passage d'une modification de l'espace de travail vers l'index, puis de l'index vers l'historique Git.



