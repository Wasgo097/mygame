#pragma once
#include "Iteam.h"
class  Weapon:public Iteam
{
protected:
	Damage damage, m_damage;
	Effect effect = Effect::none;
	Weapon(Price pri = 1, Name nam = "Iteam", Damage dam = 1, Weight wei = Weight::medium, Damage m_dam=0, Effect eff=Effect::none):Iteam(pri, nam,wei), damage(dam),m_damage(m_dam),effect(eff){}
public:
	//const static WeaponType weptyp=WeaponType::null;
	const static AttackType atttyp = AttackType::physics;
	void s_damage(Damage dam) { damage = dam; }
	Damage r_damage()const { return damage; }
	virtual Damage r_m_damage()const  = 0;
	virtual void s_m_damage(Damage x) = 0;
	virtual Effect r_effect()const = 0;
	virtual void s_effect(Effect x) = 0;
	virtual AttackType r_atttyp()const = 0;

	// Inherited via Iteam
	virtual void save_to_file(string) const override=0;
	virtual void load_from_file(string)override=0;
	virtual int get_quality() = 0;
	//virtual WeaponType r_weptyp()const = 0;
};
