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
    cfg.title = "Le glisser qui sort";
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

    bool draggingWithoutCapture = false;
    bool draggingWithCapture = false;

    float noCaptureX = 180.0f;
    float noCaptureY = 250.0f;

    float captureX = 670.0f;
    float captureY = 250.0f;

    const float boxWidth = 180.0f;
    const float boxHeight = 100.0f;

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

            // -----------------------------------------------------
            // CLIC GAUCHE
            // -----------------------------------------------------

            else if (auto* mousePress =
                         ev->As<NkMouseButtonPressEvent>()) {

                if (mousePress->GetButton() ==
                    NkMouseButton::NK_MB_LEFT) {

                    float x = (float)mousePress->GetX();
                    float y = (float)mousePress->GetY();

                    // Carré de gauche : SANS CAPTURE
                    if (x >= noCaptureX &&
                        x <= noCaptureX + boxWidth &&
                        y >= noCaptureY &&
                        y <= noCaptureY + boxHeight) {

                        draggingWithoutCapture = true;
                    }

                    // Carré de droite : AVEC CAPTURE
                    else if (x >= captureX &&
                             x <= captureX + boxWidth &&
                             y >= captureY &&
                             y <= captureY + boxHeight) {

                        draggingWithCapture = true;

                        window.CaptureMouse(true);
                    }
                }
            }

            // -----------------------------------------------------
            // MOUVEMENT DE LA SOURIS
            // -----------------------------------------------------

            else if (auto* mouseMove =
                         ev->As<NkMouseMoveEvent>()) {

                float x = (float)mouseMove->GetX();
                float y = (float)mouseMove->GetY();

                // Sans capture
                if (draggingWithoutCapture &&
                    mouseMove->IsButtonDown(
                        NkMouseButton::NK_MB_LEFT)) {

                    noCaptureX = x - boxWidth / 2.0f;
                    noCaptureY = y - boxHeight / 2.0f;
                }

                // Avec capture
                if (draggingWithCapture &&
                    mouseMove->IsButtonDown(
                        NkMouseButton::NK_MB_LEFT)) {

                    captureX = x - boxWidth / 2.0f;
                    captureY = y - boxHeight / 2.0f;
                }
            }

            // -----------------------------------------------------
            // RELACHEMENT DU BOUTON
            // -----------------------------------------------------

            else if (auto* mouseRelease =
                         ev->As<NkMouseButtonReleaseEvent>()) {

                if (mouseRelease->GetButton() ==
                    NkMouseButton::NK_MB_LEFT) {

                    draggingWithoutCapture = false;

                    if (draggingWithCapture) {
                        draggingWithCapture = false;
                        window.CaptureMouse(false);
                    }
                }
            }

            // -----------------------------------------------------
            // FIN DE CAPTURE
            // -----------------------------------------------------

            else if (ev->As<NkMouseCaptureEndEvent>()) {
                draggingWithCapture = false;
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

        // Zone sans capture
        r2d->FillRect(
            {100.f, 150.f, 350.f, 300.f},
            {0.20f, 0.25f, 0.45f, 1.f}
        );

        r2d->DrawRect(
            {100.f, 150.f, 350.f, 300.f},
            {1.f, 1.f, 1.f, 1.f},
            3.f
        );

        // Zone avec capture
        r2d->FillRect(
            {600.f, 150.f, 350.f, 300.f},
            {0.25f, 0.45f, 0.25f, 1.f}
        );

        r2d->DrawRect(
            {600.f, 150.f, 350.f, 300.f},
            {1.f, 1.f, 1.f, 1.f},
            3.f
        );

        // Objet sans capture
        r2d->FillRect(
            {noCaptureX, noCaptureY, boxWidth, boxHeight},
            {0.85f, 0.30f, 0.30f, 1.f}
        );

        r2d->DrawRect(
            {noCaptureX, noCaptureY, boxWidth, boxHeight},
            {1.f, 1.f, 1.f, 1.f},
            2.f
        );

        // Objet avec capture
        r2d->FillRect(
            {captureX, captureY, boxWidth, boxHeight},
            {0.30f, 0.75f, 0.35f, 1.f}
        );

        r2d->DrawRect(
            {captureX, captureY, boxWidth, boxHeight},
            {1.f, 1.f, 1.f, 1.f},
            2.f
        );

        r2d->End();

        renderer->Present();
        renderer->EndFrame();
    }

    // Fermeture propre
    if (draggingWithCapture) {
        window.CaptureMouse(false);
    }

    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);
    window.Close();

    return 0;
}
