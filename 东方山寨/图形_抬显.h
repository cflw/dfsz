#pragma once
#include "ͼ�ΰ���.h"
#include "ͼ�λ���.h"
#include "����.h"
namespace ����ɽկ {
class C�л�;
struct S�ؿ�����;
//=============================================================================
// ����
//=============================================================================
class C�ؿ����� : public I���� {
public:
	static constexpr float c���ֺ� = ��ά::ca�����ֺ�[��ά::e����];
	static constexpr float cС�ֺ� = ��ά::ca�����ֺ�[��ά::e���];
	C�ؿ�����(const S�ؿ����� &);
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
public:
	��ά::tp�ı����� m����;
};

//=============================================================================
// Ѫ��
//=============================================================================
class C��Ѫ�� : public Iͼ�� {
public:
	static constexpr float c�仯�ٶ� = 0.5f; 
	static constexpr float c�߿� = 4;
	static constexpr float c��� = 2;	//ÿ��֮����һ��հ�
	static constexpr float c�� = -c�߿�Χx;
	static constexpr float c�� = c�߿�Χx + c���;
	static constexpr float c�ܳ��� = 2 * c�߿�Χx + c���;
	C��Ѫ��(int);
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	bool f�ӿ�_i������() const override;
	void f��һ();
private:
	��ά::tp��ȾĿ�� m��ȾĿ��;
	��ά::tp��ɫ���� m����;
	int m����, m��ǰ;
	float m��ʾ, mʵ��;	//�ٷֱ�
};
class C��Ѫ�� : public Iͼ�� {	//Բ��Ѫ��
public:
	static constexpr float c�仯�ٶ� = 2.f;
	static constexpr float c�뾶 = 64;
	static constexpr float c�߿� = 4;
	static constexpr float c��Ȧ = c�뾶 + c�߿� / 2 + 2;
	static constexpr float c��Ȧ = c�뾶 - c�߿� / 2 - 2;
	static const ��ѧ::S��ɫ c��ɫ;
	C��Ѫ��(const C�л� &);
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	bool f�ӿ�_i������() const override;
private:
	��ά::tp��ȾĿ�� m��ȾĿ��;
	��ά::tp��ɫ���� m����;
	��ά::tp·������ m����;
	��ά::t��Բ m��Ȧ, m��Ȧ;
	t����2 m����;
	float m��ʾ, mʵ��;	//�ٷֱ�
	const C�л� *m�л�;	//���ٵĶ���
	bool mi���� = false;
};
//=============================================================================
// ��Ļʱ��
//=============================================================================
class C��Ļʱ�� : public Iͼ�� {
public:
	static constexpr float c�ֺ� = ��ά::ca�����ֺ�[��ά::eһ��];
	static constexpr float cС���ֺ� = c�ֺ� * 0.6f;
	static constexpr float c͸���� = 0.5f;
	static constexpr float c͸�����ٶ� = c͸���� * 2;
	static const t��ɫ c������ɫ, c������ɫ0, c������ɫ1;
	C��Ļʱ��(const float &);
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f����_������ɫ();
private:
	��ά::tp��ȾĿ�� m��ȾĿ��;
	��ά::tp��ɫ���� m����;
	��ά::tp�ı����� m����;
	��ά::tp�ı���ʽ m��ʽ;
	const float &mʵ��;
	float m��ʾ, m͸���� = 1;
};

}