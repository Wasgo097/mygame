#pragma once
#include "Enemies.h"
#include "Instinct.h"
#include "Poison_shot.h"
#include "Critical_shot.h"
class Spider :public Enemies
{
public:
	//const static WeaponType weptyp = WeaponType::fangs;
	Spider(Fangs * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 80*lvl+90, 80*lvl+90, 70*lvl+40,70*lvl+40,4*lvl+8,3*lvl+7,5*lvl+9,6*lvl+10){
		skill1 = std::make_shared<Instinct>();
		skill2 = std::make_shared<Poison_shot>();
		skill3 = std::make_shared<Critical_shot>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};

Spider* rand_spider(Quality q);