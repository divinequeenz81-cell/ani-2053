\# Exercice 5 — Votre premier projet



\## Fichiers créés



Applications/MonEssai/

├── MonEssai.jenga

└── src/

&nbsp;   └── main.cpp



\### src/main.cpp



int main()

{

&nbsp;   return 0;

}



Un programme minimal qui n'affiche rien, comme demandé par l'énoncé.



\### MonEssai.jenga



from Jenga import \*



with project("MonEssai"):

&nbsp;   consoleapp()

&nbsp;   language("C++")

&nbsp;   cppdialect("C++17")

&nbsp;   location(".")



&nbsp;   files(\["src/\*\*.cpp"])



&nbsp;   objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

&nbsp;   targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")



&nbsp;   with filter("system:Windows"):

&nbsp;       usetoolchain(TC\_WINDOWS)



&nbsp;   with filter("config:Debug"):

&nbsp;       defines(\["\_DEBUG"]); optimize("Off"); symbols(True)

&nbsp;   with filter("config:Release"):

&nbsp;       defines(\["NDEBUG"]); optimize("Speed"); symbols(False)



\## Déclaration au workspace



Ajout dans Nkentseu.jenga, dans la section des Applications, juste

après la déclaration de NK3DModeler, en suivant exactement le même

format que les autres projets (section 1.9 du chapitre) :



&nbsp;   with include("Applications/MonEssai/MonEssai.jenga"):



&nbsp;       pass



Sa

