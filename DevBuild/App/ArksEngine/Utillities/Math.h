#pragma once
#include <cmath>
#include <algorithm>
// This is a Class for all math
namespace ArksEngine
{
    template<typename T>
    class Math {
    public:
        // Add two numbers
        static T Add(T a, T b) { return a + b; }

        // Subtract two numbers
        static T Subtract(T a, T b) { return a - b; }

        // Multiply two numbers
        static T Multiply(T a, T b) { return a * b; }

        // Divide two numbers
        static T Divide(T a, T b) { return a / b; }

        // Calculate modulus of two numbers
        static T Modulus(T a, T b) { return a % b; }

        // Raise a number to a power
        static T Power(T base, T exponent) { return pow(base, exponent); }

        // Calculate the square of a number
        static T Square(T x) { return x * x; }

        // Calculate the square root of a number
        static T SquareRoot(T x) { return sqrt(x); }

        // Calculate the cube root of a number
        static T CubeRoot(T x) { return cbrt(x); }

        // Calculate the nth root of a number
        static T NthRoot(T x, T n) { return pow(x, 1 / n); }

        // Calculate the sine of an angle (in radians)
        static T Sin(T x) { return sin(x); }

        // Calculate the cosine of an angle (in radians)
        static T Cos(T x) { return cos(x); }

        // Calculate the tangent of an angle (in radians)
        static T Tan(T x) { return tan(x); }

        // Calculate the arcsine of a value (result in radians)
        static T Asin(T x) { return asin(x); }

        // Calculate the arccosine of a value (result in radians)
        static T Acos(T x) { return acos(x); }

        // Calculate the arctangent of a value (result in radians)
        static T Atan(T x) { return atan(x); }

        // Calculate the arctangent of a point (y, x) (result in radians)
        static T Atan2(T y, T x) { return atan2(y, x); }

        // Calculate the natural logarithm (base e) of a number
        static T Log(T x) { return log(x); }

        // Calculate the base-10 logarithm of a number
        static T Log10(T x) { return log10(x); }

        // Calculate the logarithm of a number with a custom base
        static T LogBase(T x, T base) { return log(x) / log(base); }

        // Round a number to the nearest integer
        static T Round(T x) { return round(x); }

        // Round a number up to the nearest integer
        static T Ceil(T x) { return ceil(x); }

        // Round a number down to the nearest integer
        static T Floor(T x) { return floor(x); }

        // Truncate the decimal part of a number
        static T Trunc(T x) { return trunc(x); }

        // Calculate the absolute value of a number
        static T Abs(T x) { return abs(x); }

        // Return the minimum of two numbers
        static T Min(T a, T b) { return std::min(a, b); }

        // Return the maximum of two numbers
        static T Max(T a, T b) { return max(a, b); }

        // Clamp a value between a minimum and maximum value
        static T Clamp(T value, T minValue, T maxValue) { return std::clamp(value, minValue, maxValue); }

        // Perform linear interpolation between two values
        static T Lerp(T a, T b, T t) { return a + t * (b - a); }

        // Convert degrees to radians
        static T DegToRad(T degrees) { return degrees * (acos(-1) / 180.0); }

        // Convert radians to degrees
        static T RadToDeg(T radians) { return radians * (180.0 / acos(-1)); }

    };
}


