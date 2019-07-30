#include "Ghost.h"

Ghost * rand_ghost(Quality q) {
	//magic iteam >8
	int i = std::rand() % 10;
	int lv = (int)q * 10 + std::rand() % 10;
	if (i > 8) {
		return new Ghost(rand_staff(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return new Ghost(rand_staff(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
