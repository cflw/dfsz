#include "����.h"
#include "��ս.h"
#include "��Ϸ.h"
#include "ͼ�ι���.h"
#include "�ؿ�.h"
#include "�л�����.h"
#include "ͼ��_̧��.h"
#include "��Ƶ����.h"
namespace ����ɽկ {
void C��ս����::f��ʼ��_����(C�ؿ����� &a) {
	m�ؿ����� = &a;
}
std::shared_ptr<C�ؿ��¼�״̬> C��ս����::f���¼�_(const std::shared_ptr<C��ս�¼�> &a) {
	mw���� = false;
	m���� = nullptr;
	a->m��ս = this;
	a->m�ؿ� = m�ؿ�����;
	m�¼� = a.get();
	std::shared_ptr<C�ؿ��¼�״̬> v�� = std::make_shared<C�ؿ��¼�״̬>(a);
	m�ؿ�����->f����¼�(v��);
	v��->m��ʼʱ�� = -1;
	return v��;
}
void C��ս����::f����() {
	if (m�¼� && m�¼�->m״̬->m��־[(int)E�ؿ��¼�״̬::e��ʼ��]) {	//��ʼ���˲��ܼ���
		//����ֵ
		for (auto &v : ma��) {
			if (v->fi����() && mw���� == false) {
				mw���� = true;
				m�¼�->f�¼�_��������(*v);
				f�¼�����();
			}
		}
		//ʱ��
		if (m���� > 0) {
			m���� -= c֡��;
		} else {
			mʱ�� -= c֡��;
			const float v�ذ� = floor(mʱ��);
			if (m�ذ� != v�ذ�) {
				m�ذ� = v�ذ�;
				auto &v��Ƶ = C��Ϸ::fg��Ƶ();
				auto &v���ſ��� = v��Ƶ.fg���ſ���();
				if (m�ذ� < c��ս����ʱ1) {
					static const tp���� v����ʱ1 = v��Ƶ.fg����()[L"����.��Ч.����ʱ1"];
					v���ſ���.f������Чl(*v����ʱ1);
				} else if (m�ذ� < c��ս����ʱ0) {
					static const tp���� v����ʱ0 = v��Ƶ.fg����()[L"����.��Ч.����ʱ0"];
					v���ſ���.f������Чl(*v����ʱ0);
				}
			}
			if (mʱ�� <= 0 && mw���� == false) {
				mw���� = true;
				mʱ�� = 0;
				m�¼�->f�¼�_ʱ�䵽();
				f�¼�����();
			}
		}
	}
}
void C��ս����::f��ս��ʼ(int a����) {
	fg��ս��־() = true;
	assert(m��Ѫ�� == nullptr);
	auto vͼ�ι��� = C��Ϸ::fg��Դ().f����_ͼ��();
	m��Ѫ�� = vͼ�ι���.f����ͼ��<C��Ѫ��>(a���� - 1);
	m��Ļʱ�� = vͼ�ι���.f����ͼ��<C��Ļʱ��>(mʱ��);
	mʱ�� = 10000;
	m���� = 10000;
}
void C��ս����::f��ս����() {
	fg��ս��־() = false;
	m��Ѫ��->f����_����();
	m��Ѫ�� = nullptr;
	m��Ļʱ��->f����_����();
	m��Ļʱ�� = nullptr;
	ma��.clear();
}
void C��ս����::f������ʼ(const std::wstring &a����, int a����) {

}
void C��ս����::f��������() {

}
void C��ս����::f�¼�����() {
	fʱ�䶳��(10000);
	m�¼�->f����_����();
	m�¼� = nullptr;
}
void C��ս����::fsʱ��(float a��, float a����) {
	mʱ�� = a��;
	fʱ�䶳��(a����);
	m��Ļʱ��->f����_������ɫ();
}
void C��ս����::fʱ�䶳��(float a����) {
	m���� = a����;
}
void C��ս����::f��Ѫ����һ() {
	m��Ѫ��->f��һ();
}
t��־::reference C��ս����::fg��ս��־() {
	return m�ؿ�����->m��־[C�ؿ�����::E��־::e��ս];
}
bool C��ս����::fg��ս��־() const {
	return m�ؿ�����->m��־[C�ؿ�����::E��־::e��ս];
}
void C��ս����::fs��(C�л� *p) {
	assert(p->m��־[C�л�::E��־::e��]);
	ma��.push_back(p);
}
void C��ս����::fs��(std::shared_ptr<C�л�> p) {
	fs��(p.get());
}
C�л� *C��ս����::fg��(int i) const {
	return ma��[i];
}
C�л� *C��ս����::fg����() {
	if (m����) {
		return m����;
	}
	//Ѱ�Ҷ���
	for (auto &v : ma��) {
		if (v->fi����()) {
			m���� = v;
			return m����;
		}
	}
	return nullptr;
}
}