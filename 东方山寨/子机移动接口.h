#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
class C���;
class C�ӻ�;
class I�ӻ��ƶ� {
public:
	virtual void f�ӿ�_����() = 0;
	virtual void f�ӿ�_��λ(int ����) = 0;	//�ӻ����������仯ʱ����
	virtual void f�ӿ�_�����(C��� &);
protected:
	void f��ʼ��_�����(C��� &);
	std::vector<C�ӻ�> *va�ӻ�;	//����ӻ�
	const t����2 *v�Ի�����;	//�Ի�����
	const int *v�ӻ�����;	//�ӻ�ʵʱ����
	const float *v���ٽ���;	//��ҵ��ٽ���
};
}