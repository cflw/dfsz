#pragma once
#include <bitset>
#include <atomic>
#include <cflw����.h>
#include <cflw����.h>
namespace ����ɽկ {
namespace ���� = cflw::����;
namespace ���� = cflw::����;
typedef std::bitset<32> t��־;
//==============================================================================
// �Զ����
//==============================================================================
class C�Զ���� {
public:
	std::atomic<int> m��� = 0;
	void f����();
	int f�±��();
};
//==============================================================================
// ��Ϸ�ٶ�
//==============================================================================
class C��Ϸ�ٶ� {
private:
	float m�ٶ�;
	float m��;
	float m֡;
public:
	C��Ϸ�ٶ�(float �ٶ� = 1);
	void f�ڲ�����();
	void fs�ٶ�(float �ٶ�);
	float fg�ٶ�() const;
	float fg��() const;
	float fg֡() const;	//����fg�ٶ�
	float fg��Ⱦ��() const;
	float fg��Ⱦ֡() const;
};
//==============================================================================
// ��Ϸ����
//==============================================================================
// ��Ϸ�����ü̳�,���Ƿ���Ҫ����ʵ��.��Ϊ���漰����̬/��̬�������Ϸ����Ĺ���
class C��Ϸ���� {
public:
	virtual void f����_ʹ��() = 0;
	virtual void f����_����() = 0;
	virtual bool f����_iʹ��() const = 0;
};
/*
template<typename t> concept T��Ϸ���� = requires(T a) {
	a.f����_ʹ��();
	a.f����_����();
	{a.f����_iʹ��()}->bool;
}
*/
//����Ϸ������͵��ʱ����ֱ�Ӽ̳�
class C����Ϸ���� {
public:
	C����Ϸ����() = default;
	void f����_ʹ��() {
		mʹ�� = true;
	}
	void f����_����() {
		mʹ�� = false;
	}
	bool f����_iʹ��() const {
		return mʹ��;
	}
private:
	bool mʹ�� = false;
};
//==============================================================================
// �¼�����
//==============================================================================
class I�¼� {
public:
	virtual void f�¼�_��ʼ��() {}	//�����������󲢸�ֵ�����
	virtual void f�¼�_ִ��() {}	//ÿ֡����һ��
	virtual void f�¼�_����() {}	//�������ڴ�������ʱ����
	virtual void f�¼�_����() {}	//�ؿ��¼�����ʱ,�л��볡ʱ����
	virtual void f�¼�_����() {}	//�л�������ʱ����
};
//==============================================================================
// ͼ�ι���
//==============================================================================
class Iͼ�ι��� {
public:
	virtual void f׼��() = 0;
	virtual void fˢ��() = 0;
	void f�Զ�׼��();
};
//==============================================================================
// ѭ������
//==============================================================================
class Cѭ������ {
public:
	enum E��־ {
		e�״�����,
		eȥ��ĩβ,	//Ҫ��ϰٷֱ�
		e����,
		eС��,	//[0,1]
	};
	static const t��־ c��׼����, c��Ȼ����, c�м��ֵ, cС��, cС������, c��������, cԲ��;
	static t��־ fc��׼(bool �״� = false, bool ���� = false, bool С�� = false);
	static t��־ fc��ֵ(bool ͷ = true, bool β = true);
	static t��־ fc����(bool С�� = false);
	static unsigned int f����λ(int);
	static unsigned int f����λ(bool, int);
	static float f����(int ����, int ����, t��־);
};
//==============================================================================
// ��ʱ��
//==============================================================================
class C��ʱ�� {
public:
	C��ʱ��(float aʱ�� = 1);
	bool f�δ�();
	void fֹͣ();
	void f����(float);
private:
	float m�δ�;
	float m��ʱ;
};
//�δ�һ�κ��ֹͣ�ļ�ʱ��
class C���μ�ʱ�� {
public:
	C���μ�ʱ��(float ʱ�� = 1);
	bool f�δ�();
	void f����(float);
private:
	float m�δ�;
	float m��ʱ;
};
//==============================================================================
// ����
//==============================================================================
template<typename t> class I���� {
public:
	virtual t *f�ӿ�_�½�() const = 0;	//�������󣬷�����ָ�룬С���ڴ�й¶
	std::unique_ptr<t> f�½�u() const {
		return std::unique_ptr<t>(this->f�ӿ�_�½�());
	}
	std::shared_ptr<t> f�½�s() const {
		return std::shared_ptr<t>(this->f�ӿ�_�½�());
	}
};
template<typename t����, typename t������ = t����> class C�򵥹��� : public I����<t����> {
public:
	static_assert(std::is_base_of<t����, t������>::value, "");
	t���� *f�ӿ�_�½�() const override {
		return new t������();
	}
};
}	//namespace ����ɽկ