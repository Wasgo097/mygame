#pragma once
#include "Helmet.h"

class m_Helmet :public Helmet{
public:
	static const DefendType deftyp = DefendType::magic;
	m_Helmet(std::pair<Effect, Defence> * r_eff, Name nam = "Magic Helmet", Price pri = 1, Defence res_dam = 1, Weight wei = Weight::light) :Helmet(nam, pri, res_dam, wei) {
		if (r_eff != nullptr) {
			res_effect = r_eff;
			r_eff = nullptr;
		}
		else {
			res_effect = new std::pair<Effect, Defence>[res_effect_size];
			res_effect[0].first = Effect::bleeding;
			res_effect[0].second = 0;
			res_effect[1].first = Effect::toxic;
			res_effect[1].second = 0;
			res_effect[2].first = Effect::stunning;
			res_effect[2].second = 1;
		}
	}
	m_Helmet(Name nam = "Magic Helmet", Price pri = 1, Defence r_dam = 1, Weight wei = Weight::light, Defence res_toxic = 0, Defence res_bleeding = 0, Defence res_stuning = 1) :
		Helmet(pri, nam,  r_dam, wei, res_toxic, res_bleeding, res_stuning)
	{}
	virtual Defence r_r_m_damage(Effect eff)const override
	{
		if (eff == Effect::none)return 0;
		for (int i = 0; i < res_effect_size; i++)
		{
			if (res_effect[i].first == eff)
			{
				return res_effect[i].second;
			}
		}
	}
	virtual void s_r_m_damage(Defence def, Effect eff) override
	{
		for (int i = 0; i < res_effect_size; i++)
		{
			if (res_effect[i].first == eff)
			{
				res_effect[i].second = def; break;
			}
		}
	}
	virtual DefendType r_deftyp() { return deftyp; }
	virtual void save_to_file(string) const override;
	virtual void load_from_file(string) override;
	virtual int get_quality() override
	{
		return res_damage * 10 + res_effect[0].second * 15 + res_effect[1].second * 15 + res_effect[2].second * 15;
	}
};
m_Helmet * rand_m_helmet(Quality x = Quality::weak);

