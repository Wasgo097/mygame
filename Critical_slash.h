#pragma once
#include "Skill.h"
class Critical_slash :
	public Skill
{
	static const Stamina cost = 35;
public:
	Critical_slash() :Skill("Critical slash") {}
	~Critical_slash() {}

	// Inherited via Skill
	virtual void set_skill(Being * being) override;
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

