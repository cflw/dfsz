#pragma once
#include "����.h"
#include "����.h"
#include "ͼ�ΰ���.h"
#include "��ѧ����.h"
#include "ͼ�λ���.h"
#include "�Ի�����.h"
namespace ����ɽկ {
enum class E������� {
	e��
};
class C�Ի��� : public Iͼ�� {
public:
	static constexpr float c͸�����ٶ� = c֡�� / 0.25;
	static constexpr float c�߿� = 16;
	static constexpr float c��ʼλ��x = c�߿�Χx - 32;
	static constexpr float c��ʼλ��y = -96;	//����
	static constexpr float c�Ի���͸���� = 0.8f;
	C�Ի���(const S�Ի�����_�Ի� &);
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	bool f�ӿ�_i������() const override;
private:
	��ά::tp��ͼ�� m��ͼ��;
	��ά::tp���ı� m���ı�;
	��ά::tp�ı����� m�ı�����;
	��ά::tp�ı�Ч�� m�ı�Ч��;
	float m͸���� = 0;	//ͬʱ��ʾ�������
	float m�߿�ʵ�ʿ� = 0;
	float m�߿�ʵ�ʸ� = 0;
	float m�߿���ʾ�� = 0;
	bool m����;	//0����,1�ҵ���
};
class I�Ի����� : public Iͼ�� {
public:
	enum E��ʼ����� {
		e����,
	};
	enum E��� {
		e���� = Iͼ��::E��־::e�Զ���,
	};
	static constexpr float c��ʼλ��x = c�߿�Χx - 32;
	static constexpr float c��ʼλ��y = -32;	//����
	static constexpr float c�����ٶ� = 4;	//0.25�����
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;	//Ĭ�ϻ�����ɫ����
	bool f�ӿ�_i������() const override;
	void f�ӿ�_��ʼ��(const Sͼ�β��� &) override;
	virtual void f�ӿ�_�ı����(E�������);
	void f����_����(E�������);	//����f�ӿ�_�ı����
	void f����_�۽�();
	void f����_ʧ��();
protected:
	��ѧ::S����2 m����;	//����λ��
	float m����;
	float m����;	//���˵�����ǵ�ǰ����,Ϊ1
	bool m����;
};
}