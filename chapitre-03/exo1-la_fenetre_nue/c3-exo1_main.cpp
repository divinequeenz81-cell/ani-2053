#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

class MonExercice : public renderer::NkCanvasApp {
protected:

    bool OnInit() override {
        Config().title = "Exercice 1 - La fenetre nue";
        Config().width = 960;
        Config().height = 540;
        Config().resizable = true;
        Config().centered = true;

        return true;
    }

    void OnRender(renderer::NkRenderWindow &target) override {
        (void)target;
    }
};

int nkmain(const NkEntryState &state) {
    return renderer::NkCanvasApp::Run<MonExercice>(state);
}