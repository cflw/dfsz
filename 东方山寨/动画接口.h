#pragma once
#include <variant>
#include "��ѧ����.h"
#include "����.h"
namespace ����ɽկ {
//=============================================================================
// �����ӿ�
//=============================================================================
typedef std::variant<int, float, bool> t��������ֵ;
enum class E�������� {
	e����,
	eˮƽ�ƶ�,
	e����,
	e�̶�֡,
	e͸����,
};
class I���� {
public:
	virtual void f�ӿ�_s������(void *);	//��ʼ��ʱ����
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����(const E�������� &, const t��������ֵ & = {});
	virtual int f�ӿ�_g�������() const;
	virtual t����3 f�ӿ�_g��ת() const;
	virtual t����3 f�ӿ�_g����() const;
	virtual float f�ӿ�_g͸����() const;
	virtual const C��Ϸ�ٶ� *f�ӿ�_g��Ϸ�ٶ�() const;	//����������������Ϸ�ٶ�
	static int fg����ֵi(const t��������ֵ &);
	static float fg����ֵf(const t��������ֵ &);
	static bool fg����ֵb(const t��������ֵ &);
};
}