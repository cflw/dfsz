#pragma once
#include "��Ƶ����.h"
#include "����_����.h"
namespace ����ɽկ {
class C��������;
class C���ſ���;
//��Ƶ����
class C��Ƶ���� {
public:
	void f��ʼ��();
	void f����();
	void f����();
	C�������� &fg��������();
	C���ſ��� &fg���ſ���();
	C��������<tp����> &fg����();
	std::unique_ptr<��Ƶ::C��Ƶ> m��Ƶ;
	std::unique_ptr<C���ſ���> m���ſ���;
	std::unique_ptr<C��������> m��������;
	C��������<tp����> ma����;
};
//���ſ���
class C���ſ��� {
public:
	enum E��� {
		e��Чs,
		e��Чm,
		e��Чl,
		e����,
		e����,
	};
	static constexpr float c���ż�� = 1.f / 60.f;
	static constexpr float c��Чs = 0.25f;
	static constexpr float c��Чm = 0.5f;
	static constexpr float c��Чl = 1;
	void f��ʼ��_�ӿ�(��Ƶ::C��Ƶ &);
	void f����();
	void f����();
	void f������Чs(const ��Ƶ::C���� &);
	void f������Чm(const ��Ƶ::C���� &);
	void f������Чl(const ��Ƶ::C���� &);
	void f��������(const ��Ƶ::C���� &);
	void fs��Ч����(float);
	void fs��������(float);
	float fg��Ч����() const;
	float fg��������() const;
	��Ƶ::C��Ƶ *m��Ƶ = nullptr;
	std::unique_ptr<��Ƶ::C���ſ���> m����;
	��Ƶ::tp���� m���� = 0;
	tp��� ma���[e����] = {};
};
//��������
class C�������� {
public:
	void f��ʼ��_�ӿ�(��Ƶ::C��Ƶ &);
	void f��ʼ��_����(C��������<tp����> &);
	tp���� f��������(int ��ʶ, const std::wstring &);
	��Ƶ::C��Ƶ *m��Ƶ = nullptr;
	C��������<tp����> *ma���� = nullptr;
};
}