#include <NKThreading/NkThread.h>

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace nkentseu;
using namespace nkentseu::threading;

constexpr int NB_FILS = 8;
constexpr int NB_INCREMENT = 1000000;

int compteur = 0;

int main(int argc, char* argv[])
{
    int nombreFils = NB_FILS;

    if (argc > 1 && std::atoi(argv[1]) == 1)
        nombreFils = 1;

    compteur = 0;

    std::vector<NkThread> fils;
    fils.reserve(nombreFils);

    for (int i = 0; i < nombreFils; ++i)
    {
        fils.emplace_back([](void*) {
            for (int j = 0; j < NB_INCREMENT; ++j)
                compteur += 1;
        });
    }

    for (auto& fil : fils)
        fil.Join();

    const int totalAttendu = nombreFils * NB_INCREMENT;

    std::cout << "Nombre de fils : " << nombreFils << '\n';
    std::cout << "Total obtenu : " << compteur << '\n';
    std::cout << "Total attendu : " << totalAttendu << '\n';

    return 0;
}
