#pragma once
#include "ͼ�ΰ���.h"
#include "��ѧ����.h"
#include "����.h"
#include "��ѧ����.h"
#include "����_����.h"
#include "�ж�����_�ӵ������ը��.h"
#include "�ж�����_�Ի����ӵ�.h"
#include "����.h"
#include "�ӵ������.h"
namespace ����ɽկ {
struct S�ӵ�����;
class I���ӵ�;
struct S�������;
class I�ӵ�ͼ������;
using tp�ӵ�ͼ������ = std::shared_ptr<I�ӵ�ͼ������>;
//==============================================================================
// �����ӵ�
//==============================================================================
class C�ӵ� : public I�¼� {
public:
	static constexpr float c�ж��뾶 = 1;
	static constexpr float c͸����ֵ = 0.9f;
	enum E��־ {
		eʹ��,
		e�޵�,
		eȡ������,	//��"I�¼�::f�¼�_��ʼ��"�е���"C�ӵ�::f��ʼ��_ȡ������"
		e����,	//�����Ƿ����"I�¼�::f�¼�_ִ��"
		eֹͣը���ж�,
		e�Զ���
	};
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��() const;
	//�ӵ�����
	void f����_�����˶�();	//����չ����
	float f����_���㷽��();	//����չ����
	bool f����_����();	//����Ϸ����
	t����2 f����_���㷽λ(const t����2 &) const;
	bool f����_i��͸���ж�(float = c͸����ֵ) const;
	//�ӵ���չ�Ľӿ�
	template<typename t> static void f�ӿ�_�������ͳ�ʼ��(const std::shared_ptr<t> &);
	virtual void f�ӿ�_��ʼ��();
	virtual void f�ӿ�_������ʼ��(const S�ӵ����� &);
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_��ʾ() const;
	virtual void f�ӿ�_����();	//ֻ��ͨ��C�ӵ�::f����()����
	virtual void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &);
	virtual bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &);//��ը�������е���
	virtual bool f�ӿ�_i�ڴ�����();
	virtual bool f�ӿ�_����ʾ() const;
	virtual bool f�ӿ�_iֹͣը���ж�() const;
	//���¼������е��õĳ�ʼ������
	void f��ʼ��_��ʽ(int);
	void f��ʼ��_����(int);
	//�ӵ�����
	void f����_��();
	void f����_ȡ������();
	void f����_��ʧ(bool);	//[��Ҫ����]
	void f����_��ת(float);
	bool f����_����(float, float, float, float = 1);
	void f����_���ٶ�(float, float = 1);
	void f����_���ٶ�(const t����2 &, float = 1);
	void f����_���ٶ�(float, float = 1);
	int f����_��Ļ����(int p����, int p���� = 1, std::function<bool(int)> p�ж� = nullptr);
	void f����_͸��(float, float = 1);
	//�ڲ�ʹ�ñ���
	C������� *m����ָ��;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ�;
	I���ӵ� *m����;
	const S�ӵ����� *m�ӵ�����;
	int m��ʼ��_��ʽ = -1;
	int m��ʼ��_���� = -1;
	//�ⲿʹ�ñ���
	t��־ m��־;
	float m����֡;
	float m����;
	float m�������;
	int m��ʾ���;
	//float m͸���� = 1;	//TODO���ƻ���
	//����ʹ�ñ���
	t����2 m����;
	t����2 m�ٶ�;
	t����2 m����;
	t��ɫ m��ɫ[2];
};
template<typename t> void C�ӵ�::f�ӿ�_�������ͳ�ʼ��(const std::shared_ptr<t> &) {
}
//==============================================================================
// �ӵ�ʹ�õĽṹ
//==============================================================================
struct S�ӵ����� {
	static float f�ж�����(float ԭʼ, float ����, float ����);
	float fg�ж�x(float = 1) const;
	float fg�ж�y(float = 1) const;
	t����2 fg�ж�(const t����2 &) const;
	float fg��ʾx(float = 1) const;
	float fg��ʾy(float = 1) const;
	t����2 fg��ʾ(const t����2 &) const;
	bool fiԲ��() const;
	bool fi����() const;
	t����2 m�ж�;
	t����2 m�ж�����;
	t����ָ��<tp����> m����;
	t����ָ��<S�������> m����;
	int m����֡��;
};
struct S�ӵ����� {
	static constexpr float c�ٶ� = 4 * c֡��;
	S�ӵ�����() = default;
	S�ӵ�����(S�ӵ�����&, S�ӵ�����&, float);
	void f��ʼ��();
	void f����();
	bool fi���ڳ���() const;
	bool fi������() const;
	float m֡;
};
struct S�ӵ���ʧ {
	static constexpr float c�ٶ� = 2 * c֡��;
	S�ӵ���ʧ() = default;
	S�ӵ���ʧ(S�ӵ���ʧ&, S�ӵ���ʧ&, float);
	void f��ʼ��(float = 0);
	void f����();
	void f��ʧ(float Ŀ�� = 1);
	void f������ʧ(float);
	void fs��ʧ�ٶ�(float ��);
	bool fi��ʧ() const;	//Ŀ�ꣾ0
	bool fiȫ��ʧ() const;	//Ŀ���1
	bool fi����() const;
	bool fi�����() const;	//Ŀ�꣼1 �� ֡��1
	bool fi������ʧ() const;	//֡��0
	bool fi�Ѿ���ʧ() const;	//֡��1
	bool fi��û��ʧ() const;
	float m֡;
	float mĿ��;
	float m�ٶ�;
};
}	//namespace ����ɽկ