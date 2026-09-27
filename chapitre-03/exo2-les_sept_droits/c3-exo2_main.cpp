#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

static void ConfigureAppData(NkAppData &d) {
    d.appName = "Exo02SeptDroits";
}

NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfgFrame;
    cfgFrame.title = "1 - frame desactive";
    cfgFrame.x = 50;
    cfgFrame.y = 50;
    cfgFrame.width = 400;
    cfgFrame.height = 250;
    cfgFrame.centered = false;
    cfgFrame.frame = false;

    NkWindowConfig cfgResizable;
    cfgResizable.title = "2 - resizable desactive";
    cfgResizable.x = 500;
    cfgResizable.y = 50;
    cfgResizable.width = 400;
    cfgResizable.height = 250;
    cfgResizable.centered = false;
    cfgResizable.resizable = false;

    NkWindowConfig cfgMinimizable;
    cfgMinimizable.title = "3 - minimizable desactive";
    cfgMinimizable.x = 950;
    cfgMinimizable.y = 50;
    cfgMinimizable.width = 400;
    cfgMinimizable.height = 250;
    cfgMinimizable.centered = false;
    cfgMinimizable.minimizable = false;

    NkWindowConfig cfgMovable;
    cfgMovable.title = "4 - movable desactive";
    cfgMovable.x = 50;
    cfgMovable.y = 350;
    cfgMovable.width = 400;
    cfgMovable.height = 250;
    cfgMovable.centered = false;
    cfgMovable.movable = false;

    NkWindowConfig cfgClosable;
    cfgClosable.title = "5 - closable desactive";
    cfgClosable.x = 500;
    cfgClosable.y = 350;
    cfgClosable.width = 400;
    cfgClosable.height = 250;
    cfgClosable.centered = false;
    cfgClosable.closable = false;

    NkWindowConfig cfgMaximizable;
    cfgMaximizable.title = "6 - maximizable desactive";
    cfgMaximizable.x = 950;
    cfgMaximizable.y = 350;
    cfgMaximizable.width = 400;
    cfgMaximizable.height = 250;
    cfgMaximizable.centered = false;
    cfgMaximizable.maximizable = false;

    NkWindowConfig cfgFullscreen;
    cfgFullscreen.title = "7 - canFullscreen desactive";
    cfgFullscreen.x = 275;
    cfgFullscreen.y = 650;
    cfgFullscreen.width = 400;
    cfgFullscreen.height = 250;
    cfgFullscreen.centered = false;
    cfgFullscreen.canFullscreen = false;

    NkWindow windowFrame(cfgFrame);
    NkWindow windowResizable(cfgResizable);
    NkWindow windowMinimizable(cfgMinimizable);
    NkWindow windowMovable(cfgMovable);
    NkWindow windowClosable(cfgClosable);
    NkWindow windowMaximizable(cfgMaximizable);
    NkWindow windowFullscreen(cfgFullscreen);

    bool running = true;

    NkEventSystem &events = NkEvents();

    events.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            running = false;
        });

    events.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                running = false;
            }
        });

    while (running) {
        events.PollEvents();
        NkClock::Sleep((int64)10);
    }

    windowFrame.Close();
    windowResizable.Close();
    windowMinimizable.Close();
    windowMovable.Close();
    windowClosable.Close();
    windowMaximizable.Close();
    windowFullscreen.Close();

    return 0;
}