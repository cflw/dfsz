#pragma once
#include "����.h"
#include "ͼ�λ���.h"
#include "ͼ�ι���.h"
namespace ����ɽկ {
class C��ҳɼ�ͼ��ʵ��;
class C����ҳɼ� {
public:
	static constexpr float c�ֺ� = ��ά::ca�����ֺ�[��ά::e����];
	static constexpr float cС���ֺ� = c�ֺ� * 0.6f;
	static constexpr float c�о� = c�ֺ�;
	static constexpr float c����x = -c�߿�Χx + 2;
	C����ҳɼ�(��ά::C��ά &);
	��ά::tp�ı�Ч�� fc�ı�Ч��(const ��ѧ::S��ɫ &) const;
	��ά::tp�ı����� fc�ı�����(const std::wstring &, ��ά::tp�ı���ʽ) const;
	��ά::tp�ı����� fc�ı�����_С��(double, int, ��ά::tp�ı���ʽ) const;
	void f���ɼ�ͼ��(const C��ҳɼ�ͼ��ʵ�� &) const;
	��ά::C��ά *m��ά = nullptr;
	��ά::C�ı����� *m�ı����� = nullptr;
	��ά::tp���ı� m���ı�;
};
class C��ҳɼ�ͼ��ʵ�� {
public:
	void fʵ��_��ʼ������(const C����ҳɼ� &);
	void fʵ��_��ʼ��(float λ��, ��ά::tp�ı���ʽ ��ʽ, const t��ɫ &��ɫ);
	void fʵ��_����();
	void fʵ��_ֵ�仯��();
	void fʵ��_��ʾ() const;
	float fʵ��_g͸����() const;
	float m�仯 = 1;
	float m����y = 0;
	bool m�ı��仯 = true;
	��ά::tp�ı����� m�ı�����;
	��ά::tp�ı���ʽ m�ı���ʽ;
	��ά::tp�ı�Ч�� m�ı�Ч��;
	const C����ҳɼ� *m���ɼ� = nullptr;
};
template<typename t0> class C��ҳɼ�ͼ�� : public Iͼ��, public C��ҳɼ�ͼ��ʵ�� {
public:
	static_assert(std::is_arithmetic<t0>::value);
	using tf���� = std::function<t0()>;
	using tf���� = std::function<t0(t0, t0)>;	//����ֵ(ԭֵ, ����ֵ)
	using tf���� = std::function<void(C��ҳɼ�ͼ��<t0> &, const C����ҳɼ� &)>;
	//����
	C��ҳɼ�ͼ��(const tf���� &af����, const tf���� &af����, const tf���� &af����):
		mf����(af����), mf����(af����), mf����(af����) {
	}
	//��д
	void f�ӿ�_����() override {
		const t0 vĿ�� = mf����(mֵ, mf����());
		if (mֵ != vĿ��) {
			mֵ = vĿ��;
			fʵ��_ֵ�仯��();
		}
		fʵ��_����();
	}
	void f�ӿ�_����() override {
		if (m�ı��仯) {
			mf����(*this, *m���ɼ�);
			m�ı��仯 = false;
		}
	}
	void f�ӿ�_��ʾ() const override {
		fʵ��_��ʾ();
	}
	//����
	template<typename t1> static tf���� F����_ֵ(const t1 &a) {
		return [&a]()->t0 {
			return (t0)a;
		};
	}
	static tf���� F����_ֵ(const t0 &a) {
		return [&a]()->t0 {
			return a;
		};
	}
	static tf���� F����_����(const boost::rational<int> &a) {
		return [&a]()->t0 {
			return boost::rational_cast<t0>(a);
		};
	}
	//����
	static t0 f����_ֱ��(t0, t0 a) {
		return a;
	}
	static tf���� F����_����(float a����, t0 a��С, t0 a���) {
		return [=](t0 a0, t0 a1)->t0 {
			return ��ѧ::f��������<t0>(a0, a1, a����, a��С, a���);
		};
	}
	//����
	void f����_ֱ��(const C����ҳɼ� &a) {
		m�ı����� = a.fc�ı�����(std::to_wstring(mֵ), m�ı���ʽ);
	}
	static tf���� F����_ת��(std::function<std::wstring(t0)> af) {
		return [=](C��ҳɼ�ͼ��<t0> &a��, const C����ҳɼ� &a) {
			a��.m�ı����� = a.fc�ı�����(af(a��.mֵ), a��.m�ı���ʽ);
		};
	}
	static tf���� F����_С��(int aС��λ��) {
		return [=](C��ҳɼ�ͼ��<t0> &a��, const C����ҳɼ� &a) {
			a��.m�ı����� = a.fc�ı�����_С��(a��.mֵ, aС��λ��, a��.m�ı���ʽ);
		};
	}
	//����
	t0 mֵ = 0;
	tf���� mf����;
	tf���� mf����;
	tf���� mf����;
};
//==============================================================================
// ��ҳɼ�ͼ�ι���
//==============================================================================
class C��ҳɼ�ͼ�ι��� {
public:
	C��ҳɼ�ͼ�ι���(const Cͼ�ι��� &, const C����ҳɼ� &, std::vector<std::shared_ptr<Iͼ��>> &);
	template<typename t0> std::shared_ptr<C��ҳɼ�ͼ��<t0>> f����ͼ��(float λ��, ��ά::tp�ı���ʽ ��ʽ, const t��ɫ &��ɫ, const typename C��ҳɼ�ͼ��<t0>::tf���� &, const typename C��ҳɼ�ͼ��<t0>::tf���� &, const typename C��ҳɼ�ͼ��<t0>::tf���� &);
	Cͼ�ι��� mͼ�ι���;
	const C����ҳɼ� *m����ҳɼ� = nullptr;
	std::vector<std::shared_ptr<Iͼ��>> *ma��ҳɼ� = nullptr;
};
template<typename t0> std::shared_ptr<C��ҳɼ�ͼ��<t0>> C��ҳɼ�ͼ�ι���::f����ͼ��(float aλ��, ��ά::tp�ı���ʽ a��ʽ, const t��ɫ &a��ɫ, const typename C��ҳɼ�ͼ��<t0>::tf���� &af����, const typename C��ҳɼ�ͼ��<t0>::tf���� &af����, const typename C��ҳɼ�ͼ��<t0>::tf���� &af����) {
	std::shared_ptr<C��ҳɼ�ͼ��<t0>> vͼ�� = std::make_shared<C��ҳɼ�ͼ��<t0>>(af����, af����, af����);
	vͼ��->fʵ��_��ʼ������(*m����ҳɼ�);
	vͼ��->fʵ��_��ʼ��(aλ��, a��ʽ, a��ɫ);
	mͼ�ι���.fʵ��_����ͼ��(vͼ��);
	return vͼ��;
}
}	//namespace ����ɽկ