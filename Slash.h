#pragma once
#include "Skill.h"
class Slash :
	public Skill
{
	static const Stamina cost = 30;
public:
	Slash():Skill("Slash"){}
	~Slash(){}

	// Inherited via Skill
	virtual void set_skill(Being * being) override;
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

