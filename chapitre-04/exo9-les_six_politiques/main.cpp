#include <iostream>

using namespace std;

using ll = long long;

struct Resultat {
    ll vx;
    ll vy;
    ll vw;
    ll vh;
    ll mw;
    ll mh;
};

ll arrondir(ll a, ll b) {
    return (2 * a + b) / (2 * b);
}

Resultat fitLetterbox(ll RW, ll RH, ll W, ll H) {
    Resultat r;

    if (W * RH <= H * RW) {
        r.vw = W;
        r.vh = arrondir(RH * W, RW);
    } else {
        r.vh = H;
        r.vw = arrondir(RW * H, RH);
    }

    r.vx = (W - r.vw) / 2;
    r.vy = (H - r.vh) / 2;

    r.mw = RW;
    r.mh = RH;

    return r;
}

int main() {
    ll RW, RH, AW, AH, W, H;

    cin >> RW >> RH >> AW >> AH >> W >> H;

    bool reference = (RW != 0 && RH != 0);

    Resultat followWindow;
    followWindow.vx = 0;
    followWindow.vy = 0;
    followWindow.vw = W;
    followWindow.vh = H;
    followWindow.mw = W;
    followWindow.mh = H;

    Resultat stretch;
    Resultat letterbox;
    Resultat integerScale;
    Resultat fitCrop;
    Resultat manual;

    // STRETCH
    if (!reference) {
        stretch = followWindow;
    } else {
        stretch.vx = 0;
        stretch.vy = 0;
        stretch.vw = W;
        stretch.vh = H;
        stretch.mw = RW;
        stretch.mh = RH;
    }

    // FIT_LETTERBOX
    if (!reference) {
        letterbox = followWindow;
    } else {
        letterbox = fitLetterbox(RW, RH, W, H);
    }

    // INTEGER_SCALE
    if (!reference) {
        integerScale = followWindow;
    } else if (W >= RW && H >= RH) {
        ll kW = W / RW;
        ll kH = H / RH;
        ll k = (kW < kH) ? kW : kH;

        if (k >= 1) {
            integerScale.vw = RW * k;
            integerScale.vh = RH * k;

            integerScale.vx = (W - integerScale.vw) / 2;
            integerScale.vy = (H - integerScale.vh) / 2;

            integerScale.mw = RW;
            integerScale.mh = RH;
        } else {
            integerScale = fitLetterbox(RW, RH, W, H);
        }
    } else {
        integerScale = fitLetterbox(RW, RH, W, H);
    }

    // FIT_CROP
    if (!reference) {
        fitCrop = followWindow;
    } else {
        fitCrop.vx = 0;
        fitCrop.vy = 0;
        fitCrop.vw = W;
        fitCrop.vh = H;

        if (W * RH > H * RW) {
            fitCrop.mw = RW;
            fitCrop.mh = arrondir(RW * H, W);
        } else {
            fitCrop.mw = arrondir(RH * W, H);
            fitCrop.mh = RH;
        }
    }

    // MANUAL
    manual.vx = 0;
    manual.vy = 0;
    manual.vw = AW;
    manual.vh = AH;
    manual.mw = AW;
    manual.mh = AH;

    // Affichage strict
    cout << "FOLLOW_WINDOW "
         << followWindow.vx << " "
         << followWindow.vy << " "
         << followWindow.vw << " "
         << followWindow.vh << " "
         << followWindow.mw << " "
         << followWindow.mh << "\n";

    cout << "STRETCH "
         << stretch.vx << " "
         << stretch.vy << " "
         << stretch.vw << " "
         << stretch.vh << " "
         << stretch.mw << " "
         << stretch.mh << "\n";

    cout << "FIT_LETTERBOX "
         << letterbox.vx << " "
         << letterbox.vy << " "
         << letterbox.vw << " "
         << letterbox.vh << " "
         << letterbox.mw << " "
         << letterbox.mh << "\n";

    cout << "INTEGER_SCALE "
         << integerScale.vx << " "
         << integerScale.vy << " "
         << integerScale.vw << " "
         << integerScale.vh << " "
         << integerScale.mw << " "
         << integerScale.mh << "\n";

    cout << "FIT_CROP "
         << fitCrop.vx << " "
         << fitCrop.vy << " "
         << fitCrop.vw << " "
         << fitCrop.vh << " "
         << fitCrop.mw << " "
         << fitCrop.mh << "\n";

    cout << "MANUAL "
         << manual.vx << " "
         << manual.vy << " "
         << manual.vw << " "
         << manual.vh << " "
         << manual.mw << " "
         << manual.mh << "\n";

    int bandes = 0;

    if (letterbox.vw < W || letterbox.vh < H) {
        ++bandes;
    }

    if (integerScale.vw < W || integerScale.vh < H) {
        ++bandes;
    }

    if (manual.vw < W || manual.vh < H) {
        ++bandes;
    }

    cout << "BANDES " << bandes << "\n";

    bool deformation = false;

    if (reference && W * RH != H * RW) {
        deformation = true;
    }

    cout << "DEFORMATION "
         << (deformation ? "OUI" : "NON") << "\n";

    return 0;
}