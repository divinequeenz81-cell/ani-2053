#include <iostream>
#include <string>
#include <algorithm>

struct Point
{
    long long x;
    long long y;
};

int main()
{
    int n;
    std::cin >> n;

    int refuses = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long w, h, px, py, ox, oy, sx, sy, angle;

        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        int normalise = static_cast<int>((angle % 360 + 360) % 360);

        long long c;
        long long s;

        if (normalise == 0)
        {
            c = 1;
            s = 0;
        }
        else if (normalise == 90)
        {
            c = 0;
            s = 1;
        }
        else if (normalise == 180)
        {
            c = -1;
            s = 0;
        }
        else if (normalise == 270)
        {
            c = 0;
            s = -1;
        }
        else
        {
            std::cout << nom << " ANGLE REFUSE\n";
            ++refuses;
            continue;
        }

        Point coins[4] = {
            {0, 0},
            {w, 0},
            {w, h},
            {0, h}
        };

        Point monde[4];

        for (int j = 0; j < 4; ++j)
        {
            long long ax = (coins[j].x - ox) * sx;
            long long ay = (coins[j].y - oy) * sy;

            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            monde[j] = {px + rx, py + ry};
        }

        long long minx = monde[0].x;
        long long maxx = monde[0].x;
        long long miny = monde[0].y;
        long long maxy = monde[0].y;

        for (int j = 1; j < 4; ++j)
        {
            minx = std::min(minx, monde[j].x);
            maxx = std::max(maxx, monde[j].x);
            miny = std::min(miny, monde[j].y);
            maxy = std::max(maxy, monde[j].y);
        }

        std::cout << nom << " COINS "
                  << monde[0].x << " " << monde[0].y << " "
                  << monde[1].x << " " << monde[1].y << " "
                  << monde[2].x << " " << monde[2].y << " "
                  << monde[3].x << " " << monde[3].y << "\n";

        std::cout << nom << " BOITE "
                  << minx << " " << miny << " "
                  << maxx << " " << maxy << "\n";
    }

    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}
