#pragma once
#include "Party_member.h"
#include "Order.h"
#include "Protection.h"
#include "Slash.h"
class Tank :public Party_member
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	Tank(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1, Experience c_exp = 0/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/) 
		:Party_member(wep, hel, arm, shi,  lvl, c_exp, 50*lvl+130, 50*lvl+130, 30*lvl+110, 30*lvl+110, 3*lvl+8,2*lvl+6, lvl+4, 4*lvl+10){
		skill1 = std::make_shared<Slash>();
		skill2 = std::make_shared<Order>();
		skill3 = std::make_shared<Protection>();
	}

	// Inherited via Party_member
	virtual void save_to_file() const override;
	virtual void load_from_file() override;
	virtual void lev_up() override {
		lv++;
		cur_exp -= max_exp;
		max_exp = 50 * lv + 25;
		m_health = 50*lv+130;
		m_stamina = 30 * lv + 110;
		strenght.first = 3*lv + 8;
		inteligence.first = 2 * lv + 6;
		dexterity.first = lv + 4;
		durability.first = 4 * lv + 10;
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
