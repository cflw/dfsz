#include "����ӵ�����_��ɢ.h"
#include "����.h"
namespace ����ɽկ {
namespace ����ӵ����� {
C��ɢ::S���� C��ɢ::S����::fc���(int a����, float a��ɢ0, float a��ɢ1, float a����0, float a����1) {
	return S����(a����, std::pair<float, float>(a��ɢ0, a��ɢ1), std::pair<float, float>(a����0, a����1));
}
C��ɢ::S���� C��ɢ::S����::fc��(int a����, float a��ɢ0, float a��ɢ1, float a����0, float a����1) {
	const float v���� = static_cast<float>(a����);
	return S����(
		a����, 
		std::pair<float, float>(a��ɢ0 / v����, a��ɢ1 / v����), 
		std::pair<float, float>(a����0 / v����, a����1 / v����)
	);
}
C��ɢ::S����::S����(int a����, std::pair<float, float> a��ɢ, std::pair<float, float> a���) :
	m����(a����),
	m�����ſ��Ƕ�(a��ɢ),
	mˮƽ������(a���) {
}
C��ɢ::C����::C����(const S���� &a����) :
	m����(std::make_shared<S����>(a����)) {
}
C����ӵ������� *C��ɢ::C����::f�ӿ�_�½�() const {
	return new C��ɢ(m����);
}
C��ɢ::C��ɢ(const std::shared_ptr<S����> &a����):
	m����(a����) {
}
void C��ɢ::f�ӿ�_�����ӵ�() {
	m�ӵ������->m����.m���� = m���价��->fg��������();
	m�ӵ������->m����.m�ٶ� = {0, c�ٶȴ�С};
	for (auto &vѭ�� : m�ӵ������->fѭ��(m����->m����)) {
		vѭ��.f�任ģ��_��ɢ(m���价��, m����->m�����ſ��Ƕ�, m����->mˮƽ������);
		m�ӵ������->f�����ӵ�<C����ӵ�>();
	}
}
//����
}
}