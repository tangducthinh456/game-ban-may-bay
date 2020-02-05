#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"

#include <ctime>
#include <cstdlib>





class ThreatObject : public BaseObject
{
private:
	int m_x_val;
	std::vector<AmoObject*> m_p_amo_list;


public:
	ThreatObject();
	~ThreatObject();

	void Set_x_val(const int& x_val) { m_x_val = x_val; }
	int get_x_val() { return m_x_val; }

	void HandleMove(const int& x_border, const int& _border);
	void HandleMoveUFO(const int& x_border, const int& y_border);

	void SetAmoList(std::vector<AmoObject*> amo_list) { m_p_amo_list = amo_list; };
	std::vector<AmoObject*> GetAmoList() const { return m_p_amo_list; };

	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& xborder);
	void ResetAmo(AmoObject* p_amo);
};



#endif  
