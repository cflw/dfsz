#pragma once
#include <random>
#include <wrl.h>
#include <cflw��ѧ_���.h>
#include "��ѧ����.h"
#include "����.h"
#include "����_����.h"
namespace ����ɽկ {
using Microsoft::WRL::ComPtr;
typedef std::mt19937 t���������;
//==============================================================================
// ��
//==============================================================================
class C��Ϸ;
struct S��Ϸ����;
class Cͼ������;
class C��������;
class C��Ƶ����;
//�ؿ�
class C�ؿ��ű�;
class C�ؿ�����;
class C��ս����;
class C�ؿ�;
//�ӵ�
class C�ӵ�;
class C�ӵ������;
//�л�
class C�л������;
class C�л�;
struct S�л�����;
//����ӵ�
class C����ӵ�;
class C����ӵ������;
//���
class C���;
class C�Ի�;
class I�ӻ��ƶ�;
class C����ӵ�������;
class C�Ѷ�;
//����
class C����;
class C���������;
//����
struct S�ӵ�����;
struct S�Ի�����;
struct S�ӻ�����;
struct S��������;
struct S����ӵ�����;
//��չ
class C���ը��;
//ͼ��
class Iͼ��;
class Cͼ�ι���;
class I���ӵ�;
class I����;
class C������;	//����ͷ�ļ�"ͼ��_��Դ����.h"
class C���㹤��;
class Cģ�͹���;
//������Դ
class Cȡ�ı�;
//==============================================================================
// ��Ϸ
//==============================================================================
class C��Ϸ {
private:
	class Cʵ��;
	class C��Դ;
public:
	C��Ϸ();
	~C��Ϸ();
	//
	void f��ʼ��_ͼ�νӿ�(Cͼ������ &);
	void f��ʼ��_����ӿ�(C�������� &);
	void f��ʼ��_��Ƶ�ӿ�(C��Ƶ���� &);
	void f��Դ��ʼ��();
	void f��Ϸ��ʼ��();
	void f����ؿ�(C�ؿ� &);
	void f����();
	void f����();
	void f��ʾ() const;
public:	//��������
	class C���� {	//ȫ�ֿ�����Ϸ����
		friend C��Ϸ;
	public:
		//����
		C��Ϸ�ٶ� &fg��Ϸ�ٶ�() const;
		C��������<C�ӵ�> &fg�ӵ�����() const;
		C��������<C�л�> &fg�л�����() const;
		t��������� &fg���������() const;
		C�Ի� &fg�Ի�() const;
		C�ؿ����� &fg�ؿ�����() const;
		C��ս���� &fg��ս����() const;
		C�Ѷ� &fg�Ѷ�() const;
		C��� &fg���() const;
		//����
		C�ӵ������ f����_�ӵ�() const;
		C�л������ f����_�л�() const;
		C����ӵ������ f����_����ӵ�() const;
		C��������� f����_����() const;
		std::shared_ptr<C�ӵ������> f����_�ӵ�p() const;
		std::shared_ptr<C�л������> f����_�л�p() const;
		std::shared_ptr<C����ӵ������> f����_����ӵ�p() const;
		std::shared_ptr<C���������> f����_����p() const;
		template<typename t> auto f����_�����f(t &&, int = 0) const;
		t��������� f����_���������(int = 0) const;
		//��Ϸ��
		void f��Ϸ_ȫ���嵯(const t����2 & = t����2::c��, float = 600, bool ���� = false);
		void f��Ϸ_����ؿ�(C�ؿ� &);
	private:
		Cʵ�� *mʵ�� = nullptr;
	};
	class Cȡ��Դ {	//ר��ȡ��Դ����
		friend C��Ϸ;
	public:
		C��Ϸ�ٶ� &fg��Ϸ�ٶ�() const;
		C��������<S�ӵ�����> &fg�ӵ�����() const;
		C��������<S�Ի�����> &fg�Ի�����() const;
		C��������<S�ӻ�����> &fg�ӻ�����() const;
		C��������<S��������> &fg��������() const;
		C��������<S����ӵ�����> &fg����ӵ�����() const;
		C��������<S�л�����> &fg�л�����() const;
		C��������<std::wstring> &f���ı�����(const std::wstring &ȫ������, const std::wstring &����);
		const C��������<std::wstring> &f���ı�����(const std::wstring &ȫ������, const std::wstring &����) const;
		Cȡ�ı� fȡ�ı�����(const std::wstring &ȫ������, const std::wstring &����) const;
		Cȡ�ı� fg��ͨ�ı�() const;
		Cȡ�ı� fg�����ı�() const;
		C��չ����<I����<C����ӵ�������>> &fg��ҷ���() const;
		C��չ����<I���ӵ�> &fg���ӵ�() const;
		C��չ����<I����<I�ӻ��ƶ�>> &fg�ӻ��ƶ�() const;
		C��չ����<I����<I����>> &fg����() const;
		C������ &fg������() const;
		C���㹤�� &fg���㹤��() const;
		std::map<std::wstring, int> &fg���Ʊ�ʶ() const;
		int fc�����ʶ() const;
		int fg��ʶ(const std::wstring &) const;
		C��������<Iͼ��> &fgͼ������() const;
		Cͼ�ι��� f����_ͼ��();
		std::shared_ptr<Cͼ�ι���> f����_ͼ��p();
		template<typename t> auto f����_�����f(t &&, int = 0) const;
		t��������� f����_���������(int = 0) const;
	private:
		C��Դ *m��Դ = nullptr;
	};
	static C���� &fg����();
	static Cȡ��Դ &fg��Դ();
	static S��Ϸ���� &fg����();
	static Cͼ������ &fgͼ��();
	static C��Ƶ���� &fg��Ƶ();
	static C���� g����;
	static Cȡ��Դ g��Դ;
private:	//�ڲ�����
	static C��Դ &fg�ڲ���Դ();
	static std::unique_ptr<Cʵ��> mpʵ��;
	static std::unique_ptr<C��Դ> mp��Դ;
};
//==============================================================================
// ģ��ʵ��
//==============================================================================
template<typename t> auto C��Ϸ::C����::f����_�����f(t &&a�ֲ�, int a�ƽ�) const {
	return std::bind(a�ֲ�, f����_���������(a�ƽ�));
}
template<typename t> auto C��Ϸ::Cȡ��Դ::f����_�����f(t &&a�ֲ�, int a�ƽ�) const {
	return std::bind(a�ֲ�, f����_���������(a�ƽ�));
}
//ȡ������������ָ��
template<typename t> const ComPtr<t> &fȡ������������ָ��(const C��������<ComPtr<t>> &a����, int a��ʶ) {
	return a����.fg����(a��ʶ);
}
template<typename t> const std::shared_ptr<t> &fȡ������������ָ��(const C��������<std::shared_ptr<t>> &a����, int a��ʶ) {
	return a����.fg����(a��ʶ);
}
template<typename t> const t *fȡ������������ָ��(const C��������<t> &a����, int a��ʶ) {
	return a����.fgָ��(a��ʶ);
}
template<typename t> auto &&C��������<t>::operator [](const std::wstring &a) const {
	return fȡ������������ָ��(*this, C��Ϸ::fg��Դ().fg��ʶ(a));
}
}	//namespace ����ɽկ