#include "����.h"
#include "��Ϸ.h"
namespace ����ɽկ {
//==============================================================================
// �����ӿ�&�޶���
//==============================================================================
void I����::f�ӿ�_����() {
}
void I����::f�ӿ�_����() {
}
void I����::f�ӿ�_s������(void *) {
}
int I����::f�ӿ�_g�������() const {
	return 0;
}
void I����::f�ӿ�_����(const E�������� &, const t��������ֵ &) {
}
t����3 I����::f�ӿ�_g��ת() const {
	return t����3::c��;
}
t����3 I����::f�ӿ�_g����() const {
	return t����3::cһ;
}
float I����::f�ӿ�_g͸����() const {
	return 1;
}
const C��Ϸ�ٶ� *I����::f�ӿ�_g��Ϸ�ٶ�() const {
	return &C��Ϸ::g����.fg��Ϸ�ٶ�();
}
int I����::fg����ֵi(const t��������ֵ &p) {
	if (std::holds_alternative<int>(p)) {
		return std::get<int>(p);
	} else if (std::holds_alternative<float>(p)) {
		return (int)std::get<float>(p);
	} else {
		if (std::get<bool>(p)) {
			return 1;
		} else {
			return 0;
		}
	}
}
float I����::fg����ֵf(const t��������ֵ &p) {
	if (std::holds_alternative<float>(p)) {
		return std::get<float>(p);
	} else if (std::holds_alternative<int>(p)) {
		return (float)std::get<int>(p);
	} else {
		if (std::get<bool>(p)) {
			return 1;
		} else {
			return 0;
		}
	}
}
bool I����::fg����ֵb(const t��������ֵ &p) {
	if (std::holds_alternative<bool>(p)) {
		return std::get<bool>(p);
	} else if (std::holds_alternative<int>(p)) {
		return std::get<int>(p);
	} else {
		return std::get<float>(p);
	}
}
//==============================================================================
// ��ɫ����
//==============================================================================
//����
C��ɫ����::C����::C����(std::shared_ptr<S����> p):
	m����{p} {
}
I���� *C��ɫ����::C����::f�ӿ�_�½�() const {
	return new C��ɫ����(m����);
}
//��
C��ɫ����::C��ɫ����(std::shared_ptr<S����> p):
	m����{p},
	m��������{&p->m����},
	mĿ�귽��{&p->m����} {
}
void C��ɫ����::f�ӿ�_����() {
	const auto &v��Ϸ�ٶ� = C��Ϸ::fg����().fg��Ϸ�ٶ�();
	const float v��֡ = v��Ϸ�ٶ�.fg��Ⱦ֡();
	const float v���� = v��Ϸ�ٶ�.fg��Ⱦ��();
	const float v�仯֡ = m��������->m�仯�ٶ� * v��֡;
	const float vѭ��֡ = m��������->mѭ���ٶ� * v��֡;
	//����֡
	if (m�������� == mĿ�귽��) {	//��ͬ�ķ���
		const float &vѭ�� = m��������->mѭ��;
		const float &v֡�� = m��������->m֡��;
		if (m����֡ < vѭ��) {
			m����֡ += v�仯֡;
		} else {
			m����֡ += vѭ��֡;
		}
		if (m����֡ > v֡��) {
			m����֡ = vѭ��;
		}
	} else {	//��ͬ�ķ���
		if (mĿ�귽�� == &m����->m����) {
			const float &vѭ�� = m��������->mѭ��;
			if (m����֡ > vѭ��) {
				m����֡ = vѭ��;
			}
			m����֡ -= v�仯֡;
			if (m����֡ <= 0) {
				m�������� = mĿ�귽��;
			}
		} else {
			m�������� = mĿ�귽��;
			m����֡ = 0;
		}
	}
	//͸����
	if (m͸���� < 1) {
		m͸���� += 2 * v����;
	}
	if (m͸���� > 1) {
		m͸���� = 1;
	}
}
void C��ɫ����::f�ӿ�_����(const E�������� &a����, const t��������ֵ &aֵ) {
	switch (a����) {
	case E��������::e����:
		f����_����();
		break;
	case E��������::eˮƽ�ƶ�:
		f����_ˮƽ�ƶ�(I����::fg����ֵf(aֵ));
		break;
	case E��������::e͸����:
		f����_͸����(I����::fg����ֵf(aֵ));
		break;
	}
}
void C��ɫ����::f����_����() {
	mĿ�귽�� = &m����->m����;
}
void C��ɫ����::f����_ˮƽ�ƶ�(float a) {
	if (a < 0) {
		return f����_����();
	} else if (a > 0) {
		return f����_����();
	} else {
		return f����_����();
	}
}
void C��ɫ����::f����_����() {
	mĿ�귽�� = &m����->m����;
}
void C��ɫ����::f����_����() {
	mĿ�귽�� = &m����->m����;
}
void C��ɫ����::f����_͸����(float a) {
	m͸���� = a;
}
int C��ɫ����::f�ӿ�_g�������() const {
	return (int)m����֡ + m��������->m���;
}
t����3 C��ɫ����::f�ӿ�_g����() const {
	if (m��������->m����) {
		return {-1, 1, 1};
	} else {
		return t����3::cһ;
	}
}
float C��ɫ����::f�ӿ�_g͸����() const {
	return m͸����;
}
//==============================================================================
// ��ά�任����
//==============================================================================
C��ά�任����::C��ά�任����(float a��ת, const t����2 &a����, const tf���� &af����):
	m��ת{a��ת},
	m����{a����},
	mf����{af����} {
}
void C��ά�任����::f�ӿ�_����() {
	mf����(*this);
}
t����3 C��ά�任����::f�ӿ�_g��ת() const {
	return {0, 0, m��ת};
}
t����3 C��ά�任����::f�ӿ�_g����() const {
	return {m����.x, m����.y, 1};
}
//=============================================================================
// ��ά�任����
//=============================================================================
C��ά�任����::C��ά�任����(const t����3 &a��ת, const t����3 &a����, const tf���� &af����):
	m��ת{a��ת},
	m����{a����},
	mf����{af����} {
}
void C��ά�任����::f�ӿ�_����() {
	mf����(*this);
}
t����3 C��ά�任����::f�ӿ�_g��ת() const {
	return m��ת;
}
t����3 C��ά�任����::f�ӿ�_g����() const {
	return m����;
}

}