#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "Mon document";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);

    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    bool modified = false;
    math::NkVec2u lastSize = window.GetSize();

    NkString title = "Mon document - ";
    title += std::to_string(lastSize.x).c_str();
    title += " x ";
    title += std::to_string(lastSize.y).c_str();

    window.SetTitle(title);

    while (window.IsOpen()) {
        math::NkVec2u windowSize = window.GetSize();

        if (windowSize.x != lastSize.x || windowSize.y != lastSize.y) {
            lastSize = windowSize;

            NkString newTitle = "Mon document";

            if (modified) {
                newTitle += "*";
            }

            newTitle += " - ";
            newTitle += std::to_string(windowSize.x).c_str();
            newTitle += " x ";
            newTitle += std::to_string(windowSize.y).c_str();

            window.SetTitle(newTitle);
        }
    }

    return 0;
}