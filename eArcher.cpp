#include "eArcher.h"

eArcher * rand_eArcher(Quality q) {
	//magic iteam >6
	int i = std::rand() % 10;
	int lv = (int)q * 10 + std::rand() % 10;
	if (i > 6) {
		return  new eArcher(rand_m_bow(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return  new eArcher(rand_bow(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
