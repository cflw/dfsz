#include "����.h"
#include "��ѧ����.h"
namespace ����ɽկ {
//=============================================================================
// �߽�
//=============================================================================
const C�߽� C�߽�::c�߿� = C�߽�::fc���ľ���(c�߿�Χx, c�߿�Χy);
const C�߽� C�߽�::c���� = C�߽�::fc���ľ���(c��Ļ��Χx, c��Ļ��Χy);
const C�߽� C�߽�::c�Ի� = C�߽�::fc���ľ���(c�ƶ���Χx, c�ƶ���Χy);
//����
C�߽�::C�߽�(float a��, float a��, float a��, float a��) :
	m��{a��}, m��{a��}, m��{a��}, m��{a��} {
}
C�߽� C�߽�::fc���ľ���(float x, float y) {
	return {-x, y, x, -y};
}
//����
float C�߽�::fg���() const {
	return m�� - m��;
}
float C�߽�::fg�߶�() const {
	return m�� - m��;
}
float C�߽�::fgб��() const {
	return hypot(fg���(), fg�߶�());
}
float C�߽�::fg����() const {
	return fg���() / 2;
}
float C�߽�::fg��߶�() const {
	return fg�߶�() / 2;
}
float C�߽�::fg��б��() const {
	return fgб��() / 2;
}
//�ж�
bool C�߽�::f����ж�(const t����2 &a����, float d) const {
	return a����.x < m�� - d;
}
bool C�߽�::f�ұ��ж�(const t����2 &a����, float d) const {
	return a����.x > m�� + d;
}
bool C�߽�::f�ϱ��ж�(const t����2 &a����, float d) const {
	return a����.y > m�� + d;
}
bool C�߽�::f�±��ж�(const t����2 &a����, float d) const {
	return a����.y < m�� - d;
}
bool C�߽�::f����ж�(const t����2 &a����, float d) const {
	return f����ж�(a����, d) || f�ұ��ж�(a����, d) || f�ϱ��ж�(a����, d) || f�±��ж�(a����, d);
}
//����
bool C�߽�::f�������(t����2 &a����, float d) const {
	const float v�߽� = m�� - d;
	if (a����.x < v�߽�) {
		a����.x = v�߽�;
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�ұ�����(t����2 &a����, float d) const {
	const float v�߽� = m�� + d;
	if (a����.x > v�߽�) {
		a����.x = v�߽�;
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�ϱ�����(t����2 &a����, float d) const {
	const float v�߽� = m�� + d;
	if (a����.y > v�߽�) {
		a����.y = v�߽�;
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�±�����(t����2 &a����, float d) const {
	const float v�߽� = m�� - d;
	if (a����.y < v�߽�) {
		a����.y = v�߽�;
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f��������(t����2 &a����, float d) const {
	return f�������(a����, d) || f�ұ�����(a����, d);
}
bool C�߽�::f��������(t����2 &a����, float d) const {
	return f�ϱ�����(a����, d) || f�±�����(a����, d);
}
bool C�߽�::f�߽�����(t����2 &a����, float d) const {
	return f�������(a����, d) || f�ұ�����(a����, d) || f�ϱ�����(a����, d) || f�±�����(a����, d);
}
//����
bool C�߽�::f��߷���(t����2 &a����, float d) const {
	const float v�߽� = m�� - d;
	if (a����.x < v�߽�) {
		a����.x = ��ѧ::f����(a����.x, v�߽�);
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�ұ߷���(t����2 &a����, float d) const {
	const float v�߽� = m�� + d;
	if (a����.x > v�߽�) {
		a����.x = ��ѧ::f����(a����.x, v�߽�);
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�ϱ߷���(t����2 &a����, float d) const {
	const float v�߽� = m�� + d;
	if (a����.y > v�߽�) {
		a����.y = ��ѧ::f����(a����.y, v�߽�);
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f�±߷���(t����2 &a����, float d) const {
	const float v�߽� = m�� - d;
	if (a����.y < v�߽�) {
		a����.y = ��ѧ::f����(a����.y, v�߽�);
		return true;
	} else {
		return false;
	}
}
bool C�߽�::f���ҷ���(t����2 &a����, float d) const {
	return f��߷���(a����, d) || f�ұ߷���(a����, d);
}
bool C�߽�::f���·���(t����2 &a����, float d) const {
	return f�ϱ߷���(a����, d) || f�±߷���(a����, d);
}
bool C�߽�::f�߽練��(t����2 &a����, float d) const {
	return f��߷���(a����, d) || f�ұ߷���(a����, d) || f�ϱ߷���(a����, d) || f�±߷���(a����, d);
}
//=============================================================================
// ������״
//=============================================================================
C������״::C������״(const t����2 &a����, const t����2 &a��ߴ�, float a����) : m����(a����), m��ߴ�(a��ߴ�), m����(a����), mi����(true) {}
C������״::C������״(const t����2 &a����, float a�뾶) : m����(a����), m��ߴ�(a�뾶, 0), m����(0), mi����(false) {}
C������״ C������״::fc�Զ�(const t����2 &a����, const t����2 &a�ж�, const t����2 &a����, float a����) {
	if (a�ж�.y > 0) {	//����
		return {a����, a�ж�.f������(a����), a����};
	} else {
		if (a����.fi�������()) {	//Բ��
			return {a����, a�ж�.x * a����.x};
		} else {	//����
			return {a����, t����2::fc��ͬ(a�ж�.x).f������(a����), a����};
		}
	}
}
C������״ C������״::fc���Բ(const t����2 &a����, const t����2 &a�ж�, const t����2 &a����) {
	const float v�ж�x = a�ж�.x * a����.x;
	const float v�ж�y = a�ж�.y * a����.y;
	const float v��� = std::max(v�ж�x, v�ж�y);
	return {a����, v���};
}
C������״ C������״::fc��СԲ(const t����2 &a����, const t����2 &a�ж�, const t����2 &a����) {
	const float v�ж�x = a�ж�.x * a����.x;
	const float v�ж�y = a�ж�.y * a����.y;
	const float v��С = std::max(v�ж�x, v�ж�y);
	return {a����, v��С};
}
bool C������״::f�ཻ�ж�(const tԲ�� &aԲ��) const {
	if (mi����) {
		return ��ѧ::fԲ����ת�����ཻ�ж�(aԲ��.m����, aԲ��.m�뾶, m����, m��ߴ�, m����);
	} else {
		return ��ѧ::fԲ���ཻ�ж�(aԲ��.m����, aԲ��.m�뾶, m����, m��ߴ�.x);
	}
}
bool C������״::fiԲ��() const {
	return !mi����;
}
bool C������״::fi����() const {
	return mi����;
}
tԲ�� C������״::fgԲ��() const {
	return tԲ��(m����, m��ߴ�.x);
}
t��ת���� C������״::fg��ת����() const {
	return t��ת����(m����, m��ߴ�, m����);
}
}	//namespace ����ɽկ