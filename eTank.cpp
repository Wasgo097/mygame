#include "eTank.h"

eTank * rand_eTank(Quality q) {

	//magic iteam >6
	int i = std::rand() % 10;
	int lv = (int)q * 10 + std::rand() % 10;
	if (i > 6) {
		return new eTank(rand_m_sword(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return new eTank(rand_sword(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
