#include "����.h"
#include "��Ϸ.h"
#include "��ѧ����.h"
#include "�л�����.h"
#include "����.h"
#include "ͼ������.h"
namespace ����ɽկ {
//==============================================================================
// �л���
//==============================================================================
C�л�::C�л�(int p) :
	m����ֵ(p) {
}
void C�л�::f����_ʹ��() {
	m��־[eʹ��] = true;
	m����ָ��->f�Ӽ���();
}
void C�л�::f����_����() {
	assert(m��־[eʹ��]);	//��ֹ�ظ�����
	this->f�¼�_����();
	m��־.reset();
	m����ָ��->f������();
}
bool C�л�::f����_iʹ��() const {
	return m��־[eʹ��];
}
void C�л�::f��ʼ��() {
}
void C�л�::f����() {
	const float v֡�� = m��Ϸ�ٶ�->fg��();
	if (m�޵�ʱ�� > 0) {
		m�޵�ʱ�� -= v֡��;
	}
	f�����˶�();
	m����->f�ӿ�_����(E��������::eˮƽ�ƶ�, ��ѧ::fȡ����<float>(m�ٶ�.x, 1));
	m����->f�ӿ�_����();
}
void C�л�::f����() {
	m����->f�ӿ�_����();
}
void C�л�::f��ʾ() const {
	if (fi����()) {
		f��ʾͼƬ();
	} else {
		auto &v��ͼ = C��Ϸ::fgͼ��().fg��ͼ��();
		v��ͼ.f����Բ��(tԲ��(m����, 16));
	}
}
bool C�л�::fi�ڴ�����() const {
	return C�߽�::c����.f����ж�(m����, 32);
}
void C�л�::f�е�(int p�˺�) {
	//�޵�ʱ��������˺�
	if (m�޵�ʱ�� <= 0) {
		if (m����ֵ.m��ǰ > 0) {
			m����ֵ.m��ǰ -= p�˺�;
		}
	}
}
//ȡֵ
bool C�л�::fi����() const {
	return m����ֵ.m��ǰ <= 0;
}
bool C�л�::fi��() const {
	return m��־[E��־::e��];
}
const t����2 &C�л�::fg����() const {
	return m����;
}
const SͼƬ�������� &C�л�::fgͼƬ��������() const {
	return *m�л�����;
}
float C�л�::fg�ж��뾶() const {
	return m�л����� ? m�л�����->m�ж��뾶 : c�ж��뾶;
}
tԲ�� C�л�::fg�ж���() const {
	return {m����, fg�ж��뾶()};
}
const S������� &C�л�::fg�������() const {
	const auto &v���� = m�л�����->m����.mָ��;
	return v����[m����->f�ӿ�_g�������()];
}
float C�л�::fg�ƶ�����x() const {
	return ��ѧ::fȡ����<float>(m�ٶ�.x);
}
float C�л�::fg�ƶ�����y() const {
	return ��ѧ::fȡ����<float>(m�ٶ�.y);
}
bool C�л�::fi�˶�ʱ����(float aʱ��) const {
	return m�˶�ʱ�� < aʱ��;
}
float C�л�::fʣ���˶�ʱ��(float aʱ��) const {
	return aʱ�� - m�˶�ʱ��;
}
//����
void C�л�::f�����˶�() {
	const float v���� = m��Ϸ�ٶ�->fg��();
	if (mf�˶�) {
		m�ٶ� = mf�˶�(*this);
	}
	m�˶�ʱ�� += v����;
	����::f�����˶�����(m����, m�ٶ�, v����);
}
void C�л�::fֱ���ƶ�(const t����2 &aĿ��, float aʱ��) {
	m�ٶ� = ����::f��Ŀ���ٶ�(m����, aĿ��, aʱ��);
}
//��ʼ��
void C�л�::fs����ֵ(int a����ֵ, float a�޵�ʱ��) {
	m����ֵ.f����(a����ֵ);
	m�޵�ʱ�� = a�޵�ʱ��;
}
//�˶�
void C�л�::fs�ٶ�(const t����2 &a�ٶ�) {
	m�ٶ� = a�ٶ�;
	mf�˶� = nullptr;
}
void C�л�::fs�˶�(const tf�˶� &af�˶�) {
	mf�˶� = af�˶�;
	m�˶�ʱ�� = 0;
}
void C�л�::f�˶�_�ٶ�(const t����2 &a�ٶ�, float aʱ��) {
	if (aʱ�� > 0) {
		fs�˶�(F�л��˶�_ֱ���ٶ�(a�ٶ�, aʱ��));
	} else {
		fs�ٶ�(a�ٶ�);
	}
}
void C�л�::f�˶�_��ʱ�ƶ���(const t����2 &aĿ��, float aʱ��, float aƽ����ʼ, float aƽ������) {
	if (aƽ����ʼ != 0 || aƽ������ != 0) {
		f�˶�_ƽ���ƶ���(aĿ��, aʱ��, aƽ����ʼ, aƽ������);
	} else {
		fs�˶�(F�л��˶�_Ŀ������(aĿ��, aʱ��));
	}
}
void C�л�::f�˶�_�����ƶ���(const t����2 &aĿ��, float a�ٶ�, float aƽ����ʼ, float aƽ������) {
	if (aƽ����ʼ != 0 || aƽ������ != 0) {
		const float vʱ�� = aĿ��.fg��С() / a�ٶ�;
		f�˶�_ƽ���ƶ���(aĿ��, vʱ��, aƽ����ʼ, aƽ������);
	} else {
		fs�˶�(F�л��˶�_Ŀ������(aĿ��, m����.f�������(aĿ��) / a�ٶ�));
	}
}
void C�л�::f�˶�_��ʱ�ƶ���(const t����2 &aĿ��, float aʱ��, float aƽ����ʼ) {
	if (aƽ����ʼ != 0) {
		f�˶�_ƽ���ƶ���(aĿ��, aʱ��, aƽ����ʼ);
	} else {
		fs�ٶ�((aĿ�� - m����) / aʱ��);
	}
}
void C�л�::f�˶�_�����ƶ���(const t����2 &aĿ��, float a�ٶ�, float aƽ����ʼ) {
	if (aƽ����ʼ != 0) {
		const float vʱ�� = aĿ��.fg��С() / a�ٶ�;
		f�˶�_ƽ���ƶ���(aĿ��, vʱ��, aƽ����ʼ);
	} else {
		fs�ٶ�(t����2::fc����r(a�ٶ�, m����.f���㷽��r(aĿ��)));
	}
}
void C�л�::f�˶�_ƽ���ƶ���(const t����2 &aĿ��, float a��ʱ��, float aƽ����ʼ, float aƽ������) {
	const float v���� = m����.f���㷽��r(aĿ��);
	const float v���� = m����.f�������(aĿ��);
	const float v����ʱ�� = a��ʱ�� - aƽ����ʼ - aƽ������;
	const float v�ٶ� = v���� / (0.5f * aƽ����ʼ + 0.5f * aƽ������ + v����ʱ��);
	fs�˶�(F�л��˶�_ƽ���ƶ���(t����2::fc����r(v�ٶ�, v����), a��ʱ��, aƽ����ʼ, aƽ������));
}
void C�л�::f�˶�_ƽ���ƶ���(const t����2 &aĿ��, float a��ʱ��, float aƽ����ʼ) {
	const float v���� = m����.f���㷽��r(aĿ��);
	const float v���� = m����.f�������(aĿ��);
	const float v����ʱ�� = a��ʱ�� - aƽ����ʼ;
	const float v�ٶ� = v���� / (0.5f * aƽ����ʼ + v����ʱ��);
	fs�˶�(F�л��˶�_ƽ���ƶ���(t����2::fc����r(v�ٶ�, v����), a��ʱ��, aƽ����ʼ));
}
void C�л�::f�˶�_��Ժ���������ƶ�(float a������, float a��ƽ��, float a�ḡ��, float a��ƽ��, float a�ݸ���) {
	constexpr float c�ƶ���ʱ�� = 1.5f;
	constexpr float c�ƶ���ʼ = 0.5f;
	constexpr float c�ƶ����� = 0.5f;
	auto v���� = C��Ϸ::fg����().f����_���������(m���);
	const auto v�ݷֲ� = std::uniform_real_distribution<float>(a��ƽ�� - a�ݸ���, a��ƽ�� + a�ݸ���);
	const float v��λ��0 = v�ݷֲ�(v����);
	const float v�ݲ� = v��λ��0 - m����.y;
	const float v��λ��1 = (abs(v�ݲ�) > a��ƽ��) ? (m����.y + ��ѧ::fȡ����(v�ݲ�) * a��ƽ��) : v��λ��0;
	if (a������ == m����.x) {
		const auto v��ֲ� = std::uniform_real_distribution<float>(-a��ƽ��, a��ƽ��);
		const float v���ƶ� = v��ֲ�(v����);
		const float v��λ�� = m����.x + v���ƶ�;
		f�˶�_ƽ���ƶ���({v��λ��, v��λ��1}, c�ƶ���ʱ��, c�ƶ���ʼ, c�ƶ�����);
	} else {
		const auto v��ֲ� = std::uniform_real_distribution<float>(a��ƽ�� - a�ḡ��, a��ƽ�� + a�ḡ��);
		const float v���ƶ� = v��ֲ�(v����);
		const float v��λ�� = m����.x + ��ѧ::fȡ����(a������ - m����.x) * v���ƶ�;
		f�˶�_ƽ���ƶ���({v��λ��, v��λ��1}, c�ƶ���ʱ��, c�ƶ���ʼ, c�ƶ�����);
	}
}
//����
void C�л�::f����_����() {
	m��־[e�޶���] = true;
}
void C�л�::f����_����() {
	this->f�¼�_����();
	this->f����_����();
}
//==============================================================================
// �л��˶�
//==============================================================================
C�л�::tf�˶� F�л��˶�_ֱ���ٶ�(const t����2 &a�ٶ�, float aʱ��) {
	return [=](const C�л� &a�л�)->t����2 {
		return a�л�.fi�˶�ʱ����(aʱ��) ? a�ٶ� : t����2::c��;
	};
}
C�л�::tf�˶� F�л��˶�_Ŀ������(const t����2 &aĿ��, float aʱ��) {
	return [=](const C�л� &a�л�)->t����2 {
		const float vʣ��ʱ�� = a�л�.fʣ���˶�ʱ��(aʱ��);
		const t����2 v����� = aĿ�� - a�л�.m����;
		return (vʣ��ʱ�� >= c֡��) ? (v����� / vʣ��ʱ��) : v�����;
	};
}
C�л�::tf�˶� F�л��˶�_ƽ���ƶ���(const t����2 &a����ٶ�, float a��ʱ��, float aƽ����ʼ, float aƽ������) {
	const float v���ٽ����� = a��ʱ�� - aƽ������;
	assert(a��ʱ�� - aƽ����ʼ - aƽ������ >= 0);	//�����˶�ʱ��Ҫ����0
	return [=](const C�л� &a�л�)->t����2 {
		const float v�˶�ʱ�� = a�л�.m�˶�ʱ��;
		if (v�˶�ʱ�� < aƽ����ʼ) {	//ƽ����ʼ
			return ��ѧ::f��ֵ<t����2>(t����2::c��, a����ٶ�, v�˶�ʱ�� / aƽ����ʼ);
		} else if (v�˶�ʱ�� < v���ٽ�����) {	//����
			return a����ٶ�;
		} else if (v�˶�ʱ�� < a��ʱ��) {	//ƽ������
			return ��ѧ::f��ֵ<t����2>(a����ٶ�, t����2::c��, (v�˶�ʱ�� - v���ٽ�����) / aƽ������);
		} else {	//ֹͣ�ƶ�
			return t����2::c��;
		}
	};
}
C�л�::tf�˶� F�л��˶�_ƽ���ƶ���(const t����2 &a����ٶ�, float a��ʱ��, float aƽ����ʼ) {
	assert(a��ʱ�� - aƽ����ʼ >= 0);
	return [=](const C�л� &a�л�)->t����2 {
		const float v�˶�ʱ�� = a�л�.m�˶�ʱ��;
		if (v�˶�ʱ�� < aƽ����ʼ) {
			return ��ѧ::f��ֵ<t����2>(t����2::c��, a����ٶ�, v�˶�ʱ�� / aƽ����ʼ);
		} else {
			return a����ٶ�;
		}
	};
}

}	//namespace ����ɽկ