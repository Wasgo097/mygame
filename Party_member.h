#pragma once
#include "Being.h"

class Party_member :public Being{
protected:
	Experience max_exp;
	Experience cur_exp;
	Party_member(Weapon * wep, Helmet *hel, Armor * arm, Shield * shi, Level lvl = 1, Experience c_exp = 0, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1) 
		:Being(wep, hel, arm, shi, lvl, m_heal, c_heal, m_stam, c_stam, str,inte, dex, dur), cur_exp(c_exp){
		max_exp = 50 * lv + 25;
	}
	Party_member() = default;
public:
	void add_exp(Experience x){cur_exp += x;}
	Experience r_c_exp()const{return cur_exp;}
	Experience r_m_exp()const {return max_exp;}
	virtual void save_to_file()const = 0;
	virtual void load_from_file() = 0;
	bool posible_promotion() { return cur_exp >= max_exp; }
	virtual void lev_up()=0;
};
