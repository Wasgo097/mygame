#pragma once
#include "Shared.h"
#include "Being.h"
class Skill {
protected:
	Damage damage;
	Damage m_damage;
	Effect effect = Effect::none;
	string name;
public:
	Skill(string name) { this->name = name; }
	virtual ~Skill() {}
	virtual void set_skill(Being* being) = 0;
	virtual bool use_skill(Being * being,Being * target) = 0;
	std::pair<Damage, std::pair<Damage, Effect>> get_damage() {return std::make_pair(damage, std::make_pair(m_damage, effect));}
	string r_name() { return name; }
	virtual Stamina r_cost()const=0;
};

