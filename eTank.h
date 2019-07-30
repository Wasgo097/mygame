#pragma once
#include "Enemies.h"
#include "Order.h"
#include "Protection.h"
#include "Slash.h"
class eTank :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	eTank(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 50 * lvl + 130, 50 * lvl + 130, 30 * lvl + 110, 30 * lvl + 110, 3 * lvl + 8, 2 * lvl + 6, lvl + 4, 4 * lvl + 10){
		skill1 = std::make_shared<Slash>();
		skill2 = std::make_shared<Order>();
		skill3 = std::make_shared<Protection>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
eTank *rand_eTank(Quality q = Quality::weak);