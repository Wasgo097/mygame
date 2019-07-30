#pragma once
#include "m_Helmet.h"
#include "m_Armor.h"
#include "m_Shield.h"
#include "m_Bow.h"
#include "m_Fangs.h"
#include "m_Sword.h"
#include "Staff.h"
//#include "Slash.h"
//#include "Critical_slash.h"
//#include "Instinct.h"
//#include "Critical_shot.h"
//#include "Poison_shot.h"
//#include "Flame_shot.h"
//#include "Hook.h"
//#include "Fire_ball.h"
//#include "Order.h"
//#include "Protection.h"
//#include "Treatment.h"
//#include "Curse.h"
class Skill;
class  Being{
protected:
	Level lv;
	Health c_health,m_health;
	Stamina c_stamina,m_stamina;
	std::pair<Feature, Feature> strenght;
	std::pair<Feature, Feature> inteligence;
	std::pair<Feature, Feature> dexterity;
	std::pair<Feature, Feature> durability;
	Weapon * weapon = nullptr;
	Helmet *helmet = nullptr;
	Armor *armor = nullptr;
	Shield *shield = nullptr;
	std::shared_ptr<Skill> skill1=nullptr;
	std::shared_ptr<Skill> skill2=nullptr;
	std::shared_ptr<Skill> skill3=nullptr;
	std::vector<std::pair<Effect, unsigned short>> effect;
	Being(Weapon * wep, Helmet * hel, Armor * arm, Shield  *shi, Level lvl = 1, Health m_heal = 1, Health c_heal = 1, Stamina m_stam = 1, Stamina c_stam = 1, Feature str = 1, Feature inte = 1, Feature dex = 1, Feature dur = 1){
		weapon = wep;
		helmet = hel;
		armor = arm;
		shield = shi;
		lv = lvl;
		if (m_heal >= c_heal && m_stam >= c_stam){
			m_health = m_heal;
			m_stamina = m_stam;
			c_health = c_heal;
			c_stamina = c_stam;
		}
		else{
			std::cout << "Error character stats!!" << std::endl;
			m_health = m_heal;
			m_stamina = m_stam;
			c_health = m_heal;
			c_stamina = m_stam;
		}
		strenght.first = str;
		inteligence.first = inte;
		dexterity.first = dex;
		durability.first = dur;
		strenght.second = 0;
		inteligence.second = 0;
		durability.second = 0;
		dexterity.second = 0;
	}
	virtual ~Being(){
		if (weapon != nullptr) delete weapon;
		if (helmet != nullptr) delete helmet;
		if (armor != nullptr) delete armor;
		if (shield != nullptr) delete shield;
	}
	Being(const Being & src) = delete; 
	/*{
		lv = src.lv;
		m_health = src.m_health;
		m_stamina = src.m_stamina;
		c_health = src.c_health;
		c_stamina = src.c_stamina;
		strenght.first = src.strenght.first;
		inteligence.first = src.inteligence.first;
		dexterity.first = src.dexterity.first;
		durability.first = src.durability.first;

		strenght.second = 0;
		inteligence.second = 0;
		durability.second = 0;
		dexterity.second = 0;

		WeaponType weptyp = src.weapon->r_weptyp();
		AttackType atyp = src.weapon->r_atttyp();
		Weapon * weapon = nullptr;
		/*switch (weptyp)
		{
		case WeaponType::bow:
			if (atyp == AttackType::physics)
			{
				weapon = new Bow(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight());
			}
			else
			{
				weapon = new m_Bow(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight(), src.weapon->r_m_damage(), src.weapon->r_effect());
			}
			break;
		case WeaponType::fangs:
			if (atyp == AttackType::physics)
			{
				weapon = new Fangs(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight());
			}
			else
			{
				weapon = new m_Fangs(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight(), src.weapon->r_m_damage(), src.weapon->r_effect());
			}
			break;
		case WeaponType::staff:
			weapon = new Staff(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight(), src.weapon->r_m_damage(), src.weapon->r_effect());
			break;
		case WeaponType::sword:
			if (atyp == AttackType::physics)
			{
				weapon = new Sword(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight());
			}
			else
			{
				weapon = new m_Sword(src.weapon->r_price(), src.weapon->r_name(), src.weapon->r_damage(), src.weapon->r_weight(), src.weapon->r_m_damage(), src.weapon->r_effect());
			}
			break;
		}
		DefendType dtyp_a = src.armor->r_deftyp();
		DefendType dtyp_h = src.helmet->r_deftyp();
		DefendType dtyp_s = src.shield->r_deftyp();
		if (dtyp_a == DefendType::physics){
			armor = new Armor(src.armor->r_name(), src.armor->r_price(), src.armor->r_res_damage(), src.armor->r_weight());
		}
		else{
			std::pair<Effect, Defence> *pair = new std::pair<Effect, Defence>[3];
			pair[0].first = Effect::bleeding;
			pair[0].second = src.armor->r_r_m_damage(Effect::bleeding);
			pair[1].first = Effect::toxic;
			pair[1].second = src.armor->r_r_m_damage(Effect::toxic);
			pair[2].first = Effect::stunning;
			pair[2].second = src.armor->r_r_m_damage(Effect::stunning);
			armor = new m_Armor(pair, src.armor->r_name(), src.armor->r_price(), src.armor->r_res_damage(), src.armor->r_weight());
		}
		if (dtyp_h == DefendType::physics){
			helmet = new Helmet(src.helmet->r_name(), src.helmet->r_price(), src.helmet->r_res_damage(), src.helmet->r_weight());

		}
		else{
			std::pair<Effect, Defence> *pair = new std::pair<Effect, Defence>[3];
			pair[0].first = Effect::bleeding;
			pair[0].second = src.helmet->r_r_m_damage(Effect::bleeding);
			pair[1].first = Effect::toxic;
			pair[1].second = src.helmet->r_r_m_damage(Effect::toxic);
			pair[2].first = Effect::stunning;
			pair[2].second = src.helmet->r_r_m_damage(Effect::stunning);
			helmet = new m_Helmet(pair, src.helmet->r_name(), src.helmet->r_price(), src.helmet->r_res_damage(), src.helmet->r_weight());
		}
		if (dtyp_s == DefendType::physics){
			shield = new Shield(src.shield->r_name(), src.shield->r_price(), src.shield->r_res_damage(), src.shield->r_weight());

		}
		else{
			std::pair<Effect, Defence> *pair = new std::pair<Effect, Defence>[3];
			pair[0].first = Effect::bleeding;
			pair[0].second = src.shield->r_r_m_damage(Effect::bleeding);
			pair[1].first = Effect::toxic;
			pair[1].second = src.shield->r_r_m_damage(Effect::toxic);
			pair[2].first = Effect::stunning;
			pair[2].second = src.shield->r_r_m_damage(Effect::stunning);
			shield = new m_Shield(pair, src.shield->r_name(), src.shield->r_price(), src.shield->r_res_damage(), src.shield->r_weight());
		}
	}*/
	Being(Being && src) = delete;
	/*{
		lv = src.lv;
		m_health = src.m_health;
		m_stamina = src.m_stamina;
		c_health = src.c_health;
		c_stamina = src.c_stamina;
		strenght.first = src.strenght.first;
		inteligence.first = src.inteligence.first;
		dexterity.first = src.dexterity.first;
		durability.first = src.durability.first;
		strenght.second = 0;
		inteligence.second = 0;
		durability.second = 0;
		dexterity.second = 0;
		weapon = src.weapon;
		src.weapon = nullptr;
		helmet = src.helmet;
		src.helmet = nullptr;
		armor = src.armor;
		src.armor = nullptr;
		shield = src.shield;
		src.shield = nullptr;
	}*/

