\# Exercice 2 — Mesurer avant de croire



\## Commandes utilisées (PowerShell)



(Get-ChildItem -Recurse -Include \*.cpp,\*.h | Where-Object { $\_.FullName -notmatch '\\Build\\' }).Count

(Get-ChildItem -Recurse -Include \*.cpp,\*.h | Where-Object { $\_.FullName -notmatch '\\Build\\' } | Get-Content | Measure-Object -Line).Lines

(Get-ChildItem -Recurse -Include \*.jenga | Where-Object { $\_.FullName -notmatch '\\Build\\' }).Count



\## Mes résultats



| Mesure | Chapitre | Mon chiffre |

|---|---|---|

| Fichiers .cpp + .h | 2641 | 4335 |

| Lignes de code | 1 193 385 | 1 905 063 |

| Fichiers .jenga | 221 | 207 |



\## Explication de l'écart



J'ai exclu le dossier Build de mes comptages, ce qui écarte la première

cause possible d'écart. L'écart restant est particulier : j'ai plus de

fichiers source et plus de lignes que le chapitre, mais moins de

fichiers .jenga. Cette asymétrie s'explique le mieux par l'évolution du

dépôt dans le temps : le chapitre précise que ses chiffres ont été

mesurés "le jour où" l'auteur écrivait cette page. Depuis, du code a

manifestement été ajouté au moteur (plus de .cpp/.h, plus de lignes),

pendant que des fichiers .jenga ont pu être consolidés ou fusionnés

(via le registre nkentseudependson décrit en section 1.7, qui réduit

le besoin de dupliquer des déclarations projet par projet). Le dépôt

n'est donc pas figé : mesurer soi-même donne un instantané différent

de celui du livre, sans que cela indique une erreur de comptage.

