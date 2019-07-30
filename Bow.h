#pragma once
#include "Weapon.h"
class Bow :public Weapon
{
public:
	//const static WeaponType weptyp = WeaponType::bow;
	const static AttackType atttyp = AttackType::physics;
	Bow(Price pri = 1, Name nam = "Bow",Damage dam = 1, Weight wei = Weight::medium,Damage m_dam=0,Effect eff=Effect::none) :Weapon(pri, nam, dam, wei,m_dam,eff) {}
	//virtual WeaponType r_weptyp()const override { return weptyp; }
	virtual AttackType r_atttyp()const override { return atttyp; }
	virtual Damage r_m_damage()const override { return 0; }
	virtual void s_m_damage(Damage x)override {}
	virtual Effect r_effect()const override { return Effect::none; }
	virtual void s_effect(Effect x)override {}

	// Inherited via Weapon
	virtual void save_to_file(string) const override;
	virtual void load_from_file(string) override;

	// Inherited via Weapon
	virtual int get_quality() override
	{
		return damage * 10;
	}
};
Bow * rand_bow(Quality x=Quality::weak);
Bow * compare_bow(Bow* first, Bow *second);
Bow * compare_bow_worst(Bow* first, Bow *second);

