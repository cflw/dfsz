#pragma once
#include "����.h"
#include "����_����.h"
#include "ͼ������.h"
#include "ͼ�λ���.h"
namespace ����ɽկ {
//==============================================================================
// ͼ�ι���
//==============================================================================
struct Sͼ�β��� {
	t����2 m����;
	t����2 m�ٶ�;
	float m���� = 1;
	int mͼ�� = 0;
	t����ָ��<tp����> m����;
	t����ָ��<S�������> m����;
	t��־ m��־;	//�Զ���,�� Iͼ��::E��� �޹�
};
class Cͼ�ι��� {
public:
	typedef std::function<void(Cͼ�ι��� &)> tf����;
	class Cʵ�� {
	public:
		void f��ʼ��_����(const C��Ϸ�ٶ� &);
		void f��ʼ��_����(C��������<Iͼ��> &);
		void f����ͼ��(std::shared_ptr<Iͼ��>, Sͼ�β��� &);
		bool fi�п�() const;
		C��������<Iͼ��> *maͼ�� = nullptr;
		const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	};
	Cͼ�ι���(Cʵ��&);
	void fʵ��_����ͼ��(std::shared_ptr<Iͼ��>);
	template<typename t, typename...t����> std::shared_ptr<t> f����ͼ��(const t���� &...a����);
	template<typename t> std::shared_ptr<t> f����ͼ��(const I����<t> &);
public:
	Sͼ�β��� m����;
private:
	Cʵ�� *mʵ�� = nullptr;
};
//==============================================================================
// ͼ�ι���ģ��ʵ��
//==============================================================================
template<typename t, typename...t����> std::shared_ptr<t> Cͼ�ι���::f����ͼ��(const t���� &...a����) {
	static_assert(std::is_base_of<Iͼ��, t>::value, "����̳���Iͼ��");
	if (mʵ��->fi�п�()) {
		std::shared_ptr<t> vͼ�� = std::make_shared<t>(a����...);
		mʵ��->f����ͼ��(vͼ��, m����);
		return vͼ��;
	}
	return nullptr;
}
template<typename t> std::shared_ptr<t> Cͼ�ι���::f����ͼ��(const I����<t> &p) {
	static_assert(std::is_base_of<Iͼ��, t>::value, "����̳���Iͼ��");
	if (mʵ��->fi�п�()) {
		std::shared_ptr<t> vͼ�� = p.f�½�s();
		mʵ��->f����ͼ��(vͼ��, m����);
		return vͼ��;
	}
	return nullptr;
}
}	//namespace ����ɽկ