#pragma once
#include "Enemies.h"
#include "Hook.h"
#include "Fire_ball.h"
#include "Critical_slash.h"
class eMage_warrior :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	eMage_warrior(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 30 * lvl + 115, 30 * lvl + 115, 40 * lvl + 110, 40 * lvl + 110, 2 * lvl + 4, 3 * lvl + 10, lvl + 6, 4 * lvl + 8){
		skill1 = std::make_shared<Fire_ball>();
		skill2 = std::make_shared<Critical_slash>();
		skill3 = std::make_shared<Hook>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
eMage_warrior *rand_eMage_warrior(Quality q = Quality::weak);