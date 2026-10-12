#include <cstdio>
#include <fstream>
#include "NKMedia/Video/NkVideoReader.h"
#include "NKMedia/NkMediaProbe.h"

using namespace nkentseu;
using namespace nkentseu::media;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Utilisation : lecteur.exe video.avi video_tronquee.avi faux.mp4\n");
        return 1;
    }

    std::ofstream resultats("resultats.txt");
    if (!resultats) {
        printf("Erreur : impossible de creer resultats.txt\n");
        return 1;
    }

    for (int i = 1; i < 4; ++i) {
        const char* chemin = argv[i];
        NkVideoReader lecteur;
        int images = 0;

        bool ouvert = lecteur.Open(chemin);

        printf("\nFichier : %s\n", chemin);
        printf("Ouvert : %s\n", ouvert ? "oui" : "non");

        if (ouvert) {
            const NkVideoReaderInfo& info = lecteur.Info();

            printf("Conteneur : %s\n", info.container.CStr());
            printf("Codec : %s\n", info.codec.CStr());
            printf("Dimensions : %d x %d\n", info.width, info.height);

            NkVideoFrame image;
            while (lecteur.ReadFrame(image)) {
                ++images;
            }

            printf("Images lues : %d\n", images);
        }

        NkMediaInfo mediaInfo;
        bool sondeOK = NkMediaProbe::ProbeFile(chemin, mediaInfo);

        if (sondeOK) {
            printf("Sonde : %s\n", mediaInfo.ContainerName());

            for (uint64 j = 0; j < mediaInfo.tracks.Size(); ++j) {
                const NkMediaTrack& piste = mediaInfo.tracks[j];
                printf("Piste : codec=%s, dimensions=%d x %d\n",
                       piste.codec.CStr(), piste.width, piste.height);
            }
        } else {
            printf("Sonde : format non reconnu\n");
        }

        resultats << "fichier : " << chemin
                  << ", ouvert : " << (ouvert ? "oui" : "non")
                  << ", images : " << images
                  << ", sonde : "
                  << (sondeOK ? mediaInfo.ContainerName() : "inconnue")
                  << '\n';
    }

    resultats.close();
    printf("\nResultats enregistres dans resultats.txt\n");
    return 0;
}