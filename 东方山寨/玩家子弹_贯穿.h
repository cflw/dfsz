#pragma once
#include "����ӵ�����.h"
namespace ����ɽկ {
namespace ����ӵ� {
class C�ᴩ : public C����ӵ� {
private:
	struct S״̬ : public C����Ϸ���� {
		t����2 *v������;
		t����2 v�������;	//����ڰ�����
		int v�������;
		int v�������;
		float v����;
		float v��ʧ;
		void fs�������(const t����2 &);
		t����2 fgʵ����() const;
	};
	C��̬����<S״̬> v״̬��;
	static const float c��������;
	static const float c��ʧ�ٶ�;
public:
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() override;
	void f�ӿ�_�л��ж�(C�л�������ӵ��ж� &) override;
	void f�ӿ�_����() override;
private:
	S״̬ &f��չ_״̬();
	t����2 fgĩ��();
};

}
}