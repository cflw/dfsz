#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <atomic>
#include <mutex>
#include <execution>
#include <cflw����_ѭ��.h>
#include "��Ϸ_���Ʊ�ʶ.h"
namespace ����ɽկ {
namespace ѭ�� = cflw::����::ѭ��;
//==============================================================================
// ��̬/��̬����,����Ԫ�ر�������Ϸ����
//==============================================================================
class C������� {
public:
	C�������(size_t a����): m����(a����) {
		m���� = 0;
	}
	void f�Ӽ���() {
		//assert(m���� < m����);
		++m����;
		m�ӱ仯 = true;
	}
	void f������() {
		assert(m���� > 0);
		--m����;
		m���仯 = true;
	}
	size_t fg����() const {
		return m����;
	}
	bool fi�仯() const {
		return m�ӱ仯 || m���仯;
	}
	bool fi�ӱ仯() const {
		return m�ӱ仯;
	}
	bool fi���仯() const {
		return m���仯;
	}
	void f�ޱ仯() {
		m�ӱ仯 = false;
		m���仯 = false;
	}
	void f�޼ӱ仯() {
		m�ӱ仯 = false;
	}
	void f�޼��仯() {
		m���仯 = false;
	}
	operator size_t() {
		return m����;
	}
private:
	const size_t m����;
	std::atomic<size_t> m����;
	bool m�ӱ仯 = false, m���仯 = false;
};
//��������
template<typename t> class C�������� {
public:
	using value_type = t;
	using reference = t & ;
	using const_reference = const t&;
	typedef std::shared_ptr<t> tָ��;
	C��������(size_t a����): m����(a����), m��������(a����) {
		ma����.reserve(a����);
	}
	~C��������() {
	}
	void f���() {
		ma����.clear();
		ma�½�.clear();
	}
	void f���(tָ�� ap) {
		std::lock_guard<std::mutex> m������(m������);
		ma�½�.push_back(ap);
	}
	bool fi�п�(size_t a���� = 1) const {
		return m��ǰ���� + a���� <= fg����();
	}
	bool fi�޿�() const {
		return m��ǰ���� >= fg����();
	}
	size_t fg����() const {
		return m��ǰ����;
	}
	size_t fg����() const {
		return m��������;
	}
	bool fi�仯() const {
		return m����.fi�仯();
	}
	void feʹ��(std::function<void(t&)> af) {
		std::for_each(std::execution::seq, ma����.begin(), ma����.end(), [&af](const tָ�� &ap����) {
			if (ap����->f����_iʹ��()) {
				af(*ap����);
			}
		});
	}
	void feʹ��p(std::function<void(tָ��)> af) {
		std::for_each(std::execution::seq, ma����.begin(), ma����.end(), [&af](const tָ�� &ap����) {
			if (ap����->f����_iʹ��()) {
				af(ap����);
			}
		});
	}
	void feʹ��_����(std::function<void(t&)> af) {
		std::for_each(std::execution::par, ma����.begin(), ma����.end(), [&af](const tָ�� &ap����) {
			if (ap����->f����_iʹ��()) {
				af(*ap����);
			}
		});
	}
	void f����() {
		f����_ɾ����ʹ�ö���();
		f����_�ϲ��¶���();
		f��������();
		assert(m��ǰ���� == ma����.size());
	}
	void f����_ɾ����ʹ�ö���() {
		if (m����.fi���仯()) {
			ma����.erase(std::remove_if(ma����.begin(), ma����.end(), [](const tָ�� &aָ��)->bool {
				return !aָ��->f����_iʹ��();
			}), ma����.end());
			m����.f�޼��仯();
		}
	}
	void f����_�ϲ��¶���() {
		if (m����.fi�ӱ仯()) {
			assert(!ma�½�.empty());
			std::copy(ma�½�.begin(), ma�½�.end(), std::back_inserter(ma����));
			ma�½�.clear();
			m����.f�޼ӱ仯();
		}
	}
	void f��������() {
		m��ǰ���� = m����.fg����();
	}
	std::vector<tָ��> ma����;
	std::vector<tָ��> ma�½�;
	const size_t m��������;
	size_t m��ǰ���� = 0;
	C������� m����;
	std::mutex m������;
};
//��̬����
template<typename t> class C��̬���� : public std::vector<t> {
public:
	using value_type = t;
	using reference = t & ;
	using const_reference = const t&;
	using t�� = std::vector<t>;
	C��̬����() = default;
	void f���() {
		for (auto v = t��::begin(); v != t��::end(); ++v) {
			if (v->f����_iʹ��()) {
				v->f����_����();
			}
		}
	};
	void f�½�(int a����, std::function<void(t &, int)> p�½�) {
		int v���� = 0;
		for (int i = 0; i < t��::size(); ++i) {
			t &v = t��::operator[](i);
			if (!v.f����_iʹ��()) {
				p�½�(v, i);
				++v����;
				if (v���� >= a����) {
					return;
				}
			}
		}
		for (;v���� < a����; ++v����) {
			t v;
			p�½�(v, t��::size());
			t��::push_back(v);
		}
	}
	int f�����½�(int a����, std::function<void(t &)> p�½�) {
		int vλ�� = 0;
		int v���� = 0;
		for (int i = 0; i < t��::size(); ++i) {
			t &v = t��::operator[](i);
			if (v.f����_iʹ��()) {
				vλ�� = i + 1;
			} else {
				++v����;
				if (v���� >= a����) {
					break;
				}
			}
		}
		v���� = 0;
		while (v���� < a����) {
			const int v��ǰλ�� = vλ�� + v����;
			if (v��ǰλ�� < t��::size()) {
				p�½�(t��::operator[](v��ǰλ��));
			} else {
				t v;
				p�½�(v);
				t��::push_back(v);
			}
			++v����;
		}
		return vλ��;
	}
};
//==============================================================================
// ӳ������
//==============================================================================
//ӳ��ָ��
template<typename tֵ> class Cӳ��ָ�� {
public:
	typedef Cӳ��ָ��<tֵ> t��;
	Cӳ��ָ��() = default;
	Cӳ��ָ��(int a����, tֵ *aָ��) :
		m����(a����), mָ��(aָ��) {
	}
	t�� &operator =(int a����) {
		if (a���� == 0) {
			f���();
		} else if (m���� != a����) {
			m����.clear();
			m���� = a����;
			mָ�� = nullptr;
		}
		return *this;
	}
	t�� &operator =(tֵ *aָ��) {
		m����.clear();
		m���� = 0;
		mָ�� = aָ��;
		return *this;
	}
	t�� &operator =(const std::wstring &a����) {
		if (a����.empty()) {
			f���();
		} else if (a���� != m����) {
			m���� = a����;
			m���� = 0;
			mָ�� = nullptr;
		}
		return *this;
	}
	t�� &operator =(tֵ &aֵ) {
		mָ�� = std::addressof(aֵ);
		m���� = 0;
		m����.clear();
		return *this;
	}
	tֵ *operator ->() const {
		return mָ��;
	}
	tֵ &operator *() const {
		return *mָ��;
	}
	tֵ &operator [](int p) const {
		return mָ��[p];
	}
	bool fi�����() const {
		return mָ�� == nullptr;
	}
	bool fi���������() const {
		if (m����.empty()) {	//û����
			return false;
		} else if (m���� == 0) {	//������û������
			return true;
		} else {	//��������
			return false;
		}
	}
	void f���븳ֵ(tֵ *aָ��) {
		mָ�� = aָ��;
	}
	void f���() {
		m����.clear();
		m���� = 0;
		mָ�� = nullptr;
	}
	std::wstring m����;
	int m���� = 0;	//ֵ�������е����
	tֵ *mָ�� = nullptr;	//ָ��ֵ
};
//����ָ��,ָ�ĵ�ַ���������仯ʱʹ��
template<typename tֵ> class C����ָ�� {
public:
	typedef C����ָ��<tֵ> t��;
	C����ָ��() = default;
	C����ָ��(int p��, tֵ *aָ��) :
		m����(p��), mָ��(aָ��) {
	}
	t�� &operator =(int p����) {
		m���� = p����;
		return *this;
	}
	t�� &operator =(tֵ *aָ��) {
		m���� = 0;
		mָ�� = aָ��;
		return *this;
	}
	tֵ *operator ->() const {
		return mָ��;
	}
	tֵ &operator *() const {
		return *mָ��;
	}
	tֵ &operator [](int p) const {
		return mָ��[p];
	}
	bool fi�����() const {
		return m���� != m���� || mָ�� == nullptr;
	}
	void f���븳ֵ(tֵ *aָ��) {
		m���� = m����;
		mָ�� = aָ��;
	}
	int m���� = 0;	//ֵ�������е����
	int m���� = -1;	//����ʱ��ֵ
	tֵ *mָ�� = nullptr;	//ָ��ֵ
};
//����
template<typename t> using t����ָ�� = Cӳ��ָ��<const t>;
template<typename t> using t��չָ�� = Cӳ��ָ��<t>;
//��������
template<typename tֵ> class C�������� {
public:
	using value_type = tֵ;
	using reference = tֵ&;
	using const_reference = const tֵ&;

	typedef t����ָ��<tֵ> tָ��;
	C��������() = default;
	auto &&operator [](const std::wstring &) const;
	void f���(int a��, const tֵ &aֵ) {
		assert(fi������(a��));
		maӳ��.emplace(a��, ma����.size());
		ma����.push_back(aֵ);
	}
	void f���(int a��, const std::initializer_list<tֵ> &aaֵ) {
		assert(fi������(a��));
		int i = 0;
		for (const auto &vֵ : aaֵ) {
			maӳ��.emplace(����::f��(a��, i++), ma����.size());
			ma����.push_back(vֵ);
		}
	}
	template<typename...t����>
	void f����(int a��, t���� &&...a����) {
		assert(fi������(a��));
		maӳ��.emplace(a��, ma����.size());
		ma����.emplace_back(a����...);
	}
	void f����(int a��0, int a��1) {
		assert(fi������(a��0));
		maӳ��.emplace(a��0, maӳ��.at(a��1));
	}
	tֵ &fȡ��(int a��) {
		assert(fi������(a��));
		maӳ��[a��] = ma����.size();
		ma����.emplace_back();
		return ma����.back();
	}
	tָ�� f��(int a��) const {
		if (a��) {
			assert(fi����(a��));
			return tָ��(a��, fgָ��(a��));
		} else {
			return tָ��{};
		}
	}
	const tֵ &fg����(int a��) const {
		assert(fi����(a��));
		const int vλ�� = maӳ��.at(a��);
		return ma����[vλ��];
	}
	const tֵ *fgָ��(int a��) const {
		if (a��) {
			assert(fi����(a��));
			const int vλ�� = maӳ��.at(a��);
			return ma����.data() + vλ��;
		} else {
			return nullptr;
		}
	}
	bool fi����(int a��) const {
		return maӳ��.find(a��) != maӳ��.end();
	};
	bool fi������(int a��) const {
		return maӳ��.find(a��) == maӳ��.end();
	}
	void f����(tָ�� &aָ��) const {
		if (aָ��.fi���������()) {
			aָ��.m���� = C���Ʊ�ʶ::f��������(aָ��.m����);
		}
		if (aָ��.m����) {
			aָ��.mָ�� = fgָ��(aָ��.m����);
		} else {
			aָ��.mָ�� = nullptr;
		}
	}
	void f���() {
		maӳ��.clear();
		ma����.clear();
	}
public:
	std::map<int, int> maӳ��;	//��ʶ�����
	std::vector<tֵ> ma����;
};
//��չ����
template<typename tֵ> class C��չ���� : public std::map<int, std::unique_ptr<tֵ>> {
public:
	using value_type = tֵ;
	using reference = tֵ & ;
	using const_reference = const tֵ&;

	typedef std::map<int, std::unique_ptr<tֵ>> t����;
	typedef t��չָ��<tֵ> tָ��;
	typedef C����ָ��<const tֵ> t����ָ��;
	C��չ����() {
		f���(0, nullptr);
	}
	void f���(int a��, tֵ *aֵ) {
		if (a�� == 0) {
			assert(t����::operator[](a��) == nullptr);
		} else {
			assert(!fi����(a��));
		}
		t����::operator[](a��).reset(aֵ);
	}
	template<typename t����, typename...t����>
	void f����(int a��, t���� &&...a����) {
		static_assert(std::is_base_of<tֵ, t����>::value, "t���� ������ tֵ �Ļ���");
		f���(a��, new t����(a����...));
	}
	std::unique_ptr<tֵ> &fȡ��(int a��) {
		assert(t����::find(a��) == t����::end());
		return t����::operator[](a��);
	}
	tָ�� f��(int a��) const {
		assert(fi����(a��));
		return tָ��(a��, fg��չ(a��));
	}
	tֵ *fg��չ(int a��) const {
		assert(fi����(a��));
		return t����::at(a��).get();
	}
	bool fi����(int a��) const {
		return t����::find(a��) != t����::end();
	}
	void f����(tָ�� &aָ��) {
		if (aָ��.fi���������()) {
			aָ��.m���� = C���Ʊ�ʶ::f��������(aָ��.m����);
		}
		aָ��.mָ�� = fg��չ(aָ��.m����);
	}
};
}