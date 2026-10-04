#include "NKWindow/NKMain.h"

class FenetreNue : public NkCanvasApp
{
public:
    FenetreNue()
    {
        SetTitle("Fenetre nue");
        SetSize({800, 600});
        SetBackgroundColor({18, 18, 24});
    }
};

int nkmain()
{
    return NkCanvasApp::Run<FenetreNue>();
}