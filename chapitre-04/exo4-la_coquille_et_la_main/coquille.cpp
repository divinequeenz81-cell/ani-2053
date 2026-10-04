#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
using namespace nkentseu;
using namespace nkentseu::renderer;
class Coquille : public NkCanvasApp {
public:
    Coquille() {
        Config().title = "La coquille et la main";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = NkColor2D{18,18,24,255};
    }
    void OnUpdate(float32 dt) override {
        mX += mVitesse * dt;
        const float32 largeur = static_cast<float32>(Window().GetSize().x);
        if (mX < 0.f || mX + 50.f > largeur) mVitesse = -mVitesse;
    }
    void OnRender(NkRenderWindow &target) override {
        target.Clear(NkColor2D{18,18,24,255});
        NkRenderer2D &r = target.GetRenderer2D();
        r.DrawFilledRect(NkRect2f{mX,mY,50.f,50.f}, NkColor2D{255,0,0,255});
        target.Display();
    }
private:
    float32 mX=100.f;
float32 mY=100.f;
float32 mVitesse=200.f;
};
int nkmain(const nkentseu::NkEntryState &state) {
    return NkCanvasApp::Run<Coquille>(state);
}