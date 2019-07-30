#pragma once
#include "Skill.h"
class Flame_shot :
	public Skill{
	static const Stamina cost = 35;
public:
	Flame_shot():Skill("Flaming shot"){}
	~Flame_shot(){}
	// Inherited via Skill
	virtual void set_skill(Being * being) override;
	virtual bool use_skill(Being * being, Being * target) override;
	virtual Stamina r_cost()const override {
		return cost;
	}
};

