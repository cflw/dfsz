#pragma once
#include <cflw����_ѭ��.h>
#include "ͼ�ΰ���.h"
#include "��ѧ����.h"
#include "����.h"
namespace ����ɽկ {
class Cͼ������;
using tpģ�� = const class Cģ��*;
//����
struct S��ά���� {
	��ѧ::S����3 m����;
	��ѧ::S����2 m����;
};
struct VS_3D {
	��ѧ::S����4 m����0;
	��ѧ::S����2 m����;
};
class Cģ�� {
public:
	Cģ��(const S��ά���� *, size_t, const uint16_t *, size_t);
	Cģ��(const Cģ�� &) = delete;
	Cģ��(Cģ�� &&);
	Cģ�� &operator =(const Cģ�� &) = delete;
	Cģ�� &operator =(Cģ�� &&);
	~Cģ��();
public:	//��Ա�����ڹ������֮��ֻ��
	S��ά���� *m����;
	uint16_t *m����;
	size_t m������, m������;
};
class C����ѭ�� : public ����::ѭ��::Iѭ��<C����ѭ��> {
public:
	static constexpr float c��λ�� = -20;
	static constexpr float cԶλ�� = 100;
	C����ѭ��(float �ƶ�, float ���, float �� = c��λ��, float Զ = cԶλ��);
	void fѭ������_����();
	bool fѭ������_i����() const;
	float fѭ������_������();
	float mλ��, m���, mԶ, m��;
};
class C����ά : public Iͼ�ι��� {
public:
	static constexpr size_t c���㻺������ = 1000;
	static constexpr size_t c������������ = 2000;
	C����ά(Cͼ������ &, ��ά::C��ά &);
	void f׼��() override;
	void fˢ��() override;
	void f���³�������();
	void fs�������(const ��ѧ::S����4 &);
	void fs��ͼ����(const ��ѧ::S����4 &);
	void fs�������(const ��ѧ::S����4 &);
	void fs���(const ��ѧ::S��� &);
	void fs����ɫ(const ��ѧ::S��ɫ &);
	void fs��Χ(float ��ʼ, float ��Χ);
	void fs����(��ά::tp����);
	void f��ģ��(const Cģ�� &);
	void f��ƽ��(int x, int y);
public:
	��ά::C��Ⱦ���� *m��Ⱦ����;
	struct S����v {
		��ѧ::S����4 m���� = ��ѧ::S����4::c��λ, m��ͼ = ��ѧ::S����4::c��λ, mͶӰ = ��ѧ::S����4::c��λ;
	} m����v;
	struct S����p {
		��ѧ::S����3 m�۾�λ�� = ��ѧ::S����3::c��;
		int32_t x0;	//���
		��ѧ::S��ɫ m����ɫ = ��ѧ::S��ɫ(0.0f, 0.0f, 0.0f, 1);
		float m��ʼ = 0, m��Χ = 1000;
	} m����p;
	��ѧ::S����4 m�������;
	��ά::tpͼ�ι��� mͼ�ι���;
	��ά::C�Զ����� m����;
	��ά::tp���� m����;
	����::C�ռ�<VS_3D> m����ռ�;
	��ά::tp���� m��������v, m��������p;
	��ά::tp������ m������;
	bool m����v = false, m����p = false;
};
}