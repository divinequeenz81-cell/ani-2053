#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

string enMinuscules(string texte) {
    transform(texte.begin(), texte.end(), texte.begin(),
              [](unsigned char c) {
                  return static_cast<char>(tolower(c));
              });
    return texte;
}

vector<unsigned char> decoderHex(const string& hex) {
    vector<unsigned char> octets;

    if (hex == "-") {
        return octets;
    }

    for (size_t i = 0; i + 1 < hex.size(); i += 2) {
        unsigned int valeur = stoul(hex.substr(i, 2), nullptr, 16);
        octets.push_back(static_cast<unsigned char>(valeur));
    }

    return octets;
}

bool correspond(const vector<unsigned char>& b,
                initializer_list<unsigned int> signature) {
    if (b.size() < signature.size()) {
        return false;
    }

    size_t i = 0;

    for (unsigned int valeur : signature) {
        if (b[i] != valeur) {
            return false;
        }
        ++i;
    }

    return true;
}

string reconnaitreFormat(long long taille,
                         const vector<unsigned char>& b) {
    if (taille < 4) {
        return "";
    }

    if (taille >= 8 &&
        correspond(b, {0x89, 0x50, 0x4E, 0x47})) {
        return "PNG";
    }

    if (correspond(b, {0xFF, 0xD8, 0xFF})) {
        return "JPEG";
    }

    if (correspond(b, {0x42, 0x4D})) {
        return "BMP";
    }

    if (correspond(b, {0x71, 0x6F, 0x69, 0x66})) {
        return "QOI";
    }

    if (correspond(b, {0x47, 0x49, 0x46, 0x38})) {
        return "GIF";
    }

    if (b.size() >= 4 &&
        b[0] == 0x00 &&
        b[1] == 0x00 &&
        (b[2] == 0x01 || b[2] == 0x02) &&
        b[3] == 0x00) {
        return "ICO";
    }

    if (taille >= 10 && correspond(b, {0x23, 0x3F})) {
        return "HDR";
    }

    if (correspond(b, {0x76, 0x2F, 0x31, 0x01})) {
        return "EXR";
    }

    if (b.size() >= 2 &&
        b[0] == 0x50 &&
        b[1] >= 0x31 &&
        b[1] <= 0x36) {
        switch (b[1]) {
            case 0x31:
            case 0x34:
                return "PBM";
            case 0x32:
            case 0x35:
                return "PGM";
            case 0x33:
            case 0x36:
                return "PPM";
        }
    }

    if (taille >= 18 &&
        b.size() >= 3 &&
        (b[2] == 0x00 ||
         b[2] == 0x01 ||
         b[2] == 0x02 ||
         b[2] == 0x03 ||
         b[2] == 0x09 ||
         b[2] == 0x0A ||
         b[2] == 0x0B)) {
        return "TGA";
    }

    size_t debut = 0;

    if (correspond(b, {0xEF, 0xBB, 0xBF})) {
        debut = 3;
    }

    while (debut < b.size() &&
           (b[debut] == 0x20 ||
            b[debut] == 0x09 ||
            b[debut] == 0x0A ||
            b[debut] == 0x0D)) {
        ++debut;
    }

    vector<unsigned char> reste;

    if (debut < b.size()) {
        reste.assign(b.begin() + debut, b.end());
    }

    if (correspond(reste, {0x3C, 0x3F, 0x78, 0x6D, 0x6C}) ||
        correspond(reste, {0x3C, 0x73, 0x76, 0x67})) {
        return "SVG";
    }

    return "";
}

string extraireExtension(const string& nom) {
    size_t point = nom.find_last_of('.');

    if (point == string::npos) {
        return "";
    }

    return enMinuscules(nom.substr(point + 1));
}

bool extensionCorrecte(const string& format,
                       const string& extension) {
    static const map<string, set<string>> extensions = {
        {"PNG", {"png"}},
        {"JPEG", {"jpg", "jpeg"}},
        {"BMP", {"bmp"}},
        {"QOI", {"qoi"}},
        {"GIF", {"gif"}},
        {"ICO", {"ico", "cur"}},
        {"HDR", {"hdr"}},
        {"EXR", {"exr"}},
        {"PBM", {"pbm"}},
        {"PGM", {"pgm"}},
        {"PPM", {"ppm"}},
        {"TGA", {"tga"}},
        {"SVG", {"svg"}}
    };

    auto it = extensions.find(format);

    if (it == extensions.end()) {
        return false;
    }

    return it->second.count(extension) > 0;
}

int main() {
    int N;

    if (!(cin >> N)) {
        return 0;
    }

    int lus = 0;
    int mensonges = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i) {
        string nom;
        long long taille;
        string hex;

        cin >> nom >> taille >> hex;

        vector<unsigned char> octets = decoderHex(hex);
        string format = reconnaitreFormat(taille, octets);

        if (format.empty()) {
            cout << nom << " REFUSE\n";
            ++refuses;
        } else {
            ++lus;

            string extension = extraireExtension(nom);

            if (extensionCorrecte(format, extension)) {
                cout << nom << " " << format << " OK\n";
            } else {
                cout << nom << " " << format << " MENT\n";
                ++mensonges;
            }
        }
    }

    cout << "LUS " << lus << '\n';
    cout << "MENSONGES " << mensonges << '\n';
    cout << "REFUSES " << refuses << '\n';

    return 0;
}