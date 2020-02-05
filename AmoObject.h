#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_


#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"



class AmoObject : public BaseObject
{
public:
	enum AmoType
	{
		NONE = 0,
		LASER = 1,
		SPHERE = 2
	};

AmoObject();
~AmoObject();


void HandleMove(const int& x_border, const int& y_border);
void HandleMoveRightToLeft();

void setRectX(const int& x_val) { m_x_val = x_val; }
int getRectX() { return m_x_val; }

void set_type(const int& type) { m_amo_type = type; }
unsigned int get_type() const { return m_amo_type; }

void set_is_move(bool is_move) { m_is_move = is_move; }
bool get_is_move() const { return m_is_move; }


void SetWidthHeight(const int& width, const int& height) { m_rect.h = height, m_rect.w = width; }

private:
	int m_x_val;
	bool m_is_move;
	int m_amo_type;

};


#endif AMO_OBJECT_H_
