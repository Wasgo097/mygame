#pragma once
#include "Suit.h"

class Shield :public Suit{
public:
	static const DefendType deftyp = DefendType::physics;
	Shield(Name nam = "Shield", Price pri = 1, Defence res_dam = 1, Weight wei = Weight::light) :Suit(nam, pri,  res_dam, wei) {}
	Shield(Price pri = 1,Name nam = "Shield",  Defence r_dam = 1, Weight wei = Weight::light, Defence res_toxic = 0, Defence res_bleeding = 0, Defence res_stuning = 0) :
		Suit(pri, nam, r_dam, wei, res_toxic, res_bleeding, res_stuning)
	{}
	virtual Defence r_r_m_damage(Effect eff)const override { return 0; };
	virtual void s_r_m_damage(Defence def, Effect eff) override {};
	virtual DefendType r_deftyp() { return deftyp; }

	// Inherited via Suit
	virtual void save_to_file(string) const override;
	virtual void load_from_file(string) override;
	virtual int get_quality() override
	{
		return res_damage * 10;
	}
};
Shield * rand_shield(Quality x = Quality::weak);
Shield* compare_shield(Shield* first, Shield* second);
Shield* compare_shield_worst(Shield* first, Shield* second);