#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
class C�л�;
class C����ӵ�;
class C�л�������ӵ��ж� {
public:
	typedef std::function<bool(const tԲ�� &)> tf�ж�;
	void f�󶨵л�(C�л� &);
	void f������ӵ�(C����ӵ� &);
	bool f����ӵ�_�ύ�ж�(const tf�ж� &);
	bool f����ӵ�_�ύ�ж�(const tԲ�� &);
	bool f����ӵ�_�ύ�ж�(const t��ת���� &);
	C�л� *m�л� = nullptr;
	C����ӵ� *m�ӵ� = nullptr;
};

}