#pragma once
#include <vector>
#include <memory>
#include "�ؿ�.h"
namespace ����ɽկ {
class C��ս�¼�;
class C�л�;
class C��Ѫ��;
class C��Ļʱ��;
class C��ս���� {
public:
	template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> f�¼�(const t���� &...);
	std::shared_ptr<C�ؿ��¼�״̬> f���¼�_(const std::shared_ptr<C��ս�¼�> &);
	void f��ʼ��_����(C�ؿ����� &);	//�������е���
	void f����();
	void f��ս��ʼ(int �¼�����);
	void f��ս����();
	void f������ʼ(const std::wstring &����, int ����);
	void f��������();
	void fsʱ��(float ��, float ���� = 1);
	void fʱ�䶳��(float ����);
	void f��Ѫ����һ();
	t��־::reference fg��ս��־();
	bool fg��ս��־() const;
	void fs��(C�л� *);
	void fs��(std::shared_ptr<C�л�>);
	C�л� *fg����();
	C�л� *fg��(int = 0) const;
private:
	void f�¼�����();
	C�ؿ����� *m�ؿ����� = nullptr;
	std::vector<C�л� *> ma��;
	std::shared_ptr<C��Ѫ��> m��Ѫ��;
	std::shared_ptr<C��Ļʱ��> m��Ļʱ��;
	C��ս�¼� *m�¼�;
	float mʱ��, m����, m�ذ� = 0;
	C�л� *m����;
	bool mw���� = false;	//��֤ ��������,ʱ�䵽 ֻ�ܵ�������һ��һ��
};
class C��ս�¼� : public C�ؿ��¼� {
public:
	virtual void f�¼�_��������(C�л� &) {}
	virtual void f�¼�_ʱ�䵽() {}
public:
	C��ս���� *m��ս;
	C�ؿ����� *m�ؿ�;
};
template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> C��ս����::f�¼�(const t���� &...a����) {
	static_assert(std::is_base_of<C��ս�¼�, t>::value, "����̳���C��ս�¼�");
	return f���¼�_(std::make_shared<t>(a����...));
}

}