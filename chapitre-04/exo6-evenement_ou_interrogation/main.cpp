#include <iostream>
#include <string>

using namespace std;

int main() {
    int v, N;
    cin >> v >> N;

    int xe = 0;
    int xi = 0;

    bool space = false;
    bool left = false;
    bool right = false;

    int sautsEvenements = 0;
    int sautsInterrogation = 0;
    int manques = 0;

    for (int i = 1; i <= N; ++i) {
        int k;
        cin >> k;

        int sautsEspaceImage = 0;

        for (int j = 0; j < k; ++j) {
            string evenement;
            cin >> evenement;

            if (evenement.size() < 2) {
                continue;
            }

            char action = evenement[0];
            string nom = evenement.substr(1);

            if (nom == "SPACE") {
                if (action == '+') {
                    space = true;
                    ++sautsEvenements;
                    ++sautsEspaceImage;
                } else if (action == '-') {
                    space = false;
                }
            } else if (nom == "RIGHT") {
                if (action == '+') {
                    right = true;
                    xe += v;
                } else if (action == '-') {
                    right = false;
                }
            } else if (nom == "LEFT") {
                if (action == '+') {
                    left = true;
                    xe -= v;
                } else if (action == '-') {
                    left = false;
                }
            }
        }

        if (!space) {
            manques += sautsEspaceImage;
        }

        if (space) {
            ++sautsInterrogation;
        }

        if (right) {
            xi += v;
        }

        if (left) {
            xi -= v;
        }

        cout << i << " " << xe << " " << xi << "\n";
    }

    cout << "SAUTS EVENEMENTS " << sautsEvenements << "\n";
    cout << "SAUTS INTERROGATION " << sautsInterrogation << "\n";
    cout << "MANQUES " << manques << "\n";

    return 0;
}