#pragma once
#include "�ӵ�����.h"
namespace ����ɽկ {
class C��ͨ�ӵ� : public C�ӵ� {
public:
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &) override;
	bool f�ӿ�_i�ڴ�����() override;
	bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &) override;
	//����
	void f����_��ʧ(bool);
	//����
	S�ӵ����� m����;
	S�ӵ���ʧ m��ʧ;
	tp�ӵ�ͼ������ mͼ������;
};
}	//namespace ����ɽկ