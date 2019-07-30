#pragma once
#include "Suit.h"

class Armor :public Suit{
public:
	static const DefendType deftyp = DefendType::physics;
	Armor(Name nam="Armor",Price pri=1,Defence res_dam=1,Weight wei=Weight::light):Suit(nam, pri,res_dam,wei){}
	Armor(Price pri = 1, Name nam = "Armor",   Defence r_dam = 1, Weight wei = Weight::light, Defence res_toxic = 0, Defence res_bleeding = 0, Defence res_stuning = 0) :
		Suit(pri, nam, r_dam, wei, res_toxic, res_bleeding, res_stuning)
	{}
	virtual Defence r_r_m_damage(Effect eff)const override { return 0; };
	virtual void s_r_m_damage(Defence def, Effect eff)override {};
	virtual DefendType r_deftyp() { return deftyp; }

	// Inherited via Suit
	virtual void save_to_file(string) const override;
	virtual void load_from_file(string) override;
	virtual int get_quality() override
	{
		return res_damage * 10;
	}
};
Armor * rand_armor(Quality x = Quality::weak);
Armor* compare_armor(Armor* first, Armor* second);
Armor* compare_armor_worst(Armor* first, Armor* second);