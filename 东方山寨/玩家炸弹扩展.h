#pragma once
#include "���ը������.h"
namespace ����ɽկ::���ը�� {
class Cȫ���嵯 : public C���ը�� {
public:
	static constexpr float c���뾶 = c��Ļ��Χr * 1.5f;
	Cȫ���嵯() = default;
	Cȫ���嵯(float, bool);
	void f�ӿ�_����() override;
	float f�ӿ�_g�ж��뾶() const override;
	bool f�ӿ�_i��������() const override;
private:	//��չ
	float m��ɢ�ٶ� = c���뾶;
	float m�뾶 = 0;
	float m���� = 1;
	bool m���� = false;
};
//������ը��
class C����¼ : public C���ը�� {
public:
	static constexpr float c�ж��뾶 = 128;
	static constexpr float c���� = 3;
	static constexpr float c�ٶ�y = 64;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʼ��(const S����ӵ����� &) override;
	float f�ӿ�_g�ж��뾶() const override;
	float m���� = c����;
};
}	//namespace ����ɽկ::���ը��