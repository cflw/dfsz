#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
class C�Ի�;
class C�Ի����ӵ��ж� {
public:
	enum E�ж���� {
		e���ཻ = 0,
		e���� = 0x1,
		e��ײ = 0x2,
	};
	void f���Ի�(C�Ի� *);
	int f�ӵ�_�ύ�ж�(const tԲ�� &);
	int f�ӵ�_�ύ�ж�(const t��ת���� &);
	void f�ӵ�_�ж���Ч();	//���ӵ�����
	bool f�ӵ�_i��ײ() const;
	bool f�ӵ�_i����() const;
	const t����2 &fg�Ի�����() const;
private:
	void f��ײ��������();
	void f������������();
	C�Ի� *m�Ի�;
	tԲ�� m��ײ��, m������;
	int m������;
	int m�ж����;
};

}