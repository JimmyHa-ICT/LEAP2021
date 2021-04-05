#pragma once
#include <iostream>

class Util
{
private:
    static int finalScore;
public:
    static void SetFinalScore(int score);

    static std::string GetFinalScore();

    static std::string ToStringFixedLength(int value, int digits = 3);

    static std::string ConvertShipTexture(int textr);

    static std::string ConvertLifeTexture(int textr);

    static std::string ConvertBulletTexture(int textr);

    static int shipColor;
};