\# Compte rendu – Exercice 8 : Le presse-papiers dans les deux sens



\## Presse-papiers texte



J’ai testé le programme avec un texte présent dans le presse-papiers.



Le programme a réussi à lire le texte et à le transformer en majuscules avant de le remettre dans le presse-papiers.



Exemple obtenu lors du test :



Texte lu dans le presse-papiers :

`\& "C:\\Users\\GAMING\\Desktop\\Nkentseu\\Build\\Bin\\Debug-Windows\\MonEssai\\MonEssai.exe"`



Texte remis dans le presse-papiers :

`\& "C:\\USERS\\GAMING\\DESKTOP\\NKENTSEU\\BUILD\\BIN\\DEBUG-WINDOWS\\MONESSAI\\MONESSAI.EXE"`



La partie texte fonctionne donc correctement.



\## Presse-papiers image



J’ai essayé de tester la partie image avec une image copiée dans le presse-papiers.



Le programme affiche :



`Aucune image trouvee dans le presse-papiers.`



J’ai également vérifié avec PowerShell, mais aucune image n’a été récupérée depuis le presse-papiers.



Je n’ai donc pas pu obtenir les dimensions ni le nombre de bits par pixel de l’image.



\## Conclusion



La partie texte fonctionne : le texte est lu, transformé en majuscules et remis dans le presse-papiers.



Pour la partie image, le programme arrive jusqu’à la lecture du presse-papiers, mais aucune image n’est détectée. Je me suis donc arrêté à cette étape sans inventer de résultat.



