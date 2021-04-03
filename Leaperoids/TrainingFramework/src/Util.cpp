#include "Util.h"

int Util::finalScore;

void Util::SetFinalScore(int score)
{
	Util::finalScore = score;
}

std::string Util::GetFinalScore()
{
    if (finalScore)
        return ToStringFixedLength(finalScore, 6);
    return "000000";
}

std::string Util::ToStringFixedLength(int value, int digits)
{
    unsigned int uvalue = value;
    if (value < 0) {
        uvalue = -uvalue;
    }
    std::string result;
    while (digits-- > 0) {
        result += ('0' + uvalue % 10);
        uvalue /= 10;
    }
    if (value < 0) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}