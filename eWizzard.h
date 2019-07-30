#pragma once
#include "Enemies.h"
#include "Fire_ball.h"
#include "Treatment.h"
#include "Curse.h"
class eWizzard :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	eWizzard(Staff * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 30 * lvl + 100, 30 * lvl + 100, 35 * lvl + 120, 35 * lvl + 120, lvl + 4, 4 * lvl + 10, 3 * lvl + 8, 2 * lvl + 6){
		skill1 = std::make_shared<Fire_ball>();
		skill2 = std::make_shared<Treatment>();
		skill3 = std::make_shared<Curse>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
eWizzard * rand_eWizzard(Quality q = Quality::weak);
