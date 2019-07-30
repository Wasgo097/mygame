#include "Instinct.h"

bool Instinct::use_skill(Being * being, Being * target) {
	if (being->r_stamina() > cost) {
		being->reduce_stamina(cost);
		being->get_all_effect()->push_back(std::make_pair(Effect::buff_str, 3));
		being->get_all_effect()->push_back(std::make_pair(Effect::buff_dex, 3));
		being->get_all_effect()->push_back(std::make_pair(Effect::buff_dur, 3));
		being->verify_effect();
		return true;
	}
	else return false;
}
