#include "Hook.h"

// Inherited via Skill

void Hook::set_skill(Being * being) {
	damage = 0.7*being->r_inteligence() + 0.5*being->r_weapon()->r_damage();
	effect = Effect::bleeding;
	m_damage = 0.5* being->r_weapon()->r_m_damage() + being->r_inteligence();
}
bool Hook::use_skill(Being * being, Being * target) {
	set_skill(being);
	if (being->r_stamina() > cost) {
		Stamina aditional_cost = cost;
		for (auto&x : being->get_weight_k())aditional_cost *= x;
		being->reduce_stamina(aditional_cost);
		Health cause_damage = damage;
		if (being->r_weapon()->r_weight() == Weight::heavy) cause_damage *= 1.0;
		else if (being->r_weapon()->r_weight() == Weight::medium)cause_damage *= 0.97;
		else cause_damage *= 0.95;
		Health cause_m_damage = m_damage;
		Defence armour_def = target->r_armor()->r_res_damage();
		if (target->r_armor()->r_weight() == Weight::heavy)armour_def *= 1.05;
		else if (target->r_armor()->r_weight() == Weight::medium)armour_def *= 1.00;
		else armour_def *= 0.95;
		Defence shield_def = target->r_shield()->r_res_damage();
		if (target->r_shield()->r_weight() == Weight::heavy)shield_def *= 1.05;
		else if (target->r_shield()->r_weight() == Weight::medium)shield_def *= 1.00;
		else shield_def *= 0.95;
		Defence helmet_def = target->r_helmet()->r_res_damage();
		if (target->r_helmet()->r_weight() == Weight::heavy)helmet_def *= 1.05;
		else if (target->r_helmet()->r_weight() == Weight::medium)helmet_def *= 1.00;
		else helmet_def *= 0.95;
		Defence defence = (armour_def + shield_def + helmet_def);
		defence += target->r_durability() / 10; 
		Defence m_defence = target->r_armor()->r_r_m_damage(effect) + target->r_helmet()->r_r_m_damage(effect) + target->r_shield()->r_r_m_damage(effect);
		if (cause_damage - defence < 11)cause_damage = 10;
		else cause_damage -= defence;
		if (cause_m_damage - m_defence < 2)cause_m_damage = 1;
		else {
			cause_m_damage -= m_defence;
			target->get_all_effect()->push_back(std::make_pair(Effect::bleeding, 2));
		}
		target->reduce_health(cause_damage);
		target->reduce_health(cause_m_damage);
		return true;
	}
	else return false;
}
