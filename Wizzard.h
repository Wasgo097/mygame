#pragma once
#include "Party_member.h"
#include "Fire_ball.h"
#include "Treatment.h"
#include "Curse.h"
class Wizzard :public Party_member{
public:
	//const static WeaponType weptyp = WeaponType::staff;
	Wizzard(Staff * wep, Helmet* hel, Armor* arm, Shield* shi, Level lvl = 1, Experience c_exp = 0/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Party_member(wep, hel, arm, shi, lvl, c_exp, 30*lvl+100, 30*lvl+100, 35*lvl+120, 35*lvl+120, lvl+4, 4*lvl+10, 2*lvl+8, 3*lvl+6){
		skill1 = std::make_shared<Fire_ball>();
		skill2 = std::make_shared<Treatment>();
		skill3 = std::make_shared<Curse>();
	}
	// Inherited via Party_member
	virtual void save_to_file() const override;
	virtual void load_from_file() override;
	virtual void lev_up() override {
		lv++;
		cur_exp -= max_exp;
		max_exp = 50 * lv + 25;
		m_health = 30 * lv + 100;
		m_stamina = 35*lv+120;
		strenght.first = lv+4;
		inteligence.first = 4 * lv+10;
		dexterity.first = 2*lv + 8;
		durability.first = 3 * lv + 6;
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
