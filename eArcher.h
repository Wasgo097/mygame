#pragma once
#include "Enemies.h"
#include "Critical_shot.h"
#include "Poison_shot.h"
#include "Flame_shot.h"
class eArcher :public Enemies{
public:
	//const static WeaponType weptyp = WeaponType::bow;
	eArcher(Bow * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 30 * lvl + 100, 30 * lvl + 100, 40 * lvl + 120, 40 * lvl + 120, 2 * lvl + 6, 4 * lvl + 10, lvl + 4, 3 * lvl + 8){
		skill1 = std::make_shared<Poison_shot>();
		skill2 = std::make_shared<Flame_shot>();
		skill3 = std::make_shared<Critical_shot>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
eArcher * rand_eArcher(Quality q = Quality::weak);
