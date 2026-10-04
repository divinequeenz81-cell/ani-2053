#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    int points = 0;
    int segments = 0;
    int triangles = 0;
    int refuses = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string type;
        int sommets;

        std::cin >> type >> sommets;

        if (type == "POINTS")
        {
            std::cout << type << " " << sommets << " " << sommets
                      << " POINTS " << 0 << "\n";
            points += sommets;
        }
        else if (type == "LINES")
        {
            int nombre = sommets / 2;
            int restants = sommets % 2;

            std::cout << type << " " << sommets << " " << nombre
                      << " SEGMENTS " << restants << "\n";
            segments += nombre;
        }
        else if (type == "LINE_STRIP")
        {
            int nombre = (sommets >= 2) ? sommets - 1 : 0;
            int restants = (sommets >= 2) ? 0 : sommets;

            std::cout << type << " " << sommets << " " << nombre
                      << " SEGMENTS " << restants << "\n";
            segments += nombre;
        }
        else if (type == "TRIANGLES")
        {
            int nombre = sommets / 3;
            int restants = sommets % 3;

            std::cout << type << " " << sommets << " " << nombre
                      << " TRIANGLES " << restants << "\n";
            triangles += nombre;
        }
        else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN")
        {
            int nombre = (sommets >= 3) ? sommets - 2 : 0;
            int restants = (sommets >= 3) ? 0 : sommets;

            std::cout << type << " " << sommets << " " << nombre
                      << " TRIANGLES " << restants << "\n";
            triangles += nombre;
        }
        else
        {
            std::cout << type << " " << sommets << " REFUSE\n";
            ++refuses;
        }
    }

    std::cout << "POINTS " << points << "\n";
    std::cout << "SEGMENTS " << segments << "\n";
    std::cout << "TRIANGLES " << triangles << "\n";
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}
