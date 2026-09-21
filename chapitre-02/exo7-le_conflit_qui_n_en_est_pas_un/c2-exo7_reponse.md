\# Exercice 7 — Le conflit qui n'en est pas un



\## Objectif



Deux clones du même dépôt ont modifié le même fichier `fusion.txt`, mais à deux endroits différents. Le but était de vérifier que Git pouvait réunir automatiquement ces deux modifications.



\## Préparation



Le fichier `fusion.txt` contenait initialement dix lignes :



```text

ligne 1

ligne 2

ligne 3

ligne 4

ligne 5

ligne 6

ligne 7

ligne 8

ligne 9

ligne 10

```



Deux copies du dépôt ont ensuite été utilisées.



Dans le premier clone, une modification a été effectuée dans une partie du fichier. Elle a été enregistrée dans un commit puis poussée vers GitHub.



Dans le second clone, une autre modification a été effectuée à un endroit éloigné du même fichier.



\## Résultat



Lorsque le second clone a récupéré les modifications du dépôt distant avec :



```powershell

git pull origin main

```



Git a effectué une fusion automatique.



Aucun conflit n'a été demandé car les deux modifications concernaient des zones différentes du fichier. Git a donc pu conserver les deux changements simultanément.



Le fichier final contenait toujours les dix lignes et les modifications provenant des deux clones.



\## Conclusion



Cette manipulation montre que le fait que deux personnes modifient le même fichier ne provoque pas nécessairement un conflit.



Un conflit apparaît lorsque Git ne peut pas déterminer automatiquement quelle modification conserver, notamment lorsque les mêmes lignes ou des zones qui se chevauchent sont modifiées.



Dans notre cas, les modifications étaient suffisamment éloignées pour que Git puisse les assembler automatiquement.



L'exercice démontre donc la différence entre \*\*modifier le même fichier\*\* et \*\*modifier les mêmes lignes\*\* : le premier cas peut être fusionné automatiquement, tandis que le second peut nécessiter une résolution manuelle.



