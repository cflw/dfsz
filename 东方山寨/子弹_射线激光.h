#pragma once
#include "����_����.h"
#include "�ӵ�ͼ�νӿ�.h"
#include "�ӵ�����.h"
namespace ����ɽկ {
class C���߼��� : public C�ӵ� {
private:
	enum E��� {
		e�ƶ� = C�ӵ�::e�Զ���,
		eԤ����,
		e�仯_����,	//�ڵ����Ҫ��������
		e�仯_����,	//������Ҫ���¼���
		e�仯_ѭ��,	//ѭ���������¼���
	};
	struct S��ʧ�� : public C����Ϸ���� {	//��¼��ʧ�Ľڵ�
		int v���;
		int v�¸���;
		��ѧ::S��Χ<float> v��Χ;	//����Խ���뷢���ԽԶ
		S�ӵ���ʧ v��ʧ;
	};
	struct S����Ϣ;	//������ʱʹ��
	static const float c��ʧ�ΰ볤��;
	static const float c��������ٶ�;
	static const float cԤ���߿��;
	static const float cը���޵�ʱ��;
public:
	C���߼���() = default;
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_������ʼ��(const S�ӵ����� &) override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &) override;
	bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &) override;
	//��ʼ��
	void f��ʼ��_����(float = -1, float = -1);
	//����
	void f����_��ʧ(bool);
	void f����_Ԥ����(bool);
public:	//��չ
	t����2 f��չ_ȡ�̶��˵�(float, float = 1);
	float f��չ_g�ܳ�() const;
	t����2 f��չ_g�е�() const;
	t����2 f��չ_gԶ��() const;
	t����2 f��չ_g��(float) const;
	//��ʧ�εĲ���
	void f��ʧ��_�½�(float λ��, float �뾶 = 0);
	void f��ʧ��_����(S��ʧ�� &, int �ϸ���);
	void f��ʧ��_����();
	int f��ʧ��_����();
	//ѭ��
	ѭ��::C��ɢ<std::vector<S��ʧ��>> &fѭ��_��ʧ��();
private:
	float m��ʼ��_��, m��ʼ��_��;
	C��̬����<S��ʧ��> ma��ʧ��;
	int m��ʼ�� = -1;	//��ʾһ����ʧ�ε����
	int m���� = -1;
	float mը���޵�;	//����ը������һ���޵�ʱ��
	t����2 mĿ��;
	S�ӵ����� m����;
	S�ӵ���ʧ m��ʧ;
	ѭ��::C��ɢ<std::vector<S��ʧ��>> mѭ������_��ʧ��;
	C�ӵ�����::Cֱ��::ta���� ma�ڵ�;
	tp�ӵ�ͼ������ mͼ������;
};
}