#pragma once
#include "����ӵ�����.h"
namespace ����ɽկ {
namespace ����ӵ� {
//�յ��ӵ�, �Զ����ٵл�
class C�յ� : public C����ӵ� {
private:
	struct S״̬ : public C����Ϸ���� {
		C�л� *vĿ��;
		float v����;	//�ӵ���������ڵ�ʱ��
	};
	C��̬����<S״̬> v״̬��;
	C��̬����<C�л�> *va�л�;
	static const float c��ʼ����;
public:	//�ӿ�
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
private:	//��չ
	S״̬ &f��չ_״̬();
	C�л� *f��չ_Ѱ��Ŀ��();
};

}
}