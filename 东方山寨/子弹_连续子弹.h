#pragma once
#include "�ӵ�����.h"
namespace ����ɽկ {
class C�����ӵ� : public C�ӵ� {
private:
	typedef void (*tf�������)(C�����ӵ� &, C�����ӵ� &);
	using tp�����ӵ� = std::shared_ptr<C�����ӵ�>;
	enum E��� {
		e������ = C�ӵ�::e�Զ���,	//��"f�ӿ�_����"��,�ӵ��ڴ�����ʱ�ӱ��.��"f�ӿ�_�ڴ�����"�����ж�
		e����ͷ��,
		eϸ��,	//����ͨ��ϸ���ӵ��������ӵ�
	};
public:	//���ӹ���
	class C���ӹ��� {	//��������
	public:
		C���ӹ���();
		C���ӹ���(tf�������);
		C���ӹ��� &operator +=(const std::shared_ptr<C�����ӵ�> &);
	private:
		std::shared_ptr<C�����ӵ�> m��;
		tf������� mf����;
	};
	class C���ι��� {
	public:
		C���ι���();
		C���ι���(tf�������);
		~C���ι���();
		C���ι��� &operator +=(const std::shared_ptr<C�����ӵ�> &);
	private:
		std::shared_ptr<C�����ӵ�> mͷ, m��;
		tf������� mf����;
	};
public:	//ϸ�ֹ���
	template<typename t, bool ti���캯�� = std::is_constructible<t, const t &, const t &, float>::value> class Cϸ�ֹ��� {
	public:	//ti���캯��=trueʱ,�����������ϸ�ֹ��캯��
		static_assert(std::is_base_of<C�����ӵ�, t>::value, "");
		static void f����(const std::shared_ptr<t> &);	//��"C�����ӵ�::mfϸ��"��ֵ
	};
public:	//��д�Ľӿں���
	C�����ӵ�() = default;
	C�����ӵ�(const C�����ӵ� &, const C�����ӵ� &, float);
	template<typename t> static void f�ӿ�_�������ͳ�ʼ��(const std::shared_ptr<t> &);
	void f�ӿ�_��ʼ��() override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_�Ի��ж�(C�Ի����ӵ��ж� &) override;
	bool f�ӿ�_i�ڴ�����() override;
	bool f�ӿ�_����ʾ() const override;
	bool f�ӿ�_ը���ж�(C�ӵ������ը���ж� &) override;
public:		//��ʼ��
public:		//����
	void f����_��ʧ(bool);
private:	//��չ
	std::shared_ptr<C�����ӵ�> fg��ָ��() const;
	bool f��չ_i��() const;
	void f��չ_�Զ�ϸ��();
	float f��չ_gϸ�ּ��() const;
	static std::shared_ptr<C�����ӵ�> f�����ӵ�_cϸ��(C�����ӵ� &, C�����ӵ� &, float);	//�½��ӵ�����
	static void f�����ӵ�_����0(C�����ӵ� &, C�����ӵ� &);
	static void f�����ӵ�_�Ͽ�0(C�����ӵ� &, C�����ӵ� &);
	static void f�����ӵ�_ϸ��0(C�����ӵ� &, C�����ӵ� &, int);	//�����ӵ����������ϸ���ӵ�
	static void f�����ӵ�_����1(C�����ӵ� &, C�����ӵ� &);
	static void f�����ӵ�_�Ͽ�1(C�����ӵ� &, C�����ӵ� &);
private:	//����
	static std::mutex m���ӻ���;
	std::weak_ptr<C�����ӵ�> m��;
	std::shared_ptr<C�����ӵ�> mǰ, m��;
	S�ӵ����� m����;
	S�ӵ���ʧ m��ʧ;
	std::shared_ptr<C�����ӵ�> (*mfϸ��)(C�����ӵ� &, C�����ӵ� &, float);
	tp�ӵ�ͼ������ mͼ������;
};
//==============================================================================
// �����ӵ�ϸ�ֹ��ߵ�ʵ��
//==============================================================================
template<typename t> class C�����ӵ�::Cϸ�ֹ���<t, true> {
public:
	static void f����(const std::shared_ptr<t> &a��) {
		C�����ӵ� *const v�� = a��.get();
		v��->mfϸ�� = [](C�����ӵ� &aǰ, C�����ӵ� &a��, float a��ֵ)->std::shared_ptr<C�����ӵ�> {
			return std::make_shared<t>(aǰ, a��, a��ֵ);
		};
	}
};
template<typename t> class C�����ӵ�::Cϸ�ֹ���<t, false> {
public:
	static void f����(const std::shared_ptr<t> &a��) {
		C�����ӵ� *const v�� = a��.get();
		v��->mfϸ�� = f�����ӵ�_cϸ��;
	}
};
template<typename t> void C�����ӵ�::f�ӿ�_�������ͳ�ʼ��(const std::shared_ptr<t> &a��) {
	static_assert(std::is_base_of<C�����ӵ�, t>::value, "");
	a��->m�� = a��;
	Cϸ�ֹ���<t>::f����(a��);
}
}