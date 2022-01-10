#ifndef MATHSTRUCTS_H
#define MATHSTRUCTS_H

template<typename T>
struct Vec2
{
    T x;
    T y;
    T z;
};

template<typename T>
struct Vec3
{
    T x;
    T y;
    T z;
    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3(T px, T py, T pz)
    {
        x = px;
        y = py;
        z = pz;
    }
};

#endif // MATHSTRUCTS_H
