#pragma once
#include "Enemies.h"
#include "Fire_ball.h"
#include "Hook.h"
#include "Curse.h"
class Ghost :public Enemies{
public:
	//const static WeaponType weptyp = WeaponType::staff;
	Ghost(Staff * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl /*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Enemies(wep, hel, arm, shi, lvl, 70 * lvl + 120, 70 * lvl + 120, 70 * lvl + 160, 70 * lvl + 160,3*lvl+7,6*lvl+10,4*lvl+8,5*lvl+9){
		skill1 = std::make_shared<Fire_ball>();
		skill2 = std::make_shared<Hook>();
		skill3 = std::make_shared<Curse>();
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
Ghost* rand_ghost(Quality q = Quality::weak);