	void clear_buff() {
		s_a_dexterity(0);
		s_a_durability(0);
		s_a_inteligence(0);
		s_a_strenght(0);
	}
public:
	Shield* r_shield() { return shield; }
	void s_shield(Shield* x) { 
		delete shield;
		shield = x; }
	Helmet* r_helmet() { return helmet;}
	void s_helmet(Helmet* x) { 
		delete helmet;
		helmet = x; }
	Armor* r_armor() { return armor; }
	void s_armor(Armor* x) { 
		delete armor;
		armor = x;
	}
	Weapon * r_weapon()  { return weapon; }
	virtual void s_weapon(Weapon * x) { 
		delete weapon;
		weapon = x;
	}
	Level r_lv()const { return lv; }
	void s_lv(Level x) { lv = x; }
	void add_lv(Level x) { lv += x; }
	Health r_health()const { return c_health; }
	Health r_m_health()const { return m_health; }
	void s_health(Health x) { c_health = x; }
	void s_m_health(Health x) { m_health = x; }
	void reduce_health(Health x) { c_health -= x; }
	void regen_health(Health x) { 
		c_health += x;
		if (c_health > m_health)c_health = m_health;
	}
	Stamina r_stamina()const { return c_stamina; }
	Stamina r_m_stamina()const { return m_stamina; }
	void s_stamina(Stamina x) { c_stamina = x; }
	void s_m_stamina(Stamina x) { m_stamina = x; }
	void reduce_stamina(Stamina x) { c_stamina -= x; }
	/*r_b - return base
	r_a - return additional*/
	Feature r_b_strenght()const { return strenght.first; }
	Feature r_a_strenght()const { return strenght.second; }
	Feature r_strenght()const { return strenght.first + strenght.second; }
	void s_b_strenght(Feature x) { strenght.first = x; }
	void s_a_strenght(Feature x) { strenght.second = x; }
	void add_str(Feature x) { strenght.second += x; }
	void subtract_str(Feature x) { strenght.second -= x; }
	Feature r_b_inteligence()const { return inteligence.first; }
	Feature r_a_inteligence()const { return inteligence.second; }
	Feature r_inteligence()const { return inteligence.first + inteligence.second; }
	void s_b_inteligence(Feature x) { inteligence.first = x; }
	void s_a_inteligence(Feature x) { inteligence.second = x; }
	void add_int(Feature x) { inteligence.second += x; }
	void subtract_int(Feature x) { inteligence.second -= x; }
	Feature r_b_dexterity()const { return dexterity.first; }
	Feature r_a_dexterity()const { return dexterity.second; }
	Feature r_dexterity()const { return dexterity.first + dexterity.second; }
	void s_b_dexterity(Feature x) { dexterity.first = x; }
	void s_a_dexterity(Feature x) { dexterity.second=x; }
	void add_dex(Feature x) { dexterity.second += x;}
	void subtract_dex(Feature x) { dexterity.second -= x; }
	Feature r_b_durability()const { return durability.first; }
	Feature r_a_durability()const { return durability.second; }
	Feature r_durability()const { return durability.first + durability.second; }
	void s_b_durability(Feature x) { durability.first = x; }
	void s_a_durability(Feature x) { durability.second = x; }
	void add_dur(Feature x) { durability.second += x; }
	void subtract_dur(Feature x) { durability.second -= x; }
	auto get_first_skill()const { return skill1; }
	auto get_second_skill()const { return skill2; }
	auto get_third_skill()const { return skill3; }
	auto get_all_effect() { return &effect; }
	bool is_full_boosted() {
		return str_is_boosted() && dex_is_boosted() && int_is_boosted() && dur_is_boosted();
	}
	bool str_is_boosted() {
		for (auto&x : effect) if (x.first == Effect::buff_str&&x.second > 0) return true;
		return false;
	}
	bool dex_is_boosted() {
		for (auto&x : effect) if (x.first == Effect::buff_dex&&x.second > 0) return true;
		return false;
	}
	bool int_is_boosted() {
		for (auto&x : effect) if (x.first == Effect::buff_int&&x.second > 0) return true;
		return false;
	}
	bool dur_is_boosted() {
		for (auto&x : effect) if (x.first == Effect::buff_dur&&x.second > 0) return true;
		return false;
	}
	bool not_boosted() {
		return !(str_is_boosted() || int_is_boosted() || dex_is_boosted() || dur_is_boosted());
	}
	bool iam_stuned() {
		for (auto&x : effect) if (x.first == Effect::stunning&&x.second > 0)return true;
		return false;
	}
	bool iam_poisoned() {
		for (auto&x : effect) if (x.first == Effect::toxic&&x.second > 0)return true;
		return false;
	}
	bool iam_bleeding() {
		for (auto&x : effect) if (x.first == Effect::bleeding &&x.second > 0)return true;
		return false;
	}
	bool iam_weakened() {
		return iam_bleeding() || iam_poisoned() || iam_stuned();
	}
	bool iam_full_weakened() {
		return iam_bleeding() && iam_poisoned() && iam_stuned();
	}
	bool iam_alive() {
		return c_health > 0;
	}
	void regenerate() {
		if (iam_alive()) {
			c_health += 0.03*m_health;
			if (c_health > m_health)c_health = m_health;
			c_stamina += (0.08*m_stamina) + (r_durability() / 5);
			if (c_stamina > m_stamina)c_stamina = m_stamina;
		}
	}
	void full_regenerate() {
		c_health = m_health;
		c_stamina = m_stamina;
	}
	//sort effect and delete useless
	void check_effect(){
		int null_buff = 0;
		for (int i = effect.size() - 1; i >= 0; i--) {
			if (effect[i].second < 1)null_buff++;
			else break;
		}
		for (size_t i = 0; i < effect.size() - null_buff; i++) {
			if (effect[i].second == 0 && effect[effect.size() - 1 - null_buff].second > 0) {
				std::swap(effect[i], effect[effect.size() - 1 - null_buff]);
				null_buff++;
			}
		}
		for (int i = 0; i < null_buff; i++)effect.pop_back();
	}
	//reduce hp by poisoning and bleeding
	void reduce_hp_by_effect(){for (auto&x : effect) if (x.second > 0 && (x.first == Effect::bleeding || x.first == Effect::toxic)) reduce_health(x.second*((int)x.first + 1) * 10);}
	//reduce the duration of all effects by one
	void reduce_effect(){for (auto&x : effect)x.second--;}
	//removes all positive effects and re-sets them
	void verify_effect(){
		clear_buff();
		for (auto&x : effect) {
			if (x.second > 0 && x.first == Effect::buff_dex) s_a_dexterity(6);
			else if (x.second > 0 && x.first == Effect::buff_str) s_a_strenght(6);
			else if (x.second > 0 && x.first == Effect::buff_dur) s_a_durability(6);
			else if (x.second > 0 && x.first == Effect::buff_int) s_a_inteligence(6);
		}
	}
	std::list<double> get_weight_k() {
		std::list<double> list;
		if (armor->r_weight() == Weight::light) list.push_back(0.95);
		else if (armor->r_weight() == Weight::medium) list.push_back(0.97);
		else list.push_back(1.0);
		if (shield->r_weight() == Weight::light) list.push_back(0.95);
		else if (shield->r_weight() == Weight::medium) list.push_back(0.97);
		else list.push_back(1.0);
		if (helmet->r_weight() == Weight::light) list.push_back(0.95);
		else if (helmet->r_weight() == Weight::medium) list.push_back(0.97);
		else list.push_back(1.0);
		if (weapon->r_weight() == Weight::light) list.push_back(0.95);
		else if (weapon->r_weight() == Weight::medium) list.push_back(0.97);
		else list.push_back(1.0);
		return list;
	}
};
