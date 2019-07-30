#pragma once
#include "Enemies.h"
#include "Critical_slash.h"
#include "Hook.h"
#include "Instinct.h"
class Werewolf :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::fangs;
	Werewolf(Fangs * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/)
		:Enemies(wep, hel, arm, shi, lvl, 100 * lvl + 100, 100 * lvl + 100, 100 * lvl + 150, 100 * lvl + 150, 6 * lvl + 10, 3 * lvl + 7, 4 * lvl + 8, 5 * lvl + 9){
		skill1 = std::make_shared<Critical_slash>();
		skill2 = std::make_shared<Hook>();
		skill3 = std::make_shared<Instinct>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};

Werewolf * rand_werewolf(Quality q);