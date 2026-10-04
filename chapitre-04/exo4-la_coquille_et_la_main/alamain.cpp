#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKTime/NkTime.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState& state)
{
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "La main";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen() || !window.IsValid())
        return -1;

    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    NkRenderWindow target(window, desc);
    if (!target.IsValid())
        return -2;

    NkClock clock;
    float32 x = 100.f;
    const float32 y = 100.f;
    const float32 vitesse = 200.f;

    while (window.IsOpen() && window.IsValid())
    {
        const float32 deltaTime = clock.Tick().delta;
          const float32 avantX = x;
          (void)avantX;

        while (NkEvent* event = NkEvents().PollEvent())
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                window.Close();
                break;
            }
        }

        if (!window.IsOpen())
            break;

        x += vitesse * deltaTime;

        const float32 largeur =
            static_cast<float32>(target.GetSize().x);

        if (x < 0.f || x + 50.f > largeur)
            x -= vitesse * deltaTime * 2.f;

        target.Clear(NkColor2D{18, 18, 24, 255});

        NkRenderer2D& renderer = target.GetRenderer2D();

        renderer.DrawFilledRect(
            NkRect2f{x, y, 50.f, 50.f},
            NkColor2D{255, 0, 0, 255}
        );

        target.Display();
    }

    return 0;
}