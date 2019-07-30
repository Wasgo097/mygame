#include "Treatment.h"

 bool Treatment::use_skill(Being * being, Being * target) {
	if (being->r_stamina() > cost) {
		being->reduce_stamina(cost);
		target->regen_health(2 * being->r_inteligence() + 2 * being->r_weapon()->r_m_damage());
		return true;
	}
	else return false;
}
