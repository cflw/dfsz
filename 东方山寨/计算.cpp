#include <math.h>
#include "����.h"
#include "����.h"
#include "��Ϸ.h"
namespace ����ɽկ {
namespace ���� {
float f��ֵ(const std::pair<float, float> &a��ֵ, float a��ֵ) {
	return ��ѧ::f��ֵ<float>(a��ֵ.first, a��ֵ.second, a��ֵ);
}
bool f��ʱ(float &p��ʱ, float p) {
	p��ʱ += c֡��;
	if (p��ʱ > p) {
		p��ʱ = 0;
		return true;
	} else {
		return false;
	}
}
float f�ӱ仯(float p�仯, float aʱ��) {
	return p�仯 * aʱ�� * (float)c֡��;
}
float f�˱仯(float p�仯, float aʱ��) {
	return pow(p�仯, 1 / aʱ�� / (float)c����Ƶ��);
}
float f����͸����(float aԭ͸��, float p����) {
	const float c���͸���� = 0.2f;
	float vĿ��͸�� = p���� / 128.f;
	if (vĿ��͸�� < c���͸����) {
		vĿ��͸�� = c���͸����;
	} else if (vĿ��͸�� > 1) {
		vĿ��͸�� = 1;
	}
	return ��ѧ::f��������(aԭ͸��, vĿ��͸��, 0.1f, 0.f, 1.f / 120.f);
}
void f�����˶�����(t����2 &a����, const t����2 &a�ٶ�, float aʱ��) {
	a���� += a�ٶ� * aʱ��;
}
float f��Ŀ��ʱ��(const t����2 &aԭ, const t����2 &aĿ��, float a�ٶ�) {
	const float v���� = aĿ��.f�������(aԭ);
	const float v֡ = v���� / a�ٶ�;
	return v֡ * (float)c֡��;
}
t����2 f��Ŀ���ٶ�(const t����2 &aԭ, const t����2 &aĿ��, float aʱ��) {
	if (aʱ�� <= c֡��) {
		return aĿ�� - aԭ;
	} else {
		return (aĿ�� - aԭ) / aʱ��;
	}
}
int fc�����ʶ() {
	static int v = 0;
	v -= 10000;
	return v;
}
}}	//�����ռ����
