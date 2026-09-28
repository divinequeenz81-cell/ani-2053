#include <NKWindow/Core/NkMain.h>
#include <NKWindow/Core/NkWindow.h>
#include <NKWindow/Core/NkWindowConfig.h>

#include <NKEvent/NkEventDispatcher.h>
#include <NKEvent/NkWindowEvent.h>
#include <NKEvent/NkKeyboardEvent.h>
#include <NKEvent/NkMouseEvent.h>

#include <NKRHI/Core/NkDeviceFactory.h>
#include <NKRenderer/NkRenderer.h>
#include <NKRenderer/Tools/Render2D/NkRender2D.h>
#include <NKRHI/Commands/NkICommandBuffer.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState& state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "Les sept curseurs";
    cfg.width = 1050;
    cfg.height = 600;
    cfg.centered = true;
    cfg.resizable = true;
    cfg.vsync = true;

    NkWindow window(cfg);

    if (!window.IsValid()) {
        return -1;
    }

    NkDeviceInitInfo devInit{};
    devInit.surface = window.GetSurfaceDesc();
    devInit.width = window.GetSize().x;
    devInit.height = window.GetSize().y;

    NkIDevice* device = NkDeviceFactory::CreateAutoDetect(devInit);

    if (!device) {
        return -1;
    }

    NkRendererConfig rendererConfig =
        NkRendererConfig::ForGame(
            devInit.api,
            devInit.width,
            devInit.height
        );

    NkRenderer* renderer =
        NkRenderer::Create(device, rendererConfig);

    if (!renderer || !renderer->Initialize()) {
        NkDeviceFactory::Destroy(device);
        return -1;
    }

    NkRender2D* r2d = renderer->GetRender2D();

    bool running = true;

    while (running && window.IsOpen()) {

        // ---------------------------------------------------------
        // EVENEMENTS
        // ---------------------------------------------------------
        NkEvent* ev;

        while (NkEvents().PollEvent(ev)) {

            if (auto* closeEvent = ev->As<NkWindowCloseEvent>()) {
                (void)closeEvent;
                running = false;
            }

            else if (auto* keyEvent = ev->As<NkKeyPressEvent>()) {
                if (keyEvent->GetKey() == NkKey::NK_ESCAPE) {
                    running = false;
                }
            }

            // Changement du curseur uniquement lorsqu'un mouvement
            // de souris est reçu.
            else if (auto* mouseEvent = ev->As<NkMouseMoveEvent>()) {

                float x = (float)mouseEvent->GetX();
                float y = (float)mouseEvent->GetY();

                float zoneWidth =
    (float)window.GetSize().x / 7.0f;

int zone = -1;

if (y >= 100.0f && y <= 450.0f) {
    zone = (int)(x / zoneWidth);
}

if (zone < 0 || zone > 6) {
    window.SetCursor(
        NkWindow::NkCursorType::Arrow
    );
}
else {
                switch (zone) {

                    case 0:
                        window.SetCursor(
                            NkWindow::NkCursorType::Arrow
                        );
                        break;

                    case 1:
                        window.SetCursor(
                            NkWindow::NkCursorType::TextInput
                        );
                        break;

                    case 2:
                        window.SetCursor(
                            NkWindow::NkCursorType::Hand
                        );
                        break;

                    case 3:
                        window.SetCursor(
                            NkWindow::NkCursorType::ResizeNS
                        );
                        break;

                    case 4:
                        window.SetCursor(
                            NkWindow::NkCursorType::ResizeWE
                        );
                        break;

                    case 5:
                        window.SetCursor(
                            NkWindow::NkCursorType::ResizeNWSE
                        );
                        break;

                    case 6:
                        window.SetCursor(
                            NkWindow::NkCursorType::ResizeNESW
                        );
                        break;
                }
            }
        }

        if (!running) {
            break;
        }

        // ---------------------------------------------------------
        // RENDU
        // ---------------------------------------------------------
        if (!renderer->BeginFrame()) {
            continue;
        }

        uint32 screenW = renderer->GetWidth();
        uint32 screenH = renderer->GetHeight();

        NkICommandBuffer* cmd = renderer->GetCmd();

        r2d->Begin(cmd, screenW, screenH);

        // Fond
        r2d->FillRect(
            {0.f, 0.f, (float)screenW, (float)screenH},
            {0.08f, 0.08f, 0.10f, 1.f}
        );

        float zoneWidth = (float)screenW / 7.0f;

        // Les sept zones
        for (int i = 0; i < 7; ++i) {

            float x = i * zoneWidth;

            r2d->FillRect(
                {x + 5.f, 100.f, zoneWidth - 10.f, 350.f},
                {0.15f + i * 0.04f,
                 0.25f + i * 0.03f,
                 0.45f + i * 0.02f,
                 1.f}
            );

            r2d->DrawRect(
                {x + 5.f, 100.f, zoneWidth - 10.f, 350.f},
                {1.f, 1.f, 1.f, 1.f},
                2.f
            );
        }

        r2d->End();

        renderer->Present();
        renderer->EndFrame();
    }

    // Fermeture propre
    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);
    window.Close();

    return 0;
}