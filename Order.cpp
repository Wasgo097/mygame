#include "Order.h"

bool Order::use_skill(Being * being, Being * target) {
	if (being->r_stamina() > cost) {
		being->reduce_stamina(cost);
		target->get_all_effect()->push_back(std::make_pair(Effect::buff_str, 2));
		target->get_all_effect()->push_back(std::make_pair(Effect::buff_dex, 2));
		target->get_all_effect()->push_back(std::make_pair(Effect::buff_dur, 2));
		target->get_all_effect()->push_back(std::make_pair(Effect::buff_int, 2));
		target->verify_effect();
		return true;
	}
	else return false;
}
