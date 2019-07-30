#pragma once
#include "Skill.h"
class Fire_ball :
	public Skill{
	static const Stamina cost = 30;
public:
	Fire_ball():Skill("Fire ball"){}
	~Fire_ball(){}
	// Inherited via Skill
	virtual void set_skill(Being * being) override;
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

