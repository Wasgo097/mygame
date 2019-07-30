#pragma once
#include "Skill.h"
class Hook :public Skill{
	static const Stamina cost = 40;
public:
	Hook():Skill("Hook"){}
	~Hook(){}
	// Inherited via Skill
	virtual void set_skill(Being * being) override;
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

