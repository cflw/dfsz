#pragma once
#include "����_����.h"
#include "�ӵ�����.h"
namespace ����ɽկ {
class C���ӵ� : public C�ӵ� {
private:
	enum E�ڵ��� {
		e�ж�,
		e����,
	};
	struct S�ڵ� {
		t��־ m��־;
		int m���;
		S�ӵ���ʧ m��ʧ;
	};
	static const float cϸ�ְ뾶;
	static const float cϸ��ֱ��;
public:
	C���ӵ�() = default;
	C���ӵ�(float, float);
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_������ʼ��(const S�ӵ����� &) override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &) override;
	bool f�ӿ�_i�ڴ�����() override;
	bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &) override;
	//��ʼ��
	void f��ʼ��_����(float, float = -1);
	//����
	void f����_��ʧ(bool);
private:	//��չ
	std::pair<int, int> f��չ_�������Ƴ���(int, int);
	void f��չ_�ڵ���ʧ(int);
	void f��չ_�ڵ���ʧ���();	//����нڵ���ʧ�͵������
	S�ڵ� &f��չ_ȡ�ڵ�(int);
	const S�ڵ� &f��չ_ȡ�ڵ�(int) const;
	//�ڵ�����
	int f�ڵ�_gһά���(int, int);	//���ݶ�ά���ȡһά���
	std::pair<int, int> f�ڵ�_g��ά���(int);	//����һά���ȡ��ά���
	t����2 f�ڵ�_g�������(int);	//������ӵ�����
	t����2 f�ڵ�_g����(int);	//�������ȡ�ڵ�����
	int f�ڵ�_g�����Ӧ���(const t����2 &);	//��������ȡ�ڵ����
	float f�ڵ�_g��Է���(int);
	float f�ڵ�_g����(int);
	//ѭ��
	std::vector<S�ڵ�> &fѭ��_����();
	ѭ��::C��ɢ<std::vector<S�ڵ�>> &fѭ��_��Χ(int);
	//����
	static C��������<std::vector<bool>> ma�ڵ��ж�;
	float m��ʼ��_�� = 1, m��ʼ��_�� = 1;
	std::vector<S�ڵ�> ma�ڵ�;
	int m����, m����, m����;
	S�ӵ����� m����;
	int mѭ������_��Χ�ڵ���� = -1;
	ѭ��::C��ɢ<std::vector<S�ڵ�>> mѭ������_��Χ�ڵ�ѭ��;
	tp�ӵ�ͼ������ mͼ������;
};
}