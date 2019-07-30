#pragma once
#include "Sword.h"

class m_Sword :public Sword
{
public:
	//const static WeaponType weptyp = Sword :: weptyp;
	const static AttackType atttyp = AttackType::magic;
	m_Sword(Price pri = 1, Name nam = "Magic Sword",Damage dam = 1, Weight wei = Weight::medium, Damage m_dam = 1, Effect ef = Effect::bleeding):Sword(pri, nam, dam, wei, m_dam, ef){}
	//virtual WeaponType r_weptyp()const { return weptyp; }
	virtual AttackType r_atttyp()const override { return atttyp; }
	virtual Damage r_m_damage()const override { return m_damage; }
	void s_m_damage(Damage x)override { m_damage = x; }
	virtual Effect r_effect()const override { return effect; }
	void s_effect(Effect x)override { effect = x; }
	// Inherited via Weapon
	virtual void save_to_file(string) const override;
	virtual void load_from_file(string) override;
	virtual int get_quality() override
	{
		return damage * 10 + m_damage * 15;
	}
};
m_Sword * rand_m_sword(Quality x = Quality::weak);