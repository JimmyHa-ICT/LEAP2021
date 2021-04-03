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
};