#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Glyphe {
    long long avance, x0, y0, x1, y1;
};

int main() {
    int G;
    cin >> G;

    map<char, Glyphe> glyphes;

    for (int i = 0; i < G; i++) {
        char c;
        Glyphe g;
        cin >> c >> g.avance >> g.x0 >> g.y0 >> g.x1 >> g.y1;
        if (c == '_') c = ' ';
        glyphes[c] = g;
    }

    int K;
    cin >> K;

    map<string, long long> crenages;

    for (int i = 0; i < K; i++) {
        string couple;
        long long k;
        cin >> couple >> k;

        for (char& c : couple) {
            if (c == '_') c = ' ';
        }

        crenages[couple] = k;
    }

    string texte;
    long long ox, oy;
    cin >> texte >> ox >> oy;

    for (char& c : texte) {
        if (c == '_') c = ' ';
    }

    long long x = ox;
    long long minx = 0, miny = 0, maxx = 0, maxy = 0;
    bool boiteExiste = false;
    int absents = 0;

    for (size_t i = 0; i < texte.size(); i++) {
        char c = texte[i];
        auto it = glyphes.find(c);

        if (it == glyphes.end()) {
            cout << c << " ABSENT\n";
            absents++;
            continue;
        }

        const Glyphe& g = it->second;
        cout << (c == ' ' ? '_' : c) << " " << x << "\n";

        if (g.x1 > g.x0 && g.y1 > g.y0) {
            long long gx0 = x + g.x0;
            long long gy0 = oy + g.y0;
            long long gx1 = x + g.x1;
            long long gy1 = oy + g.y1;

            if (!boiteExiste) {
                minx = gx0;
                miny = gy0;
                maxx = gx1;
                maxy = gy1;
                boiteExiste = true;
            } else {
                minx = min(minx, gx0);
                miny = min(miny, gy0);
                maxx = max(maxx, gx1);
                maxy = max(maxy, gy1);
            }
        }

        x += g.avance;

        if (i + 1 < texte.size()) {
            string couple;
            couple += c;
            couple += texte[i + 1];

            auto cr = crenages.find(couple);
            if (cr != crenages.end()) {
                glyphes[c].avance += 0;
                x += cr->second;
            }
        }
    }

    cout << "CURSEUR " << x << "\n";

    if (!boiteExiste) {
        cout << "BOITE AUCUNE\n";
        cout << "MONTE 0\n";
        cout << "DESCEND 0\n";
        cout << "ECRAN RIEN\n";
    } else {
        cout << "BOITE " << minx << " " << miny << " "
             << maxx << " " << maxy << "\n";

        long long monte = (miny < oy) ? oy - miny : 0;
        long long descend = (maxy > oy) ? maxy - oy : 0;

        cout << "MONTE " << monte << "\n";
        cout << "DESCEND " << descend << "\n";

        if (maxy <= 0) {
            cout << "ECRAN HORS\n";
        } else if (miny < 0) {
            cout << "ECRAN COUPE\n";
        } else {
            cout << "ECRAN VISIBLE\n";
        }
    }

    cout << "ABSENTS " << absents << "\n";

    return 0;
}