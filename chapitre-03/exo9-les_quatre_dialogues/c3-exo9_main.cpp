#include <NKWindow/Core/NkMain.h>
#include <NKWindow/Core/NkDialogs.h>

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    (void)state;

    std::cout << "=== Exercice 9 : Les quatre dialogues ==="
              << std::endl;

    // 1. Dialogue d'ouverture de fichier
    std::cout << "\n1. Ouverture d'un fichier..." << std::endl;

    NkDialogResult fichier = NkDialogs::OpenFileDialog(
        "*.*",
        "Choisir un fichier"
    );

    if (fichier.confirmed) {
        std::cout << "Fichier choisi : "
                  << fichier.path.CStr()
                  << std::endl;
    }
    else {
        std::cout << "Ouverture annulee." << std::endl;
    }

    // 2. Dialogue d'enregistrement
    std::cout << "\n2. Enregistrement d'un fichier..." << std::endl;

    NkDialogResult sauvegarde = NkDialogs::SaveFileDialog(
        "txt",
        "Enregistrer un fichier"
    );

    if (sauvegarde.confirmed) {
        std::cout << "Fichier a enregistrer : "
                  << sauvegarde.path.CStr()
                  << std::endl;
    }
    else {
        std::cout << "Enregistrement annule." << std::endl;
    }

    // 3. Dialogue de selection de dossier
    std::cout << "\n3. Selection d'un dossier..." << std::endl;

    NkDialogResult dossier = NkDialogs::OpenFolderDialog(
        "Choisir un dossier"
    );

    if (dossier.confirmed) {
        std::cout << "Dossier choisi : "
                  << dossier.path.CStr()
                  << std::endl;
    }
    else {
        std::cout << "Selection du dossier annulee." << std::endl;
    }

    // 4. Dialogue de choix de couleur
    std::cout << "\n4. Choix d'une couleur..." << std::endl;

    NkDialogResult couleur = NkDialogs::ColorPicker();

    if (couleur.confirmed) {
        std::cout << "Couleur choisie : 0x"
                  << std::hex
                  << couleur.color
                  << std::dec
                  << std::endl;
    }
    else {
        std::cout << "Choix de la couleur annule." << std::endl;
    }

    std::cout << "\nTous les dialogues ont ete testes."
              << std::endl;

    return 0;
}