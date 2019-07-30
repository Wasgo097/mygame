#pragma once
#include "Enemies.h"
#include "Slash.h"
#include "Critical_slash.h"
#include "Instinct.h"
class eFighter :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	eFighter(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 45 * lvl + 105, 45 * lvl + 105, 35 * lvl + 110, 35 * lvl + 110, 4 * lvl + 10, lvl + 4, 3 * lvl + 8, 2 * lvl + 6){
		skill1 = std::make_shared<Slash>();
		skill2 = std::make_shared<Critical_slash>();
		skill3 = std::make_shared<Instinct>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
eFighter* rand_eFighter(Quality q = Quality::weak);