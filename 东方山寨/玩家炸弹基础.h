#pragma once
#include "����ӵ�����.h"
#include "����ӵ��������.h"
#include "�ж�����_�ӵ������ը��.h"
namespace ����ɽկ {
//���ը���ӿ�
class C���ը�� : public C����ӵ� {
public:
	static constexpr float c�ж��뾶 = 16;
	//ը���¼�
	void f�ӿ�_��ʾ() const override;	//�����ж��뾶��Բ
	float f�ӿ�_g�ж��뾶() const override;	//���������಻��Բ���ж��Ͳ�����д
	void f�ӿ�_�л��ж�(C�л�������ӵ��ж� &) override;	//������������Բ���ж��Ͳ�����д
	virtual void f�ӿ�_�ӵ��ж�(C�ӵ������ը���ж� &);	//������������Բ���ж��Ͳ�����д
	virtual bool f�ӿ�_i��������() const;
};
//���䲢����ը��
class C���ը�������� : public C����ӵ������� {
public:
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_����() override;
};
//��һ��x����һ��ը���ķ�����
template<typename t���ը��>
class C���ը���򵥷����� : public C���ը�������� {
public:
	void f�ӿ�_�����ӵ�() override {
		m�ӵ������->m����.m���� = m���价��->fg��������();
		m�ӵ������->f����ը��<t���ը��>();
	}
};
}