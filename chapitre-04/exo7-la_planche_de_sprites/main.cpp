#include <iostream>

using namespace std;

int main() {
    int C, R, W, H, F, D, P;

    cin >> C >> R >> W >> H >> F >> D >> P;

    int N;
    cin >> N;

    int caseActuelle = 0;
    int tempsAccumule = 0;

    int avances = 0;
    int plafonnes = 0;

    for (int i = 0; i < N; ++i) {
        int dt;
        cin >> dt;

        if (dt > P) {
            dt = P;
            ++plafonnes;
        }

        tempsAccumule += dt;

        while (tempsAccumule >= D) {
            tempsAccumule -= D;
            ++caseActuelle;
            ++avances;

            if (caseActuelle >= F) {
                caseActuelle = 0;
            }
        }

        int colonne = caseActuelle % C;
        int ligne = caseActuelle / C;

        int x = colonne * W;
        int y = ligne * H;

        cout << caseActuelle << " "
             << x << " "
             << y << " "
             << W << " "
             << H << "\n";
    }

    cout << "AVANCES " << avances << "\n";
    cout << "PLAFONNES " << plafonnes << "\n";

    return 0;
}