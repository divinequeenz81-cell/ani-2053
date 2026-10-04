#include <NKCanvas/App/NkCanvasApp.h>
#include <NKCanvas/Renderer/Targets/NkRenderWindow.h>
#include <NKCanvas/Renderer/Core/NkRenderer2D.h>
#include <NKWindow/Core/NkMain.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

class InterfaceApp : public NkCanvasApp {
private:
    float32 temps = 0.f;
    bool captureAvec = false;

public:
    InterfaceApp() = default;

protected:
    bool OnInit() override {
        Config().title = "Interface qui ne defile pas";
        Config().width = 960;
        Config().height = 540;
        Config().resizable = false;
        Config().centered = true;
        Config().clearColor = NkColor2D{25, 25, 30, 255};

        return true;
    }

    void OnUpdate(float32 deltaTime) override {
        temps += deltaTime;
    }

    void OnRender(NkRenderWindow &target) override {
        target.Clear(NkColor2D{25, 25, 30, 255});

        NkRenderer2D &renderer = target.GetRenderer2D();

        // Vue du monde qui avance vers la droite
        NkView2D view = target.GetDefaultView();

        view.center.x = 480.f + temps * 80.f;
        view.center.y = 270.f;
        target.SetView(view);
        // target.ResetView();
        // Monde large : rangee de carres
        for (int i = 0; i < 30; ++i) {
            float32 x = static_cast<float32>(i * 100);

            renderer.DrawRect(
                NkRect2f{x, 220.f, 70.f, 70.f},
                NkColor2D{
                    static_cast<uint8>((40 + i * 7) % 255),
                    static_cast<uint8>((100 + i * 5) % 255),
                    static_cast<uint8>((180 + i * 3) % 255),
                    255
                }
            );
        }

        renderer.DrawLine(
            NkVec2f{0.f, 310.f},
            NkVec2f{3000.f, 310.f},
            NkColor2D::White,
            3.f
        );

        // IMPORTANT :
        // Version sans ResetView pour la capture.
        target.ResetView();

        // Barre fixe en haut
        renderer.DrawRect(
            NkRect2f{0.f, 0.f, 960.f, 70.f},
            NkColor2D{20, 20, 20, 255}
        );

        renderer.DrawLine(
            NkVec2f{0.f, 70.f},
            NkVec2f{960.f, 70.f},
            NkColor2D::White,
            2.f
        );

        // Elements de l'interface
        renderer.DrawRect(
            NkRect2f{25.f, 18.f, 120.f, 32.f},
            NkColor2D{70, 130, 220, 255}
        );

        renderer.DrawRect(
            NkRect2f{760.f, 18.f, 80.f, 32.f},
            NkColor2D{70, 180, 100, 255}
        );

        // Capture de la version avec ResetView
        if (temps >= 3.f && !captureAvec) {
            target.Capture(
                "C:\\Users\\GAMING\\Desktop\\ani-2053\\chapitre-04\\exo10-l_interface_qui_ne_defile_pas\\avec.png"
            );
            captureAvec = true;
        }

        target.Display();
    }
};

int nkmain(const NkEntryState &state) {
    return NkCanvasApp::Run<InterfaceApp>(state);
}
