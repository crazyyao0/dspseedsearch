#include <iostream>
#include "LDB.hpp"
#include "DSPGen.hpp"

void SingleSearch(int seed, int galaxynumber)
{
    UniverseGen g;
    g.CreateGalaxy(seed, galaxynumber, 0);
    printf("Galaxynumber seed: %d, Star count: %d\n", seed, galaxynumber);
    for (StarData star : g.stars)
    {
        int totalres[14] = { 0 };
        float distanc = (float)(star.uPosition - g.stars[0].uPosition).magnitude() / 2400000.0f;
        printf("  %s %s, Distance: %.2f LY, DysonLumino:%.2f, DysonRadius: %.2f, Starseed: %d\n", star.typeString().c_str(), star.name.c_str(), distanc, star.dysonLumino(), star.dysonRadius, star.seed);
        for (PlanetData planet : star.planets)
        {
            printf("    %d|%d|%s|%s", planet.id, planet.seed, LDB.Select(planet.theme).DisplayName.c_str(), planet.GetPlanetSingularityString().c_str());
            printf(", 亮度(%g), 风力(%g)", planet.luminosity, planet.windStrength);
            if (planet.waterItemId == 1000)
                printf(", 水");
            else if (planet.waterItemId == 1116)
                printf(", 硫酸");
            if (planet.gasItems.size())
            {
                for (int j = 0; j < 2; j++)
                {
                    if (planet.gasItems[j] == 1120)
                        printf(", 氢 %.2f/s", planet.gasSpeeds[j]);
                    else if (planet.gasItems[j] == 1121)
                        printf(", 重氢 %.2f/s", planet.gasSpeeds[j]);
                    else if (planet.gasItems[j] == 1011)
                        printf(", 可燃冰 %.2f/s", planet.gasSpeeds[j]);
                }
            }
            else
            {
                int res[15] = { 0 };
                g.MyGenerateVeins(star, planet, res);
                for (int i = 1; i < 15; i++)
                {
                    totalres[i - 1] += res[i];
                    printf(", %d", res[i]);
                }
            }
            printf("\n");
        }
        printf("    Total");
        for (int i = 0; i < 14; i++)
            printf(", %d", totalres[i]);
        printf("\n");
    }
}

void SingleSearchFast(int seed, int galaxynumber)
{
    UniverseGen g;
    g.CreateGalaxy(seed, galaxynumber, 1);
    for (StarData star : g.stars)
    {
        int flag;
        if (star.index == 0)
            continue;
        if (star.spectr != ESpectrType::O)
            continue;
        if ((star.planets[0].singularity & EPlanetSingularity::TidalLocked) == 0)
            continue;
        float distanc = (float)(star.uPosition - g.stars[0].uPosition).magnitude() / 2400000.0f;
        if (distanc > 5.0f)
            continue;

        flag = 0;
        for (PlanetData planet : star.planets)
            flag |= themeres[planet.theme];
        if ((flag & 0x7bffe) != 0x7bffe)
            continue;

        flag = 0;
        for (PlanetData planet : star.planets)
        {
            if (planet.type == EPlanetType::Gas)
                continue;
            int res[15] = { 0 };
            g.MyGenerateVeins(star, planet, res);
            for (int i = 1; i < 14; i++)
                if (res[i])
                    flag |= 1 << i;
        }
        if ((flag & 0x3ffe) == 0x3ffe)
            printf("%d,%d,%d\n", seed, galaxynumber, star.index);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
        return 1;
    int start = atol(argv[1]);
    int end = atol(argv[2]);

    for(int i=start; i<end;i++)
        SingleSearchFast(i, 64);
    //SingleSearchFast(66812129, 64);
    return 0;
}

