#pragma once
#include "�ӵ�����.h"
namespace ����ɽկ {
class C���߼��� : public C�ӵ� {
public:
	static constexpr float cĬ�ϳ��� = 20;
	struct S�ڵ� {
		int m���;
		t����2 mԭ����;
		t����2 m����;
		t����2 m�ٶ�;
		float m����;
		t��ɫ m��ɫ;
		S�ӵ���ʧ m��ʧ;
		bool mi����;
		void f����(const t����2 &, const t����2 &, float, const t��ɫ &);
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
	void f��ʼ��_����(float);
	//����
	void f����_��ʧ(bool);
	//��չ
	S�ڵ� &f��չ_ȡ�ڵ�(int);
	const S�ڵ� &f��չ_ȡ�ڵ�(int) const;
	S�ڵ� &f��չ_ȡͷ�ڵ�();
	S�ڵ� &f��չ_ȡβ�ڵ�();
	void f��չ_����ͷ�ڵ�();
	void f��չ_�ڵ���ʧ(int);
	void f��չ_�ڵ���ʧ���();	//����нڵ���ʧ�͵������
	std::vector<S�ڵ�> &fѭ��_ȫ��();
	ѭ��::C��Χ<std::vector<S�ڵ�>> fѭ��_��Χ(int, int);
	ѭ��::C��ɢ<std::vector<S�ڵ�>> fѭ��_��Χ(int �ڵ����);
	//����
	float m��ʼ��_����, m��ʼ��_���, m��ʼ��_���� = 0.25f;
	std::vector<S�ڵ�> ma�ڵ�;
	S�ӵ����� m����;
	float m�����ʱ;
	float m��������;
	tp�ӵ�ͼ������ mͼ������;
};
}	//namespace ����ɽկ