#pragma once
#include "����.h"
#include "����_����.h"
#include "�л�����.h"
namespace ����ɽկ {
class C�л�;
class C��Ϸ�ٶ�;
//==============================================================================
// �л������
//==============================================================================
class C�л������ {
public:
	struct S���� {
		t����2 m����;
		t����2 m�ٶ�;
		t����2 mĿ��;
		int m����ֵ = 100;
		float m�ƶ�ʱ��;
		t����ָ��<S�л�����> m��ʽ;
		void fs����(const t����2 &);
		void fs�ٶ�(const t����2 &, float = -1);
		void fsĿ��(const t����2 &, float);
	};
	class Cʵ�� {
	public:
		void f��ʼ��_����(const C��Ϸ�ٶ� &);
		void f��ʼ��_����(C��������<C�л�> &);
		void f��ʼ��_��Դ(const C��������<S�л�����> &);
		void f�����л�(std::shared_ptr<C�л�>, S���� &);
		bool fi�п�() const;
		C��������<C�л�> *ma�л� = nullptr;
		const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
		const C��������<S�л�����> *ma�л����� = nullptr;
	};
	C�л������(Cʵ�� &);
	template<typename t, typename...t����> std::shared_ptr<t> f�����л�(t���� &&...);
	std::shared_ptr<C�л�> f������();
	S���� m����;
private:
	Cʵ�� *mʵ�� = nullptr;
};
//�����л�����ʵ��
template<typename t, typename...t����> std::shared_ptr<t> C�л������::f�����л�(t���� &&...a����) {
	static_assert(std::is_base_of<C�л�, t>::value, "����:t����̳��Եл�");
	if (mʵ��->fi�п�()) {
		std::shared_ptr<t> vָ�� = std::make_shared<t>(a����...);
		mʵ��->f�����л�(vָ��, m����);
		return vָ��;
	}
	return nullptr;
}
}	//namespace ����ɽկ