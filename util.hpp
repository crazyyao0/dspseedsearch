#pragma once

#include <math.h>

template<class T> 
class Math_s
{
public:
    const T PI = (T)3.141592653589793238463;
    inline int CeilToInt(T a) const {
        return (int)ceil(a);
    }
    inline int RoundToInt(T a) const {
        return (int)round(a);
    }
    inline T Round(T a) const {
        return (T)round(a);
    }
    inline T Clamp(T a, T min, T max) const {
        if (a < min)return min;
        if (a > max)return max;
        return a;
    }
    inline T Clamp01(T a) const {
        if (a < 0)return 0;
        if (a > 1)return 1;
        return a;
    }
    inline T Lerp(T a, T b, T t) const {
        return a + (b - a) * Clamp01(t);
    }
    inline T Abs(T a) const {
        return (T)abs(a);
    }
    inline T Sqrt(T a) const {
        return (T)sqrt(a);
    }
    inline T Pow(T base, T exp) const {
        return (T)pow(base, exp);
    }
    inline T Sin(T a) const {
        return (T)sin(a);
    }
    inline T Ceil(T a) const {
        return (T)ceil(a);
    }
    inline T Log10(T v) const {
        return (T)log10(v);
    }
    inline T Log(T v) const {
        return (T)log(v);
    }
    inline T Min(T a, T b) const {
        return a < b ? a : b;
    }
    inline T Max(T a, T b) const {
        return a > b ? a : b;
    }
};

const Math_s<float> Mathf;
const Math_s<double> Math;

struct Vector2 {
    float x = 0.0f;
    float y = 0.0f;
};

class VectorLF3 {
public:
    static VectorLF3 zero;
    double x;
    double y;
    double z;

    VectorLF3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    VectorLF3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double sqrMagnitude() const {
        return x * x + y * y + z * z;
    }
    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    VectorLF3 normalized() const {
        double num = x * x + y * y + z * z;
        if (num < 1E-34) 
            return VectorLF3{ 0, 0, 0 };
        double num2 = sqrt(num);
        return VectorLF3{ x / num2, y / num2, z / num2 };
    }
    VectorLF3 operator *(VectorLF3& rhs) const
    {
        return VectorLF3{ x * rhs.x, y * rhs.y, z * rhs.z };
    }
    VectorLF3 operator *(double s) const
    {
        return VectorLF3{ x * s, y * s, z * s };
    }

    VectorLF3 operator - (VectorLF3& rhs) const
    {
        return VectorLF3{ x - rhs.x, y - rhs.y, z - rhs.z };
    }

    VectorLF3 operator + (VectorLF3& rhs) const
    {
        return VectorLF3{ x + rhs.x, y + rhs.y, z + rhs.z };
    }
};

VectorLF3 VectorLF3::zero(0.0, 0.0, 0.0);

class DotNet35Random
{
public:
    int inext = 0;
    int inextp = 31;
    int seedArray[56] = { 0 };

    DotNet35Random(int seed) 
    {
        int num = 161803398 - std::abs(seed);
        seedArray[55] = num;
        int num2 = 1;
        for (int i = 1; i < 55; i++) 
        {
            int num3 = 21 * i % 55;
            seedArray[num3] = num2;
            num2 = num - num2;
            if (num2 < 0) 
                num2 += 2147483647;
            num = seedArray[num3];
        }

        for (int j = 1; j < 5; j++)
        {
            int l = 32;
            for (int k = 1; k < 56; k++)
            {
                seedArray[k] -= seedArray[l];
                if (seedArray[k] < 0)
                    seedArray[k] += 2147483647;
                l = (l >= 55) ? 1 : l + 1;
            }
        }
    }

    double NextDouble()
    {
        return Sample();
    }

    double Sample()
    {
        if (++inext >= 56)
            inext = 1;
        if (++inextp >= 56)
            inextp = 1;
        int num = seedArray[inext] - seedArray[inextp];
        if (num < 0)
            num += 2147483647;
        seedArray[inext] = num;
        return (double)num * 4.6566128752457969E-10;
    }

    int Next() 
    {
        return (int)(Sample() * 2147483647.0);
    }

    int Next(int maxValue)
    {
        return (int)(Sample() * (double)maxValue);
    }

    int Next(int minValue, int maxValue)
    {
        unsigned int num = (unsigned int)(maxValue - minValue);
        if (num <= 1)
            return minValue;
        return (int)((unsigned int)(Sample() * (double)num) + minValue);
    }
};