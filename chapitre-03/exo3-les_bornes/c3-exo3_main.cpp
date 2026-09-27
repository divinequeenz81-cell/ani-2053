#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Les bornes";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.minWidth = 640;
    cfg.minHeight = 360;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen()) {
    }

    return 0;
}