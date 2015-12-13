#pragma once

#include <random>

namespace math
{
#ifdef _USE_MATH_DEFINES

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

#endif  /* _USE_MATH_DEFINES */


static std::mt19937 standard_rand_engine = std::mt19937(std::random_device {}());

template<class T> T clamp(T value, T min, T max = std::numeric_limits<T>().max())
{
    return value <= min ? min : value >= max ? max : value;
};

template<class T> T rand(T min, T max)
{
    std::uniform_int_distribution<T> dist(min, max);
    return dist(standard_rand_engine);
};

template<class T> T rand(T max)
{
    return rand((T)0, max);
};

inline float rand(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(standard_rand_engine);
};

inline float rand(float max)
{
    return rand(0, max);
};

inline double rand(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(standard_rand_engine);
};

inline double rand(double max)
{
    return rand(0.0, max);
};

template<class T> T getDistance(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
    T kx = v1.x - v2.x;
    T ky = v1.y - v2.y;

    return sqrt(pow(kx, 2) + pow(ky, 2));
};

template<class T, class T2, class T3> bool isBetween(T val, T2 p1, T3 p2)
{
    return (val > p1 && val < p2);
};

template<class T> T toRad(T val)
{
    return val * M_PI / 180;
};

template<class T> T toDeg(T val)
{
    return val * 180 / M_PI;
};

template<class T> sf::Vector2<T> rotatePoint(sf::Vector2<T> vec, T sin, T cos)
{
    return { vec.x * cos - vec.y * sin, vec.x * sin + vec.y * cos };
};

template<class T> sf::Vector2<T> rotatePoint(sf::Vector2<T> vec, T degree)
{
    return rotatePoint(vec, (T)sin(degree), (T)cos(degree));
};

template<class T> sf::Vector2<T> rotatePoint(sf::Vector2<T> vec, sf::Vector2<T> around, T sin, T cos)
{
    return around + rotatePoint(vec - around, sin, cos);
};

template<class T> sf::Vector2<T> rotatePoint(sf::Vector2<T> vec, sf::Vector2<T> around, T degree)
{
    return rotatePoint(vec, around, (T)sin(degree), (T)cos(degree));
};

template<class T> T length(sf::Vector2<T> vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
};

template<class T> T normalize(T vector)
{
    float length = math::length(vector);
    if (length == 0)
        return sf::Vector2f(0, 0);
    vector.x = vector.x / length;
    vector.y = vector.y / length;

    return vector;
};

template<class T> sf::Vector2<T> angleToVector(T val)
{
    return normalize(sf::Vector2<T>(sin(toRad(val)), -cos(toRad(val))));
};


template<class T> T vectorToAngle(sf::Vector2<T> val)
{
    float angle = toDeg(atan2(val.x, -val.y));
    //    if(angle < 0.f)
    //        angle = 360.f + angle;
    return angle;
};

template<class T> T dot(sf::Vector2<T> vector1, sf::Vector2<T> vector2)
{
    return vector1.x*vector2.x + vector1.y*vector2.y;
};

template<class T> T perpDot(sf::Vector2<T> vector1, sf::Vector2<T> vector2)
{
    return (vector1.y*vector2.x) - (vector1.x*vector2.y);
};

template<class T> sf::Vector2<T> crossProduct(T val, sf::Vector2<T> vector)
{
    return sf::Vector2<T>(-val * vector.y, val * vector.x);
};

template<typename T> T lerp(T value1, T value2, float interpolation)
{
    return (value1 * (1.0f - interpolation)) + (value2 * interpolation);
};

template<typename T> sf::Vector2<T> lerp(sf::Vector2<T> value1, sf::Vector2<T> value2, float interpolation)
{
    return {lerp(value1.x,value2.x,interpolation), lerp(value1.y,value2.y,interpolation)};
};

template<typename T> T perpandicular(T vector)
{
    return T(-vector.y, vector.x);
};

const float tolerance = 0.0000001f;//1e-15;

template<typename T> T roundNearZero(T val)
{
    return std::fabs(val) < tolerance ? 0 : val;
};

template<typename T> sf::Vector2<T> roundNearZero(sf::Vector2<T> vector)
{
    vector.x = roundNearZero(vector.x);
    vector.y = roundNearZero(vector.y);

    return vector;
};

template<typename T> sf::Vector3<T> findTriangleAngle(sf::Vector2<T> a, sf::Vector2<T> b, T ac, T bc)
{
    float A, B, C;

    T ab = getDistance(a, b);

    C = acos((pow(ab, 2) + pow(ac, 2) - pow(bc, 2)) / (2 * ab*ac));
    B = acos((pow(ab, 2) + pow(bc, 2) - pow(ac, 2)) / (2 * ab*bc));
    A = acos((pow(ac, 2) + pow(bc, 2) - pow(ab, 2)) / (2 * ac*bc));

    return { A, B, C };
};

template<typename T> sf::Vector2<T> findTriangleThirdPoint(sf::Vector3<T> angles, sf::Vector2<T> a, sf::Vector2<T> b, T ac, bool firstPosibility = true)
{
    float f = atan2((a - b).y, (a - b).x) + (angles.z*(firstPosibility ? 1 : -1));
    return sf::Vector2f(cos(f)*ac, sin(f)*ac) + b;
};
};

template<typename T>
sf::Vector2<T> operator*(sf::Vector2<T> left, sf::Vector2<T> right)
{
    return {left.x*right.x, left.y*right.y};
}

inline
sf::Vector2f getSize(sf::Text& text) //lazyness will one day kill me
{
    sf::FloatRect rect = text.getLocalBounds();
    return {rect.left + rect.width, rect.top + rect.height};
}


template<typename T>
void setTextSize(sf::Text& text, sf::Vector2<T> size, sf::Vector2<T> margin)
{
    sf::FloatRect rect = text.getLocalBounds();
    sf::Vector2f textSize(rect.left + rect.width, rect.top + rect.height);

    sf::Vector2f ratio((size.x - margin.x) / (textSize.x), (size.y - margin.y) / (textSize.y));
    float charSize = ((ratio.x + ratio.y)/2.f) * text.getCharacterSize();
    text.setCharacterSize(charSize);

    rect = text.getLocalBounds();
    textSize = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    text.setScale((size.x - margin.x) / (textSize.x), (size.y - margin.y) / (textSize.y));

    rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width/2.f, rect.top + rect.height/2.f);
//    text.move(size/2.f);
}
