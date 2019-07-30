#pragma once
#include "Enemies.h"
#include "Instinct.h"
#include "Critical_slash.h"
#include "Order.h"
class Orc :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	Orc(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl /*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/)
		:Enemies(wep, hel, arm, shi, lvl, 110 * lvl + 80, 110 * lvl + 80, 90 * lvl +100, 90 * lvl + 100, 6 * lvl + 9, 3 * lvl + 7, 4 * lvl + 8, 5 * lvl + 10) {
		skill1 = std::make_shared<Instinct>();
		skill2 = std::make_shared<Critical_slash>();
		skill3 = std::make_shared<Order>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
Orc* rand_orc(Quality q = Quality::weak);