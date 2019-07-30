#pragma once
#include "Skill.h"
class Order :public Skill{
	static const Stamina cost = 45;
public:
	Order():Skill("Order"){}
	~Order(){}
	// Inherited via Skill
	virtual void set_skill(Being * being) override {}
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

