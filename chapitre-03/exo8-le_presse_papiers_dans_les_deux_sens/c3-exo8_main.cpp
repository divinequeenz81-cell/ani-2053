#include <NKWindow/Core/NkMain.h>
#include <NKWindow/Core/NkWindow.h>
#include <NKWindow/Core/NkWindowConfig.h>

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
(void)state;

```
NkWindowConfig cfg;
cfg.title = "Exercice 8 - Presse-papiers";
cfg.width = 800;
cfg.height = 500;
cfg.centered = true;
cfg.resizable = true;
cfg.vsync = true;

NkWindow window(cfg);

if (!window.IsValid()) {
    std::cout << "Erreur : impossible de creer la fenetre."
              << std::endl;
    return -1;
}

// ---------------------------------------------------------
// 1. LIRE LE PRESSE-PAPIERS TEXTE ET IMAGE
// ---------------------------------------------------------

NkString texte = window.GetClipboardText();

NkClipboardImage image;
bool imageTrouvee = window.GetClipboardImage(image);

// ---------------------------------------------------------
// 2. TRAITER LE TEXTE
// ---------------------------------------------------------

if (!texte.Empty()) {
    std::cout << "Texte lu dans le presse-papiers : "
              << texte.CStr() << std::endl;

    for (usize i = 0; i < texte.Length(); ++i) {
        char& caractere = texte[i];

        if (caractere >= 'a' && caractere <= 'z') {
            caractere = static_cast<char>(
                caractere - 'a' + 'A'
            );
        }
    }

    std::cout << "Texte transforme en majuscules : "
              << texte.CStr() << std::endl;
}
else {
    std::cout << "Aucun texte trouve dans le presse-papiers."
              << std::endl;
}

// ---------------------------------------------------------
// 3. TRAITER L'IMAGE
// ---------------------------------------------------------

if (imageTrouvee) {
    std::cout << "Image lue dans le presse-papiers."
              << std::endl;

    std::cout << "Dimensions : "
              << image.width << " x "
              << image.height << std::endl;

    std::cout << "Bits par pixel : 32"
              << std::endl;

    // RGBA8 : inversion de R, G et B uniquement.
    // L'alpha A est conserve.

    for (usize i = 0; i < image.pixels.Size(); i += 4) {
        image.pixels[i + 0] =
            static_cast<uint8>(255 - image.pixels[i + 0]);

        image.pixels[i + 1] =
            static_cast<uint8>(255 - image.pixels[i + 1]);

        image.pixels[i + 2] =
            static_cast<uint8>(255 - image.pixels[i + 2]);
    }

    std::cout << "Image inversee en memoire."
              << std::endl;
}
else {
    std::cout << "Aucune image trouvee dans le presse-papiers."
              << std::endl;
}

// ---------------------------------------------------------
// 4. REMETTRE LES RESULTATS DANS LE PRESSE-PAPIERS
// ---------------------------------------------------------

if (!texte.Empty()) {
    if (window.SetClipboardText(texte)) {
        std::cout << "Texte remis dans le presse-papiers : "
                  << texte.CStr() << std::endl;
    }
    else {
        std::cout << "Erreur : impossible de remettre le texte."
                  << std::endl;
    }
}

if (imageTrouvee) {
    if (window.SetClipboardImage(image)) {
        std::cout << "Image inversee et remise dans le "
                     "presse-papiers."
                  << std::endl;
    }
    else {
        std::cout << "Erreur : impossible de remettre l'image."
                  << std::endl;
    }
}

window.Close();

return 0;
```

}
