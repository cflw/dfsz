#pragma once
#include "��ѧ����.h"
#include "����.h"
#include "����_����.h"
namespace ����ɽկ {
enum class Eͼ�� {
	e�ײ� = 0,
	e�л� = 10,
	e��� = 20,
	e���� = 30,
	eͼ�� = 50,
	e�ӵ� = 60,
	ȩ�� = 100,
	e���� = 700,
};
struct Sͼ�β���;
//=============================================================================
// ͼ�ζ���
//=============================================================================
class Iͼ�� {
public:
	enum E��־ {
		eʹ��,
		e����,
		e�Զ���,
	};
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_��ʾ() const = 0;
	virtual void f�ӿ�_��ʼ��(const Sͼ�β��� &);
	virtual bool f�ӿ�_i������() const;
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��();
	void f����_����();//ͼ��ֱ����ʧ
public:
	int m�� = 0;
	int m��ʾ��� = 0;
	t��־ m��־;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	C������� *m����ָ�� = nullptr;
};
class I���� : public Iͼ�� {
public:
	void f�ӿ�_��ʼ��(const Sͼ�β��� &) override;
	bool f�ӿ�_i������() const override;
	void f����_�˶�();
	void f����_����();
	float fg�����ٷֱ�() const;
	float fg�������ٷֱ�() const;
	bool fi����() const;
public:
	t����2 m����;
	t����2 m�ٶ�;
	float m����;	//�̶�
	float m���� = 0;	//����ʱ��
};
//=============================================================================
// Ԥ��ͼ��
//=============================================================================
namespace ͼ�� {
class CԲ�� : public I���� {
public:
	CԲ��() = default;
	CԲ��(float, float);
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	float fg��ǰ�뾶() const;
public:
	float m��ʼ�뾶 = 0;
	float m�����뾶 = 100;
};
}
}