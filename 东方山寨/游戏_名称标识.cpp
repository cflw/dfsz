#include "��Ϸ_���Ʊ�ʶ.h"
#include "��Ϸ.h"
#include "��ʶ.h"
namespace ����ɽկ {
int C���Ʊ�ʶ::f��������(const std::wstring &a����) {
	const auto &v���Ʊ�ʶ = C��Ϸ::g��Դ.fg���Ʊ�ʶ();
	if (auto v = v���Ʊ�ʶ.find(a����); v != v���Ʊ�ʶ.end()) {
		return v->second;
	} else {
		return 0;
	}
}
void C���Ʊ�ʶ::f�������Ʊ�ʶ(const std::wstring &a��, const std::wstring &a��) {
	auto &v���Ʊ�ʶ = C��Ϸ::g��Դ.fg���Ʊ�ʶ();
	v���Ʊ�ʶ[a��] = v���Ʊ�ʶ[a��];
}
C���Ʊ�ʶ::C���Ʊ�ʶ(const std::wstring &a����, int a��ʶ):
	m����(a����),
	m��(0),
	m��ʶ(std::make_shared<std::vector<int>>(3)),
	mi�ɴ���(!a����.empty()) {
	m��ʶ->at(0) = a��ʶ;
}
C���Ʊ�ʶ::C���Ʊ�ʶ(const std::wstring &a����, int a��ʶ, C���Ʊ�ʶ const *a��һ��) :
	m����(a����),
	m��(a��һ��->m�� + 1),
	m��ʶ(a��һ��->m��ʶ),
	mi�ɴ���(a��һ��->mi�ɴ��� && !a����.empty()) {
	if (m�� == m��ʶ->size()) {	//��С�Ĳ�
		m��ʶ->push_back(a��ʶ);
	} else {
		if (a��ʶ) {
			m��ʶ->at(m��) = a��ʶ;
		}
	}
	switch (m��) {
	case 0:	//ͬʱ���1,2��
		m��ʶ->at(1) = 0;
	case 1:
		m��ʶ->at(2) = 0;
	}
}
C���Ʊ�ʶ::C���Ʊ�ʶ(C���Ʊ�ʶ &&a��ʶ) :
	m����(std::move(a��ʶ.m����)),
	m��(a��ʶ.m��),
	m��ʶ(std::move(a��ʶ.m��ʶ)),
	mi�ɴ���(a��ʶ.mi�ɴ���){
	a��ʶ.m�� = -1;	//ֻ��Ϊ��ȷ������ʱֵ
}
C���Ʊ�ʶ::~C���Ʊ�ʶ() {
	//Ŀǰ�ı�ʶֻ��2��,������ڸ�С�Ĳ���Ѹ�С��ӵ��������
	if (m�� <= 0) {
		//0�����ʱֵ������
	} else if (m�� < 2) {
		++m��ʶ->at(m��);
	} else {	//��>=2
		if (m�� == m��ʶ->size() - 1) {	//���һ��,����
			++m��ʶ->at(m��);
		} else {	//�����ڶ���,[-1]�ӵ�[-2]��,ɾ��[-1],������
			m��ʶ->at(m��) += m��ʶ->back();
			m��ʶ->pop_back();
		}
	}
}
void C���Ʊ�ʶ::fs����(const std::wstring &a����) {
	m���� = a����;
}
C���Ʊ�ʶ C���Ʊ�ʶ::f������(const std::wstring &a����, int a��ʶ) const {
	C���Ʊ�ʶ v(m���� + L"." + a����, a��ʶ, this);
	if (v.mi�ɴ���) {
		v.f�������Ʊ�ʶ();
	}
	return v;
}
int C���Ʊ�ʶ::fg��ʶ() const {
	auto &v���Ʊ�ʶ = C��Ϸ::g��Դ.fg���Ʊ�ʶ();
	if (auto v�� = v���Ʊ�ʶ.find(m����); v�� != v���Ʊ�ʶ.end()) {
		return v��->second;
	} else {
		return 0;
	}
}
int C���Ʊ�ʶ::fg�����ʶ() const {
	return ����::f��ʶ(m��ʶ->at(0), m��ʶ->at(1), fg�ӱ�ʶ());
}
int C���Ʊ�ʶ::fg����ʶ() const {
	return  m��ʶ->at(1);
}
int C���Ʊ�ʶ::fg�ӱ�ʶ() const {
	int v�� = 0;
	for (auto i = m��ʶ->begin() + 2; i < m��ʶ->end(); ++i) {
		v�� += *i;
	}
	return v��;
}
void C���Ʊ�ʶ::f�������Ʊ�ʶ() const {
	auto &v���Ʊ�ʶ = C��Ϸ::g��Դ.fg���Ʊ�ʶ();
	if (v���Ʊ�ʶ.find(m����) == v���Ʊ�ʶ.end()) {
		v���Ʊ�ʶ[m����] = fg�����ʶ();
	}
}
}	//namespace ����ɽկ