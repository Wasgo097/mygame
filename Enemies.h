#pragma once
#include "Being.h"
class Enemies :public Being
{
protected:
	Enemies(Weapon * wep, Helmet * hel, Armor* arm, Shield* shi, Level lvl = 1, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1) :Being(wep, hel, arm, shi, lvl, m_heal, c_heal, m_stam, c_stam, str,inte, dex, dur){

	}
public:
	//virtual WeaponType r_weptyp()const override = 0;
};
