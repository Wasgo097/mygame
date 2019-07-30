#pragma once
#include "Skill.h"
class Treatment :
	public Skill
{
	static const Stamina cost = 45;
public:
	Treatment():Skill("Treatment"){}
	~Treatment(){}
	// Inherited via Skill
	virtual void set_skill(Being * being) override{}
	virtual bool use_skill(Being * being, Being * target) override;
	// Inherited via Skill
	virtual Stamina r_cost() const override{
		return cost;
	}
};

