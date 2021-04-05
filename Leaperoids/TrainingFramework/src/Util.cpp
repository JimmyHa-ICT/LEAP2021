#include "Util.h"

int Util::finalScore;
int Util::shipColor;

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

std::string Util::ConvertShipTexture(int textr)
{
    if (textr == 0)
        return "playerShip3_blue";
    if (textr == 1)
        return "playerShip3_red";
    if (textr == 2)
        return "playerShip3_green";
    if (textr == 3)
        return "playerShip3_orange";
}

std::string Util::ConvertLifeTexture(int textr)
{
    if (textr == 0)
        return "playerLife3_blue";
    if (textr == 1)
        return "playerLife3_red";
    if (textr == 2)
        return "playerLife3_green";
    if (textr == 3)
        return "playerLife3_orange";
}

std::string Util::ConvertBulletTexture(int textr)
{
    if (textr == 0)
        return "laserBlue02";
    if (textr == 1)
        return "laserRed02";
    if (textr == 2)
        return "laserGreen04";
    if (textr == 3)
        return "laserRed02";
}