#pragma once
#include "Party_member.h"
#include "Hook.h"
#include "Fire_ball.h"
#include "Critical_slash.h"
class Mage_warrior :public Party_member
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	Mage_warrior(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1, Experience c_exp = 0/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Party_member(wep, hel, arm, shi, lvl, c_exp, 30*lvl+115, 30*lvl+115, 40*lvl+110, 40*lvl+110, 2*lvl+4, 3*lvl+10, lvl+6, 4*lvl+8) {
		skill1 = std::make_shared<Fire_ball>();
		skill2 = std::make_shared<Critical_slash>();
		skill3 = std::make_shared<Hook>();
	}

	// Inherited via Party_member
	virtual void save_to_file() const override;
	virtual void load_from_file() override;
	virtual void lev_up() override {
		lv++;
		cur_exp -= max_exp;
		max_exp = 50 * lv + 25;
		m_health = 30*lv+115;
		m_stamina = 40 * lv + 110;
		strenght.first = 2*lv + 4;
		inteligence.first = 3 * lv + 10;
		dexterity.first = lv + 6;
		durability.first = 4 * lv + 8;
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
