#pragma once
#include "�����ӿ�.h"
namespace ����ɽկ {
class C����;
class C���߶��� : public I���� {
public:
	t����3 f�ӿ�_g����() const override;
	void f�ӿ�_s������(void *) override;
	void f�ӿ�_����() override;
	float f�ӿ�_g͸����() const override;
	const C��Ϸ�ٶ� *f�ӿ�_g��Ϸ�ٶ�() const override;
	C���� *m���� = nullptr;
	float m��ֵ = 0;
};
}