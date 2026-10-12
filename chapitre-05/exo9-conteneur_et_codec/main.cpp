#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Piste {
    string type;
    string code;
};

int hexValeur(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

vector<int> decoderHex(const string& s) {
    vector<int> octets;
    if (s == "-") return octets;

    for (size_t i = 0; i + 1 < s.size(); i += 2) {
        octets.push_back(hexValeur(s[i]) * 16 + hexValeur(s[i + 1]));
    }
    return octets;
}

bool correspond(const vector<int>& b, int pos, const string& texte) {
    if (pos < 0 || b.size() < static_cast<size_t>(pos) + texte.size()) {
        return false;
    }

    for (size_t i = 0; i < texte.size(); i++) {
        if (b[pos + i] != static_cast<unsigned char>(texte[i])) {
            return false;
        }
    }
    return true;
}

string conteneur(const vector<int>& b) {
    if (b.size() >= 12 && correspond(b, 4, "ftyp")) return "MP4";
    if (b.size() >= 4 && b[0] == 0x1A && b[1] == 0x45 &&
        b[2] == 0xDF && b[3] == 0xA3) return "WEBM";
    if (b.size() >= 12 && correspond(b, 0, "RIFF") &&
        correspond(b, 8, "WAVE")) return "WAV";
    if (b.size() >= 4 && correspond(b, 0, "OggS")) return "OGG";
    if (b.size() >= 4 && correspond(b, 0, "fLaC")) return "FLAC";
    if (b.size() >= 3 && correspond(b, 0, "ID3")) return "MP3";
    if (b.size() >= 2 && b[0] == 0xFF && b[1] >= 0xE0) return "MP3";
    return "INCONNU";
}

string nomCodec(const string& code) {
    if (code == "mp4a") return "aac";
    if (code == "Opus" || code == "opus") return "opus";
    if (code == "avc1" || code == "avc3") return "h264";
    if (code == "hvc1" || code == "hev1") return "h265";
    if (code == "vp08") return "vp8";
    if (code == "vp09") return "vp9";
    if (code == "mp4v") return "mpeg4";
    if (code == ".mp3") return "mp3";
    if (code == "twos" || code == "sowt" || code == "lpcm") return "pcm";
    return code;
}

bool codecLisible(const string& code) {
    return code == "mjpa" || code == "jpeg" || code == "MJPG" ||
           code == "avc1" || code == "avc3" || code == "hvc1" ||
           code == "hev1" || code == "av01";
}

int main() {
    int N;
    cin >> N;

    int totalMP4 = 0;
    int totalLisibles = 0;
    int totalInconnus = 0;

    for (int i = 0; i < N; i++) {
        string nom, hex;
        int P;
        cin >> nom >> hex >> P;

        vector<int> octets = decoderHex(hex);
        vector<Piste> pistes(P);

        for (int j = 0; j < P; j++) {
            cin >> pistes[j].type >> pistes[j].code;
        }

        string cont = conteneur(octets);
        cout << nom << " " << cont << "\n";

        if (cont == "MP4") {
            totalMP4++;

            for (int j = 0; j < P; j++) {
                string typePiste = pistes[j].type == "vide" ? "VIDEO" : "AUDIO";
                cout << nom << " PISTE " << j + 1 << " "
                     << typePiste << " " << nomCodec(pistes[j].code) << "\n";
            }

            string verdict = "SANS_IMAGE";
            for (int j = 0; j < P; j++) {
                if (pistes[j].type == "vide") {
                    verdict = codecLisible(pistes[j].code) ? "LISIBLE" : "ECHEC";
                    break;
                }
            }

            cout << nom << " LECTEUR " << verdict << "\n";
            if (verdict == "LISIBLE") totalLisibles++;
        }

        if (cont == "INCONNU") totalInconnus++;
    }

    cout << "MP4 " << totalMP4 << "\n";
    cout << "LISIBLES " << totalLisibles << "\n";
    cout << "INCONNUS " << totalInconnus << "\n";

    return 0;
}
