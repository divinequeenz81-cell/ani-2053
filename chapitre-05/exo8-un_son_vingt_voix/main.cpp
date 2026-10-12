#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long D, C;
    int N;

    cin >> D >> C;
    cin >> N;

    vector<long long> temps(N);

    for (int i = 0; i < N; i++) {
        cin >> temps[i];
    }

    long long finChargement = 0;
    int voixMax = 0;
    long long retardMax = 0;
    int coupes = 0;

    for (int i = 0; i < N; i++) {
        int voix = 0;

        for (int j = 0; j < N; j++) {
            if (temps[j] <= temps[i] &&
                temps[j] + D > temps[i]) {
                voix++;
            }
        }

        voixMax = max(voixMax, voix);

        long long debutChargement = max(temps[i], finChargement);
        finChargement = debutChargement + C;

        long long retard = finChargement - temps[i];
        retardMax = max(retardMax, retard);

        bool coupe = false;

        if (i + 1 < N && temps[i + 1] < temps[i] + D) {
            coupe = true;
            coupes++;
        }

        cout << temps[i] << " " << voix << " "
             << retard << " "
             << (coupe ? "COUPE" : "ENTIER") << "\n";
    }

    cout << "VOIX_MAX " << voixMax << "\n";
    cout << "RETARD_MAX " << retardMax << "\n";
    cout << "COUPES " << coupes << "\n";

    return 0;
}
