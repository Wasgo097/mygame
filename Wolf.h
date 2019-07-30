#pragma once
#include "Enemies.h"
#include "Slash.h"
#include "Hook.h"
#include "Instinct.h"
class Wolf :public Enemies{
public:
	//const static WeaponType weptyp = WeaponType::fangs;
	Wolf(Fangs * wep, Helmet *hel, Armor* arm, Shield *shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 30 * lvl + 100, 30 * lvl + 100, 40 * lvl + 115, 40 * lvl + 115, 4 * lvl + 10, lvl + 4, 3 * lvl + 8, 2 * lvl + 6){
		skill1 = std::make_shared<Slash>();
		skill2 = std::make_shared<Hook>();
		skill3 = std::make_shared<Instinct>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};

Wolf * rand_wolf(Quality q);