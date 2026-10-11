
#include <iostream>
#include <string>
using namespace std;

struct Format {
    string nom;
    long long octets;
    bool couleur;
    bool transparence;
    bool flottants;
};

Format formats[] = {
    {"GRAY8", 1, false, false, false},
    {"GRAY_A16", 2, false, true, false},
    {"RGB24", 3, true, false, false},
    {"RGBA32", 4, true, true, false},
    {"RGB96F", 12, true, false, true},
    {"RGBA128F", 16, true, true, true}
};

const int NB_FORMATS = 6;

int trouverFormat(const string& nom) {
    for (int i = 0; i < NB_FORMATS; i++) {
        if (formats[i].nom == nom)
            return i;
    }
    return -1;
}

int main() {
    long long w, h;
    int n;

    if (!(cin >> w >> h >> n))
        return 0;

    long long total = 0;
    int sansPerte = 0;
    int refuses = 0;

    for (int i = 0; i < n; i++) {
        string source, cible;
        cin >> source >> cible;

        int s = trouverFormat(source);
        int c = trouverFormat(cible);

        if (s == -1 || c == -1) {
            cout << source << " " << cible << " REFUSE\n";
            refuses++;
            continue;
        }

        long long octetsSource = w * h * formats[s].octets;
        long long octetsCible = w * h * formats[c].octets;

        string pertes = "";

        if (formats[s].transparence && !formats[c].transparence)
            pertes += "TRANSPARENCE";

        if (formats[s].couleur && !formats[c].couleur) {
            if (!pertes.empty()) pertes += "+";
            pertes += "COULEUR";
        }

        if (formats[s].flottants && !formats[c].flottants) {
            if (!pertes.empty()) pertes += "+";
            pertes += "ETENDUE";
        }

        if (pertes.empty()) {
            pertes = "AUCUNE";
            sansPerte++;
        }

        cout << source << " " << cible << " "
             << octetsSource << " " << octetsCible << " "
             << pertes << "\n";

        total += octetsCible;
    }

    cout << "TOTAL " << total << "\n";
    cout << "SANS_PERTE " << sansPerte << "\n";
    cout << "REFUSES " << refuses << "\n";

    return 0;
}

