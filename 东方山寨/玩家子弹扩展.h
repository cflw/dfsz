#pragma once
#include "����.h"
#include "����ӵ�����.h"
#include "��Ϸ.h"
namespace ����ɽկ {
namespace ����ӵ� {
//==============================================================================
// �յ��ӵ�, �Զ����ٵл�
//==============================================================================
class C�յ� : public C����ӵ� {
private:
	static constexpr float c��ʼ���� = 2;
	static constexpr float c���ٶ� = ��ѧ::c����<float> / c����Ƶ��;
public:
	C�յ�();
	//�ӿ�
	void f�ӿ�_����() override;
private:	//��չ
	std::shared_ptr<C�л�> fѰ��Ŀ��();
	std::weak_ptr<C�л�> mĿ��;
	float m���� = c��ʼ����;	//�ӵ���������ڵ�ʱ��
	C��������<C�л�> *ma�л�;
};
//==============================================================================
// �ᴩ
//==============================================================================
class C�ᴩ : public C����ӵ� {
private:
	static constexpr float c�������� = c��Ļ��Χr * 2;
	static constexpr float c��ʧ�ٶ� = 4.f;
	static constexpr float c��ʧ��� = 1.f / 30.f;
public:
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�л��ж�(C�л�������ӵ��ж� &) override;
	void f�ӿ�_���ел�(const C�л� &) override;
	t����2 fgĩ��() const;
	void f����();
private:
	float m���� = 0;
	float m��ʧ = 0;
	float m��ʧʱ��� = -1;
};

}
}