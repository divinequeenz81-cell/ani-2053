#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "Facteur d'echelle";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);

    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen()) {
        math::NkVec2u windowSize = window.GetSize();
        float32 scale = window.GetDpiScale();
        NkSurfaceDesc surface = window.GetSurfaceDesc();

        logger.Info(
            "Fenetre : %u x %u | Cible de rendu : %u x %u | Facteur d'echelle : %.2f",
            windowSize.x,
            windowSize.y,
            surface.width,
            surface.height,
            scale
        );
    }

    return 0;
}