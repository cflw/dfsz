#pragma once

#include "�ӵ�����.h"
namespace ����ɽկ {
class Cֱ�߼��� : public C�ӵ� {
public:
	struct S�ڵ� {
		S�ӵ���ʧ v��ʧ;
	};
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_������ʼ��(const S�ӵ����� &) override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &) override;
	bool f�ӿ�_i�ڴ�����() override;
	bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &) override;
	//��ʼ��
	void f��ʼ��_����(float, float = 1);
	//����
	void f����_��ʧ(bool);
	//��չ
	t����2 f��չ_ȡ�̶��˵�(float, float);
	t����2 f��չ_ȡ��ʾ�˵�(float);
	t����2 f��չ_ȡ�ж��˵�(float);
	t����2 f��չ_ȡ�ڵ�����(int);
	S�ڵ� &f��չ_ȡ�ڵ�(int);
	S�ڵ� &f��չ_ȡ��������ڵ�(const t����2 &);
	//����
	t����2 m��ʼ��_����;
	std::vector<S�ڵ�> ma�ڵ�;	//�Ӻ�ǰ
	S�ӵ����� m����;
	t����2 mĿ��;
	tp�ӵ�ͼ������ mͼ������;
};
}	//namespace ����ɽկ