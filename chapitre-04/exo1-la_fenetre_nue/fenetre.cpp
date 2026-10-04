#include "NKWindow/NKMain.h"

class FenetreNue : public NkCanvasApp
{
public:
    FenetreNue()
    {
        Config().title = "Fenetre nue";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = {18, 18, 24, 255};
    }
};

int nkmain()
{
    return NkCanvasApp::Run<FenetreNue>();
}
