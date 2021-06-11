#include "pch.h"
#include "MfxExplain.h"

#define PI 3.14

MFX_PORT double MicroFlakeX::MfxEaseInSine(double x)
{
    return (1 - cos((x * PI) / 2));
}

MFX_PORT double MicroFlakeX::MfxEaseOutSine(double x)
{
    return (sin((x * PI) / 2));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutSine(double x)
{
    return (-(cos(PI * x) - 1) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInQuad(double x)
{
    return (x * x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutQuad(double x)
{
    return (1 - (1 - x) * (1 - x));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutQuad(double x)
{
    return (x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInCubic(double x)
{
    return (x * x * x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutCubic(double x)
{
    return (1 - pow(1 - x, 3));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutCubic(double x)
{
    return (x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInQuart(double x)
{
    return (x * x * x * x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutQuart(double x)
{
    return (1 - pow(1 - x, 4));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutQuart(double x)
{
    return (x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInQuint(double x)
{
    return (x * x * x * x * x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutQuint(double x)
{
    return (1 - pow(1 - x, 5));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutQuint(double x)
{
    return (x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInExpo(double x)
{
    return (x == 0 ? 0 : pow(2, 10 * x - 10));
}

MFX_PORT double MicroFlakeX::MfxEaseOutExpo(double x)
{
    return (x == 1 ? 1 : 1 - pow(2, -10 * x));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutExpo(double x)
{
    return (x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5 ? pow(2, 20 * x - 10) / 2
        : (2 - pow(2, -20 * x + 10)) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInCirc(double x)
{
    return (1 - sqrt(1 - pow(x, 2)));
}

MFX_PORT double MicroFlakeX::MfxEaseOutCirc(double x)
{
    return (sqrt(1 - pow(x - 1, 2)));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutCirc(double x)
{
    return (x < 0.5
        ? (1 - sqrt(1 - pow(2 * x, 2))) / 2
        : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInBack(double x)
{
    double c1 = 1.70158;
    double c3 = c1 + 1;

    return (c3 * x * x * x - c1 * x * x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutBack(double x)
{
    double c1 = 1.70158;
    double c3 = c1 + 1;

    return (1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
}

MFX_PORT double MicroFlakeX::MfxEaseInOutBack(double x)
{
    double c1 = 1.70158;
    double c2 = c1 * 1.525;

    return (x < 0.5
        ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
        : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
}

MFX_PORT double MicroFlakeX::MfxEaseInElastic(double x)
{
    double c4 = (2 * PI) / 3;

    return (x == 0
        ? 0
        : x == 1
        ? 1
        : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
}

MFX_PORT double MicroFlakeX::MfxEaseOutElastic(double x)
{
    double c4 = (2 * PI) / 3;

    return (x == 0
        ? 0
        : x == 1
        ? 1
        : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
}

MFX_PORT double MicroFlakeX::MfxEaseInOutElastic(double x)
{
    double c5 = (2 * PI) / 4.5;

    return (x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5
        ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
        : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
}

MFX_PORT double MicroFlakeX::MfxEaseInBounce(double x)
{
    return 1 - MfxEaseOutBounce(1 - x);
}

MFX_PORT double MicroFlakeX::MfxEaseOutBounce(double x)
{
    double n1 = 7.5625;
    double d1 = 2.75;

    if (x < 1 / d1) {
        return (n1 * x * x);
    }
    else if (x < 2 / d1) {
        return (n1 * (x -= 1.5 / d1) * x + 0.75);
    }
    else if (x < 2.5 / d1) {
        return (n1 * (x -= 2.25 / d1) * x + 0.9375);
    }
    else {
        return (n1 * (x -= 2.625 / d1) * x + 0.984375);
    }
}

MFX_PORT double MicroFlakeX::MfxEaseInOutBounce(double x)
{
    return (x < 0.5
        ? (1 - MfxEaseOutBounce(1 - 2 * x)) / 2
        : (1 + MfxEaseOutBounce(2 * x - 1)) / 2);
}