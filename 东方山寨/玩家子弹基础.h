#pragma once
#include "��ѧ����.h"
#include "ͼ�ΰ���.h"
#include "����.h"
#include "��ѧ����.h"
#include "����_����.h"
#include "�ж�����_�л�������ӵ�.h"
namespace ����ɽկ {
class C���;
struct S����ӵ�����;
class C�л�;
struct S����ӵ�����;
struct S�������;
class C����ӵ� {
public:
	static constexpr float c�ж��뾶 = 4;
	static constexpr float c͸���� = 0.5f;
	static constexpr float c����͸���ȴﵽ���ʱ�� = 0.1f;
	enum E��־ {
		eʹ��,
		e���п�����,
		//ը��
		eը��,
		e��������,
		//�Զ���
		e�Զ���,
	};
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��() const;
	const S����ӵ����� &f����_g�ӵ�����() const;
	void f����_�����˶�();
	float f����_���㷽��();
	void f����_����ʱ��();
	C������״ f����_g�ж���״() const;
	bool f����_iը��() const;
	int f����_g�˺�() const;
	float f����_g����͸����() const;
	virtual void f�ӿ�_��ʼ��(const S����ӵ����� &);
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_��ʾ() const;
	virtual void f�ӿ�_��ʧ();
	virtual void f�ӿ�_�л��ж�(C�л�������ӵ��ж� &);
	virtual void f�ӿ�_���ел�(const C�л� &);
	virtual bool f�ӿ�_�ڴ�����();
	virtual float f�ӿ�_g�ж��뾶() const;
public:
	t����2 m����;
	t����2 m�ٶ�;
	t��־ m��־;
	C��� *m��� = nullptr;
	const S����ӵ����� *m�ӵ����� = nullptr;
	C������� *m����ָ�� = nullptr;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	float m���� = 0;
	float m����֡ = 0;
	float m���� = 0;
	t����2 m����;
};
struct S����ӵ����� {
	t����2 m�ж�;
	t����2 m֡��ߴ�;
	t����ָ��<tp����> m����;
	t����ָ��<tp����> m��ʧ����;
	t����ָ��<S�������> m����;
	t����ָ��<S�������> m��ʧ����;
	int m����֡�� = 0;
	int m��ʧ֡�� = 0;
	int m�˺� = 10;
};
}