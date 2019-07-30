#pragma once
#include "Party_member.h"
#include "Slash.h"
#include "Critical_slash.h"
#include "Instinct.h"
class Fighter :public Party_member
{
public:
	//const static WeaponType weptyp = WeaponType::sword;
	Fighter(Sword * wep, Helmet * hel, Armor * arm, Shield * shi, Level lvl = 1, Experience c_exp = 0/*, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1*/)
		:Party_member(wep, hel, arm, shi, lvl, c_exp, 45*lvl+105, 45*lvl+105, 35*lvl+110,35*lvl+110, 4*lvl+10,lvl+4, 3*lvl+8, 2*lvl+6) {
		skill1 = std::make_shared<Slash>();
		skill2 = std::make_shared<Critical_slash>();
		skill3 = std::make_shared<Instinct>();
	}
	// Inherited via Party_member
	virtual void save_to_file() const override;
	virtual void load_from_file() override;
	virtual void lev_up() override {
		lv++;
		cur_exp -= max_exp;
		max_exp = 50 * lv + 25;
		m_health = 45*lv+105;
		m_stamina = 35 * lv + 110;
		strenght.first = 4*lv + 10;
		inteligence.first = lv+4;
		dexterity.first = 3 * lv + 8;
		durability.first = 2 * lv + 6;
	}
	//WeaponType r_weptyp()const override { return weptyp; }
};
