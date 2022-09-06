#include <iostream>
#include "LDB.hpp"
#include "DSPGen.hpp"
#include <chrono>

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

void SingleSearchStar(int seed, int galaxynumber, int starindex)
{
    UniverseGen g;
    g.CreateGalaxy(seed, galaxynumber, 0);

    printf("%d,%d,%d", seed, galaxynumber, starindex + 1);
    int totalres[13] = { 0 };
    double totalgas[3] = { 0.0 };
    int totalres14 = 0;
    for (StarData star : g.stars)
    {
        if (star.type == EStarType::BlackHole || star.type == EStarType::NeutronStar)
        {

            int res[15] = { 0 };
            g.MyGenerateVeins(star, star.planets[0], res);
            totalres14 += res[14];
        }
    }
    printf(",%d", totalres14);

    int birthflag = 0;
    for (PlanetData planet : g.stars[0].planets)
    {
        if (planet.theme == 4 || planet.theme == 5)
            birthflag |= 1;
        if (planet.type == EPlanetType::Gas)
            continue;
        int res[15] = { 0 };
        g.MyGenerateVeins(g.stars[0], planet, res);
        if (res[8] > 0)
            birthflag |= 1;
        if ((planet.singularity & EPlanetSingularity::TidalLocked) != EPlanetSingularity::None)
            birthflag |= 2;
    }
    printf(",%d,%d", birthflag & 1, (birthflag & 2)>>1);

    StarData& star = g.stars[starindex];
    double distanc = (float)(star.uPosition - g.stars[0].uPosition).magnitude() / 2400000.0f;
    printf(",%f", distanc);

    for (PlanetData planet : star.planets)
    {
        if (planet.type == EPlanetType::Gas)
        {
            for (int i = 0; i < planet.gasItems.size(); i++)
            {
                if(planet.gasItems[i] == 1120)
                    totalgas[0] += planet.gasSpeeds[i];
                else if (planet.gasItems[i] == 1121)
                    totalgas[1] += planet.gasSpeeds[i];
                else if (planet.gasItems[i] == 1011)
                    totalgas[2] += planet.gasSpeeds[i];
            }
        }
        else
        {
            int res[15] = { 0 };
            g.MyGenerateVeins(star, planet, res);
            for (int i = 1; i < 14; i++)
                totalres[i - 1] += res[i];
        }
    }

    for (int i = 0; i < 13; i++)
        printf(",%d", totalres[i]);
    for (int i = 0; i < 3; i++)
        printf(",%.2f", totalgas[i]);
    printf("\n");
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
			SingleSearchStar(seed, galaxynumber, star.index);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
        return 1;
    int start = atol(argv[1]);
    int end = atol(argv[2]);
	int starnumber  = atol(argv[3]);
    for(int i=start; i<end;i++)
        SingleSearchFast(i, starnumber);


	/*
	auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<8192;i++)
        SingleSearchFast(i, 64);
	auto end = std::chrono::high_resolution_clock::now();
	printf("%ld ms\n", std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count());
	*/
    //SingleSearch(29832478, 64);
    return 0;
}

