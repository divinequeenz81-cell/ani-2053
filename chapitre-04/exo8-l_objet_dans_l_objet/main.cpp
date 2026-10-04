#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Objet {
    string nom;
    string parent;

    long long tx;
    long long ty;
    int angle;
    long long echelle;

    long long x;
    long long y;
    int angleMonde;
    long long echelleMonde;
    int profondeur;
};

int normaliserAngle(int angle) {
    angle %= 360;

    if (angle < 0) {
        angle += 360;
    }

    return angle;
}

int main() {
    int N;
    cin >> N;

    vector<Objet> objets;

    int profondeurMax = 0;

    for (int i = 0; i < N; ++i) {
        Objet objet;

        cin >> objet.nom
            >> objet.parent
            >> objet.tx
            >> objet.ty
            >> objet.angle
            >> objet.echelle;

        if (objet.parent == "-") {
            // Objet racine
            objet.x = objet.tx;
            objet.y = objet.ty;

            objet.angleMonde = normaliserAngle(objet.angle);
            objet.echelleMonde = objet.echelle;

            objet.profondeur = 1;
        }
        else {
            // Chercher le parent
            int indiceParent = -1;

            for (int j = 0; j < static_cast<int>(objets.size()); ++j) {
                if (objets[j].nom == objet.parent) {
                    indiceParent = j;
                    break;
                }
            }

            const Objet& parent = objets[indiceParent];

            // 1. Mise à l'échelle de la position locale
            long long ax = objet.tx * parent.echelleMonde;
            long long ay = objet.ty * parent.echelleMonde;

            // 2. Rotation selon l'angle MONDE du parent
            long long rx;
            long long ry;

            switch (parent.angleMonde) {
                case 0:
                    rx = ax;
                    ry = ay;
                    break;

                case 90:
                    rx = -ay;
                    ry = ax;
                    break;

                case 180:
                    rx = -ax;
                    ry = -ay;
                    break;

                case 270:
                    rx = ay;
                    ry = -ax;
                    break;

                default:
                    rx = ax;
                    ry = ay;
                    break;
            }

            // 3. Ajouter la position monde du parent
            objet.x = parent.x + rx;
            objet.y = parent.y + ry;

            // 4. Composer les angles
            objet.angleMonde =
                normaliserAngle(parent.angleMonde + objet.angle);

            // 5. Composer les échelles
            objet.echelleMonde =
                parent.echelleMonde * objet.echelle;

            // 6. Calculer la profondeur
            objet.profondeur = parent.profondeur + 1;
        }

        // Mettre à jour la profondeur maximale
        if (objet.profondeur > profondeurMax) {
            profondeurMax = objet.profondeur;
        }

        // Affichage immédiat dans l'ordre d'entrée
        cout << objet.nom << " "
             << objet.x << " "
             << objet.y << " "
             << objet.angleMonde << " "
             << objet.echelleMonde << "\n";

        // Ajouter l'objet pour qu'il puisse être parent
        objets.push_back(objet);
    }

    cout << "PROFONDEUR " << profondeurMax << "\n";

    return 0;
}