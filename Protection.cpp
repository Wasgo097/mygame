#include "Protection.h"

bool Protection::use_skill(Being * being, Being * target) {
	if (being->r_stamina() > cost) {
		being->reduce_stamina(cost);
		target->regen_health(being->r_inteligence() * 5);
		for (auto &x : *target->get_all_effect()) {
			if (x.first == Effect::bleeding || x.first == Effect::toxic || x.first == Effect::stunning) {
				x.second = 0;
				break;
			}
		}
		return true;
	}
	else return false;
}
