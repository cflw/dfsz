#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
class C�ӵ�;
class C���;
class C���ը��;
class C���������;
class C�ӵ������ը���ж� {
public:
	typedef std::function<bool(const t����2 &, float)> tf�ж�;
	void f�󶨵���(C��������� *);
	void f���ӵ�(C�ӵ� *);
	void f��ը��(C���ը�� *);
	void f�����ж�();	//���������
	bool fi��������() const;	//������Ϸ״̬ȷ���Ƿ���Բ�������
	bool fը��_�ύ�ж�(tf�ж�);
	bool fը��_�ύ�ж�(const tԲ�� &);
	bool f�ӵ�_�ύ�ж�(const t����2 &, float) const;
	void f�ӵ�_��������(const t����2 &����, const t����2 &�ٶ�) const;
private:
	C��� *m��� = nullptr;
	C�ӵ� *m�ӵ� = nullptr;
	C���ը�� *mը�� = nullptr;
	C��������� *m��������� = nullptr;
	tf�ж� mf�ж� = nullptr;
};

}