#pragma once
#include "Iteam.h"
class Suit:public Iteam{
protected:
	Defence res_damage;
	std::pair  <Effect, Defence> * res_effect = nullptr;
	static const size_t res_effect_size = 3;
	static const DefendType deftyp = DefendType::physics;
	Suit(Name nam = "Suit", Price pri = 1,  Defence r_dam = 1, Weight wei = Weight::light) :Iteam(pri, nam,wei), res_damage(r_dam){
		res_effect = new std::pair<Effect, Defence>[res_effect_size];
		res_effect[0].first = Effect::bleeding;
		res_effect[0].second = 0;
		res_effect[1].first = Effect::toxic;
		res_effect[1].second = 0;
		res_effect[2].first = Effect::stunning;
		res_effect[2].second = 0;
	}
	Suit(std::pair<Effect, Defence> * r_eff,Price pri = 1, Name nam = "Suit", Defence r_dam = 1, Weight wei = Weight::light) :Iteam(pri, nam,wei), res_damage(r_dam){
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
			res_effect[2].second = 0;
		}
	}
	Suit(Price pri = 1, Name nam = "Suit", Defence r_dam = 1, Weight wei = Weight::light, Defence res_toxic = 1, Defence res_bleeding = 1, Defence res_stuning = 1) :Iteam(pri, nam,wei), res_damage(r_dam){
		res_effect = new std::pair<Effect, Defence>[res_effect_size];
		res_effect[0].first = Effect::bleeding;
		res_effect[0].second = res_bleeding;
		res_effect[1].first = Effect::toxic;
		res_effect[1].second = res_toxic;
		res_effect[2].first = Effect::stunning;
		res_effect[2].second = res_stuning;
	}
	/*Suit(const Suit & src) :Iteam(src.price, src.name), res_damage(src.res_damage), weight(src.weight)
	{
		this->~Suit();
		if (src.res_effect != nullptr)
		{
			res_effect = new std::pair<Effect, Defence>[3];
			for (int i = 0; i <= 3; i++)
			{
				res_effect[i].first = src.res_effect[i].first;
				res_effect[i].second = src.res_effect[i].second;
			}
		}
	}
	Suit(Suit && src) :Iteam(src.price, src.name), res_damage(src.res_damage), weight(src.weight)
	{
		this->~Suit();
		res_effect = src.res_effect;
		src.res_effect = nullptr;
	}*/
	virtual ~Suit()
	{
		if (res_effect != nullptr)
		{
			delete[] res_effect;
		}
		res_effect = nullptr;
	}
public:
	void s_res_dam(Defence res_dam) { res_damage = res_dam; }
	Defence r_res_damage()const { return res_damage; }
	DefendType r_deftyp() { return deftyp; }
	virtual void s_r_m_damage(Defence def, Effect eff) = 0;
	virtual Defence r_r_m_damage(Effect eff)const = 0;
	
	// Inherited via Iteam
	virtual void save_to_file(string) const override=0;
	virtual void load_from_file(string) override=0;
	virtual int get_quality() = 0;
};
