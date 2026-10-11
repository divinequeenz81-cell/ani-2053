#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Groupe {
    string police;
    long long n, w, h;
    long long x1, y1, x2, y2;
};

int main() {
    long long P, L;
    cin >> P >> L;

    int G;
    cin >> G;

    if (G == 0) {
        cout << "AUCUN\n";
        return 0;
    }

    vector<Groupe> groupes(G);
    long long besoin = 0;
    long long occupe = 0;

    for (int i = 0; i < G; i++) {
        cin >> groupes[i].police
            >> groupes[i].n
            >> groupes[i].w
            >> groupes[i].h;

        besoin += groupes[i].n
                * (groupes[i].w + P)
                * (groupes[i].h + P);

        occupe += groupes[i].n
                * groupes[i].w
                * groupes[i].h;
    }

    long long W = (L == 0) ? 512 : L;
    if (L == 0) {
        while (W * W < 2 * besoin && W < 4096) {
            W *= 2;
        }
    }

    long long H = W;

    for (int essai = 1; essai <= 8; essai++) {
        long long x = P;
        long long y = P;
        long long e = 0;
        bool succes = true;

        for (int i = 0; i < G && succes; i++) {
            Groupe& g = groupes[i];

            long long rw = g.w + P;
            long long rh = g.h + P;

            for (long long j = 0; j < g.n; j++) {
                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;

                    if (x + rw > W - P) {
                        succes = false;
                        break;
                    }
                }

                if (y + rh > H - P) {
                    succes = false;
                    break;
                }

                if (j == 0) {
                    g.x1 = x;
                    g.y1 = y;
                }

                if (j == g.n - 1) {
                    g.x2 = x;
                    g.y2 = y;
                }

                x += rw;
                e = max(e, rh);
            }
        }

        if (succes) {
            cout << "ESSAIS " << essai << "\n";
            cout << "TEXTURE " << W << " " << H << "\n";

            for (const Groupe& g : groupes) {
                cout << g.police << " "
                     << g.x1 << " " << g.y1 << " "
                     << g.x2 << " " << g.y2 << "\n";
            }

            cout << "OCCUPE " << occupe << "\n";

            long long perdu = (W * H - occupe) * 100 / (W * H);
            cout << "PERDU " << perdu << "\n";

            return 0;
        }

        if (W == H) {
            W *= 2;
        } else {
            H = W;
        }
    }

    cout << "ESSAIS 8\n";
    cout << "ECHEC\n";

    return 0;
}