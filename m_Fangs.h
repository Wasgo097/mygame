#pragma once
#include "Fangs.h"

class m_Fangs :public Fangs
{
public:
	//const static WeaponType weptyp = Fangs::weptyp;
	const static AttackType atttyp = AttackType::magic;	m_Fangs(Price pri = 1, Name nam = "Magic Fangs", Damage dam = 1, Weight wei = Weight::medium, Damage m_dam = 1, Effect ef = Effect::bleeding) :Fangs(pri, nam, dam, wei, m_dam, ef) {}
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
m_Fangs * rand_m_fangs(Quality x = Quality::weak);