#include "����.h"
#include "�ӵ�����.h"
#include "��Ϸ.h"
#include "ͼ������.h"
#include "����.h"
namespace ����ɽկ {
//==============================================================================
// �ӵ�
//==============================================================================
void C�ӵ�::f����_ʹ��() {
	this->f�ӿ�_��ʼ��();
	m��־[eʹ��] = true;
	m��־[e����] = true;
	m����ָ��->f�Ӽ���();
	//v��ʾ��� = v�ӵ���ʾ���.f�±��();
}
void C�ӵ�::f����_����() {
	assert(m��־[eʹ��]);	//��ֹ�ظ�����
	this->f�ӿ�_����();
	m��־.reset();
	m����ָ��->f������();
}
bool C�ӵ�::f����_iʹ��() const {
	return m��־[eʹ��];
}
void C�ӵ�::f����_�����˶�() {
	����::f�����˶�����(m����, m�ٶ�, m��Ϸ�ٶ�->fg��());
}
float C�ӵ�::f����_���㷽��() {
	if (!m�ٶ�.fi��()) {
		m���� = m�ٶ�.fg����r();
	}
	return m����;
}
bool C�ӵ�::f����_����() {
	if (m������� <= 0) {
		m������� = 1;
		return true;
	}
	return false;
}
t����2 C�ӵ�::f����_���㷽λ(const t����2 &a����) const {
	return m����.f���㷽λr(a����, m����);
}
bool C�ӵ�::f����_i��͸���ж�(float a��ֵ) const {
	return (m��ɫ[0].a <= a��ֵ) && (m��ɫ[1].a <= a��ֵ);
}
void C�ӵ�::f�ӿ�_��ʼ��() {
}
void C�ӵ�::f�ӿ�_������ʼ��(const S�ӵ����� &a) {
	m���� = a.m����;
	m�ٶ� = a.m�ٶ�;
	m��ɫ[0] = a.m��ɫ[0];
	m��ɫ[1] = a.m��ɫ[1];
	m���� = a.m�ٶ�.fg����r();
	m���� = a.m����;
}
void C�ӵ�::f�ӿ�_����() {
	f����_�����˶�();
}
void C�ӵ�::f�ӿ�_����() {
}
void C�ӵ�::f�ӿ�_��ʾ() const {
	auto &v��ͼ�� = C��Ϸ::fgͼ��().fg��ͼ��();
	v��ͼ��.f����Բ��(tԲ��(m����, 4));
}
void C�ӵ�::f�ӿ�_����() {
}
void C�ӵ�::f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &a�ж�) {
	if (a�ж�.f�ӵ�_�ύ�ж�(tԲ��{m����, c�ж��뾶})) {
		a�ж�.f�ӵ�_�ж���Ч();
		if (a�ж�.f�ӵ�_i��ײ()) {
			f����_����();
		}
	}
}
bool C�ӵ�::f�ӿ�_ը���ж�(C�ӵ������ը���ж� &a�ж�) {
	if (a�ж�.f�ӵ�_�ύ�ж�(m����, c�ж��뾶)) {
		a�ж�.f�ӵ�_��������(m����, m�ٶ�);
		m��־[eֹͣը���ж�] = true;
		f����_����();
		return true;
	}
	return false;
}
bool C�ӵ�::f�ӿ�_i�ڴ�����() {
	return C�߽�::c����.f����ж�(m����, 0);
}
bool C�ӵ�::f�ӿ�_����ʾ() const {
	return true;
}
bool C�ӵ�::f�ӿ�_iֹͣը���ж�() const {
	return m��־[eֹͣը���ж�];
}
//��ʼ��
void C�ӵ�::f��ʼ��_��ʽ(int a) {
	auto &va�ӵ����� = C��Ϸ::g��Դ.fg�ӵ�����();
	m�ӵ����� = va�ӵ�����.fgָ��(a);
}
void C�ӵ�::f��ʼ��_����(int) {

}
//����
void C�ӵ�::f����_��() {
	m��־[C�ӵ�::e����] = false;
}
void C�ӵ�::f����_ȡ������() {
	m��־[C�ӵ�::eȡ������] = true;
}
void C�ӵ�::f����_��ʧ(bool) {
	m��־.reset();
}
void C�ӵ�::f����_��ת(float a��) {
	m�ٶ�.fs��תd(a�� * m��Ϸ�ٶ�->fg��());
}
bool C�ӵ�::f����_����(float aС, float a��, float a�仯, float aʱ��) {
	assert(aС <= a��);
	const float v���� = m��Ϸ�ٶ�->fg��();
	const float v�仯 = a�仯 * aʱ�� * v����;
	float v��С = m�ٶ�.fg��С();
	const auto f�ٶȱ仯 = [&](float aĿ��)->bool {
		if (a�仯 > 0) {
			v��С = ��ѧ::f���Խ���<float>(v��С, aĿ��, v�仯);
			m�ٶ�.fs��С(v��С);
			return v��С == aĿ��;
		} else {
			m�ٶ�.fs��С(aĿ��);
			return true;
		}
	};
	if (v��С <= aС) {
		if (f�ٶȱ仯(aС)) {
			return true;
		}
	} else if (v��С >= a��) {
		if (f�ٶȱ仯(a��)) {
			return true;
		}
	}
	return false;
}
void C�ӵ�::f����_���ٶ�(float a����, float aʱ��) {
	const float v���� = m��Ϸ�ٶ�->fg��();
	m�ٶ� = m�ٶ�.fg��һ() * (m�ٶ�.fg��С() + a���� * aʱ�� * v����);
}
void C�ӵ�::f����_���ٶ�(const t����2 &a���ٶ�, float aʱ��) {
	const float v���� = m��Ϸ�ٶ�->fg��();
	m�ٶ� += a���ٶ� * aʱ�� * v����;
}
void C�ӵ�::f����_���ٶ�(float a����, float aʱ��) {
	const float v���� = m��Ϸ�ٶ�->fg��();
	const float v�仯�� = pow(a����, 1.f / aʱ�� * v����);
	m�ٶ� *= v�仯��;
}
int C�ӵ�::f����_��Ļ����(int a����, int a����, std::function<bool(int)> af�ж�) {
	int v���� = 0;
	if (v���� >= a����) {
		return v����;
	}
	const auto f = [&](int a����1, float &a����, float &a�ٶ�, const bool &a��, const float &a��Ļ��Χ) {
		const bool v�������� = a�� ? (a���� > a��Ļ��Χ) : (a���� < -a��Ļ��Χ);
		if ((a���� & a����1) && v�������� && (af�ж� ? af�ж�(a����1) : true)) {
			a���� = -a���� + (a�� ? 2 : -2) * a��Ļ��Χ;
			a�ٶ� = -a�ٶ�;
			++v����;
		}
	};
	f(e��, m����.x, m�ٶ�.x, false, c��Ļ��Χx);
	f(e��, m����.x, m�ٶ�.x, true, c��Ļ��Χx);
	if (v���� >= a����) {
		return v����;
	}
	f(e��, m����.y, m�ٶ�.y, false, c��Ļ��Χy);
	f(e��, m����.y, m�ٶ�.y, true, c��Ļ��Χy);
	return v����;
}
void C�ӵ�::f����_͸��(float aĿ��, float a�仯�ٶ�) {
	const float v���� = m��Ϸ�ٶ�->fg��();
	const float v�仯�ٶ� = a�仯�ٶ� * v����;
	m��ɫ[0].a = ��ѧ::f���Խ���<float>(m��ɫ[0].a, aĿ��, v�仯�ٶ�);
	m��ɫ[1].a = ��ѧ::f���Խ���<float>(m��ɫ[1].a, aĿ��, v�仯�ٶ�);
}
//==============================================================================
// �ӵ�����
//==============================================================================
float S�ӵ�����::f�ж�����(float aԭʼ, float a����, float a����) {
	return aԭʼ * a���� - a���� * sqrt(a����);
}
float S�ӵ�����::fg�ж�x(float x) const {
	return f�ж�����(m�ж�.x, m�ж�����.x, x);
}
float S�ӵ�����::fg�ж�y(float y) const {
	if (fiԲ��()) {
		return fg�ж�x(y);
	} else {
		return f�ж�����(m�ж�.y, m�ж�����.y, y);
	}
}
t����2 S�ӵ�����::fg�ж�(const t����2 &a����) const {
	return {fg�ж�x(a����.x), fg�ж�y(a����.y)};
}
float S�ӵ�����::fg��ʾx(float x) const {
	return m����->fg��() * x * 0.5f;
}
float S�ӵ�����::fg��ʾy(float y) const {
	return m����->fg��() * y * 0.5f;
}
t����2 S�ӵ�����::fg��ʾ(const t����2 &a����) const {
	return{fg��ʾx(a����.x), fg��ʾy(a����.y)};
}
bool S�ӵ�����::fiԲ��() const {
	return m�ж�.y <= 0;
}
bool S�ӵ�����::fi����() const {
	return m�ж�.y > 0;
}
//--------------------------------------------------------------------------------
// �ӵ�����
//--------------------------------------------------------------------------------
S�ӵ�����::S�ӵ�����(S�ӵ����� &aǰ, S�ӵ����� &a��, float a��ֵ) : 
	m֡{��ѧ::f��ֵ<float>(aǰ.m֡, a��.m֡, a��ֵ)} {
}
void S�ӵ�����::f��ʼ��() {
	m֡ = 0;
}
void S�ӵ�����::f����() {
	m֡ = ��ѧ::f���Խ���<float>(m֡, 1, c�ٶ�);
}
bool S�ӵ�����::fi���ڳ���() const {
	return m֡ < 1;
}
bool S�ӵ�����::fi������() const {
	return m֡ >= 1;
}
//--------------------------------------------------------------------------------
// �ӵ���ʧ
//--------------------------------------------------------------------------------
S�ӵ���ʧ::S�ӵ���ʧ(S�ӵ���ʧ &aǰ, S�ӵ���ʧ &a��, float a��ֵ) :
	m֡{��ѧ::f��ֵ<float>(aǰ.m֡, a��.m֡, a��ֵ)},
	mĿ��{��ѧ::f��ֵ<float>(aǰ.mĿ��, a��.mĿ��, a��ֵ)},
	m�ٶ�{��ѧ::f��ֵ<float>(aǰ.m�ٶ�, a��.m�ٶ�, a��ֵ)} {
}
void S�ӵ���ʧ::f��ʼ��(float a��ʼֵ) {
	m֡ = a��ʼֵ;
	mĿ�� = a��ʼֵ;
	m�ٶ� = 0;
}
void S�ӵ���ʧ::f����() {
	if (m֡ < mĿ��) {
		m֡ += m�ٶ�;
	}
}
void S�ӵ���ʧ::f��ʧ(float aĿ��) {
	mĿ�� = aĿ��;
	fs��ʧ�ٶ�(aĿ��);
}
void S�ӵ���ʧ::f������ʧ(float aĿ��) {
	mĿ�� += aĿ��;
	fs��ʧ�ٶ�(aĿ��);
}
void S�ӵ���ʧ::fs��ʧ�ٶ�(float a��) {
	if (a�� > 1) {
		m�ٶ� = c�ٶ� * (a�� + 1.f) / 2.f;
	} else {
		m�ٶ� = c�ٶ� * a��;
	}
}
bool S�ӵ���ʧ::fi��ʧ() const {
	return mĿ�� > 0;
}
bool S�ӵ���ʧ::fiȫ��ʧ() const {
	return mĿ�� >= 1;
}
bool S�ӵ���ʧ::fi����() const {
	return m֡ <= 0;
}
bool S�ӵ���ʧ::fi�����() const {
	return (mĿ�� < 1) && fi��û��ʧ();
}
bool S�ӵ���ʧ::fi������ʧ() const {
	return m֡ > 0;
}
bool S�ӵ���ʧ::fi�Ѿ���ʧ() const {
	return m֡ >= 1;
}
bool S�ӵ���ʧ::fi��û��ʧ() const {
	return m֡ < 1;
}

}