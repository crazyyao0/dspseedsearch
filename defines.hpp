#pragma once
#include <vector>
#include <string>
#include "util.hpp"

enum ESpectrType {
    M = 0,
    K = 1,
    G = 2,
    F = 3,
    A = 4,
    B = 5,
    O = 6,
    X = 7
};
enum EStarType {
    MainSeqStar = 0,
    GiantStar = 1,
    WhiteDwarf = 2,
    NeutronStar = 3,
    BlackHole = 4
};


enum EPlanetSingularity
{
    None = 0,
    TidalLocked = 1,
    TidalLocked2 = 2,
    TidalLocked4 = 4,
    LaySide = 8,
    ClockwiseRotate = 0x10,
    MultipleSatellites = 0x20
};

enum class EPlanetType
{
    None = 0,
    Vocano = 1,
    Ocean = 2,
    Desert = 3,
    Ice = 4,
    Gas = 5
};

enum class EThemeDistribute
{
    Default = 0,
    Birth = 1,
    Interstellar = 2,
    Rare = 3
};

const float orbitRadius[17] = {
  0.0f,
  0.4f,
  0.7f,
  1.0f,
  1.4f,
  1.9f,
  2.5f,
  3.3f,
  4.3f,
  5.5f,
  6.9f,
  8.4f,
  10.0f,
  11.7f,
  13.5f,
  15.4f,
  17.5f
};
const int themeres[] = {
    0x00000000,
    0x000088e6,
    0x00060000,
    0x00060000,
    0x00020001,
    0x00020001,
    0x00000276,
    0x0000057e,
    0x0000a8ee,
    0x0000167e,
    0x0000957e,
    0x0000133e,
    0x0000166e,
    0x0001007e,
    0x0000aae6,
    0x0000a8fe,
    0x0000a0c0,
    0x0000127e,
    0x0000a8ee,
    0x0000167e,
    0x0000137e,
    0x00060000,
    0x000028fe,
    0x00001856,
    0x0000137e,
    0x00002cfe
};

class PlanetData
{
public:
    int seed;
    int infoSeed;
    int id;
    int index;
    int orbitAround;
    int number;
    int orbitIndex;
    std::string name;
    std::string overrideName;
    float orbitRadius = 1.0f;
    float orbitInclination;
    float orbitLongitude;
    double orbitalPeriod = 3600.0;
    float orbitPhase;
    float obliquity;
    double rotationPeriod = 480.0;
    float rotationPhase;
    float radius = 200.0f;
    float scale = 1.0f;
    float sunDistance;
    float habitableBias;
    float temperatureBias;
    float ionHeight;
    float windStrength;
    float luminosity;
    float landPercent;
    double mod_x;
    double mod_y;
    float waterHeight;
    int waterItemId;
    bool levelized;
    int iceFlag;
    EPlanetType type;
    int singularity;
    int theme;
    int algoId;
    int style;
    PlanetData* orbitAroundPlanet = NULL;
    std::vector<int> gasItems;
    std::vector<float> gasSpeeds;

    inline float realRadius() {
        return radius * scale;
    }

    std::string GetPlanetSingularityString()
    {
        std::string singularityString = "";
        if (orbitAround > 0)
            singularityString += "ÎÀÐÇ";
        if ((singularity & EPlanetSingularity::TidalLocked) != EPlanetSingularity::None)
            singularityString += "³±Ï«Ëø¶¨ÓÀÖçÓÀÒ¹";
        if ((singularity & EPlanetSingularity::TidalLocked2) != EPlanetSingularity::None)
            singularityString += "³±Ï«Ëø¶¨1:2";
        if ((singularity & EPlanetSingularity::TidalLocked4) != EPlanetSingularity::None)
            singularityString += "³±Ï«Ëø¶¨1:4";
        if ((singularity & EPlanetSingularity::LaySide) != EPlanetSingularity::None)
            singularityString += "ºáÌÉ×Ô×ª";
        if ((singularity & EPlanetSingularity::ClockwiseRotate) != EPlanetSingularity::None)
            singularityString += "·´Ïò×Ô×ª";
        if ((singularity & EPlanetSingularity::MultipleSatellites) != EPlanetSingularity::None)
            singularityString += "¶àÎÀÐÇ";
        return singularityString;
    }

};

class StarData {
public:
    int seed;
    int index;
    int id;
    std::string name;
    std::string overrideName;
    VectorLF3 position;
    VectorLF3 uPosition;
    float mass = 1.0f;
    float lifetime = 50.0f;
    float age;
    EStarType type;
    float temperature = 8500.0f;
    ESpectrType spectr;
    float classFactor;
    float color;
    float luminosity = 1.0f;
    float radius = 1.0f;
    float acdiskRadius;
    float habitableRadius = 1.0f;
    float lightBalanceRadius = 1.0f;
    float dysonRadius = 10.0f;
    float orbitScaler = 1.0f;
    float asterBelt1OrbitIndex;
    float asterBelt2OrbitIndex;
    float asterBelt1Radius;
    float asterBelt2Radius;
    int planetCount;
    float level;
    float resourceCoef = 1.0f;

    std::vector< PlanetData> planets;

    inline float physicsRadius() {
        return radius * 1200;
    }

    inline float dysonLumino() {
        return Mathf.Round((float)Math.Pow(luminosity, 0.33000001311302185) * 1000.0f) / 1000.0f;
    }


    std::string typeString()
    {
        std::string text = "";
        if (type == EStarType::GiantStar)
        {
            text = ((spectr <= ESpectrType::K) ? (text + "ºì¾ÞÐÇ") : ((spectr <= ESpectrType::F) ? (text + "»Æ¾ÞÐÇ") : ((spectr != ESpectrType::A) ? (text + "À¶¾ÞÐÇ") : (text + "°×¾ÞÐÇ"))));
        }
        else if (type == EStarType::WhiteDwarf)
        {
            text += "°×°«ÐÇ";
        }
        else if (type == EStarType::NeutronStar)
        {
            text += "ÖÐ×ÓÐÇ";
        }
        else if (type == EStarType::BlackHole)
        {
            text += "ºÚ¶´";
        }
        else if (type == EStarType::MainSeqStar)
        {
            if(spectr == ESpectrType::A)
                text = text + "AÐÍºãÐÇ";
            else if (spectr == ESpectrType::B)
                text = text + "BÐÍºãÐÇ";
            else if (spectr == ESpectrType::F)
                text = text + "FÐÍºãÐÇ";
            else if (spectr == ESpectrType::G)
                text = text + "GÐÍºãÐÇ";
            else if (spectr == ESpectrType::K)
                text = text + "KÐÍºãÐÇ";
            else if (spectr == ESpectrType::M)
                text = text + "MÐÍºãÐÇ";
            else if (spectr == ESpectrType::O)
                text = text + "OÐÍºãÐÇ";
            else
                text = text + "XÐÍºãÐÇ";
        }
        return text;
    }
};
