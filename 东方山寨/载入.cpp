#include <tuple>
#include <boost/property_tree/json_parser.hpp>
#include <cflw�ļ�_json.h>
//����
#include "����.h"
#include "����.h"
#include "����.h"
#include "����.h"
#include "��Ϸ.h"
#include "��ʶ.h"
#include "ȡ�ı�.h"
//ͼ��
#include "ͼ������.h"
#include "ͼ������_��Դ����.h"
#include "ͼ��_��ά.h"
#include "�����ӿ�.h"
#include "����.h"
#include "ͼ��_�ӵ�.h"
#include "���߶���.h"
//����
#include "����.h"
#include "�ӵ�����.h"
#include "��Ƶ����.h"
//���
#include "���.h"
#include "�Ի�.h"
#include "�ӻ��ƶ�_λ��.h"
#include "����ӵ�����.h"
#include "����ӵ��������.h"
#include "����ӵ�����_��ɢ.h"
#include "����ӵ�������չ.h"
#include "���ը����չ.h"
//�л�
#include "�л�����.h"
namespace ����ɽկ {
using t�����ļ� = cflw::�ļ�::json::C�ļ�;
using t������ = boost::property_tree::wptree;
//=============================================================================
// ��json
//=============================================================================
class C��json�ļ� {
public:
	static bool f��ȡ(boost::property_tree::wptree &a�����, const std::filesystem::path &a·��) {
		t�����ļ� v�ļ�;
		const std::filesystem::path v·�� = C����::f����·��(a·��, L"");
		if (v�ļ�.f��(v·��.c_str())) {
			v�ļ�.f��ȡ(a�����);
			return true;
		} else {
			return false;
		}
	}
	static bool f��ȡ(boost::property_tree::wptree &a�����, const S������� &a����, const std::filesystem::path &a·��, std::filesystem::path &a���·��) {
		t�����ļ� v�ļ�;
		const std::filesystem::path v·�� = C����::f����·��(a·��, a����.m·��);
		if (v�ļ�.f��(v·��.c_str())) {
			v�ļ�.f��ȡ(a�����);
			a���·�� = v·��;
			return true;
		} else {
			__debugbreak();
			return false;
		}
	}
};
//=============================================================================
// ��������
//=============================================================================
class C�������� {
public:
	C��������(int a����, bool a���� = true) :
		m����(a����),
		m����(a����) {
	}
	template<typename t>
	static void f������ֵ(t &a, const C�������� &aȫ������, const boost::optional<const boost::property_tree::wptree &> &a��) {
		if (a��) {
			if (const std::wstring v���� = aȫ������.f�������Ʊ�ʶ(*a��); !v����.empty()) {
				a = v����;
			} else if (const auto &v���� = aȫ������.f�������ֱ�ʶ(*a��)) {
				a = v����.fgֵ();
			} else {
				a = 0;
			}
		} else {
			a = 0;
		}
	}
	template<typename t>
	static void f�������Ƹ�ֵ(t &a, const boost::optional<const boost::property_tree::wptree &> &a��) {
		if (a��) {
			if (const auto &v���Ʊ�ʶ = a��->get_optional<std::wstring>(L"����")) {
				a = *v���Ʊ�ʶ;
			} else {
				a = 0;
			}
		} else {
			a = 0;
		}
	}
	operator bool() const {
		return fi����();
	}
	std::wstring f�������Ʊ�ʶ(const boost::property_tree::wptree &a��) const {
		if (const auto &v���Ʊ�ʶ = a��.get_optional<std::wstring>(L"����")) {
			return *v���Ʊ�ʶ;
		} else {
			return L"";
		}
	}
	C�������� f�������ֱ�ʶ(const boost::property_tree::wptree &a��) const {
		bool v���� = false;
		int v���� = 0;
		int v������ = 0;
		if (const auto &v���ýڵ� = a��.get_optional<int>(L"��ʶ")) {
			v���� = *v���ýڵ�;
			v���� = true;
		}
		if (const auto &v�����ýڵ� = a��.get_optional<int>(L"�ӱ�ʶ")) {
			v������ = *v�����ýڵ�;
			v���� = true;
		}
		if (a��.get<bool>(L"����", false)) {
			return {����::f��ʶ(v����, 0, v������), v����};
		} else {
			return {����::f��ʶ(m����, v����, v������), v����};
		}
	}
	bool fi����() const {
		return m����;
	}
	int fgֵ() const {
		return m����;
	}
private:
	int m����;
	bool m����;
};
//����
class C��������json {
public:
	static std::wstring f����·��(const boost::property_tree::wptree &a��) {
		return a��.get<std::wstring>(L"·��");
	}
	static t����2 f�����ߴ�(const boost::property_tree::wptree &a��) {
		const float x = a��.get<float>(L"�ߴ�.��");
		const float y = a��.get<float>(L"�ߴ�.��");
		return {x, y};
	}
};
//����
class C��������json {
public:
	static void f����(int p��ʶ, const t����2 &p����ߴ�, const boost::property_tree::wptree &a��) {
		auto &v���㹤�� = C��Ϸ::g��Դ.fg���㹤��();
	}
};
//�ӻ��ƶ�
class C�����ӻ��ƶ�json {
public:
	typedef std::unique_ptr<I����<I�ӻ��ƶ�>> t����ֵ;
	typedef std::unique_ptr<I����<I�ӻ��ƶ�>> (*tf����)(int, const boost::property_tree::wptree &);
	static std::unique_ptr<I����<I�ӻ��ƶ�>> f����(int p����, int p�ӻ���, const boost::property_tree::wptree &a��) {
		static const std::map<int, tf����> v��������{
			{0, fλ��}
		};
		return v��������.at(p����)(p�ӻ���, a��);
	}
	static std::unique_ptr<I����<I�ӻ��ƶ�>> fλ��(int p�ӻ���, const boost::property_tree::wptree &a��) {
		const int v���� = (1 + p�ӻ���) * p�ӻ��� / 2;//=1+2+..+�ӻ���
		const int v������ = v���� * 2;
		std::vector<t����2> v����;
		//int i1 = 0;
		for (auto &v1 : a��) {
			const auto &v�ڵ�1 = v1.second;
			const float x = v�ڵ�1.get<float>(L"x", 0);
			const float y = v�ڵ�1.get<float>(L"y", 0);
			v����.emplace_back(x, y);
			assert(v����.size() <= v������);
		}
		auto va���� = std::make_shared<�ӻ��ƶ�::Cλ��::S����>(v����.data());
		return std::make_unique<�ӻ��ƶ�::Cλ��::C����>(va����);
	}
};
//=============================================================================
// ��������
//=============================================================================
void C����::f����(const S������� &a) {
	static const std::map<std::wstring, tf��������> v���뺯��{
		{L"�����б�0", f����},
		{L"ͼ��", fͼ��},
		{L"����", f����},
		{L"�����ӵ�", f�ӵ�},
		{L"���˷ɻ�", f�л�},
		{L"��ҷɻ�", f�Ի�},
		{L"����ӷɻ�", f�ӻ�},
		{L"����ӷɻ�.λ��", f�ӻ�λ��},
		//{L"��ҷ���", f��ҷ���},
		{L"����ӵ�", f����ӵ�},
		{L"�����б�0", f�����б�0},
		{L"ģ���б�0", fģ���б�0},
		{L"�����б�0", f�����б�0},
		{L"�����б�1", f�����б�1},
		{L"�ı�", f�ı�},
	};
	const boost::property_tree::wptree &v���� = a.m��.get_child(L"����");
	for (const auto &v0 : v����) {
		const std::wstring &v�ļ��� = v0.second.get_value<std::wstring>();
		boost::property_tree::wptree v��;
		std::filesystem::path v·��;
		C��json�ļ�::f��ȡ(v��, a, v�ļ���, v·��);
		const std::wstring v���� = v��.get<std::wstring>(L"ȫ��.����", L"");
		if (v����.empty()) {
			throw;
		}
		v���뺯��.at(v����)(S�������{v��, v·��});
	}
}
void C����::fͼ��(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring &vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0(vȫ������, vȫ�ֱ�ʶ);
	const boost::property_tree::wptree &va���� = a.m��.get_child(L"����");
	auto &v������ = C��Ϸ::g��Դ.fg������();
	auto &v���㹤�� = C��Ϸ::g��Դ.fg���㹤��();
	int v����ʶ = -1;
	for (const auto &[v����0_, v�ڵ�0] : va����) {
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const int vͼ�α�ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		const std::wstring &vͼ������ = v�ڵ�0.get<std::wstring>(L"����", std::wstring(L"ͼ��") + std::to_wstring(v����ʶ));
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(vͼ������);
		//����
		const t�� &v����ڵ� = v�ڵ�0.get_child(L"����");
		if (const std::wstring v����·�� = v����ڵ�.get<std::wstring>(L"·��", L""); !v����·��.empty()) {
			v������.f��������(vͼ�α�ʶ, C����::f����·��(v����·��, a.m·��).native());
		}
		const float v����ߴ�x = v����ڵ�.get<float>(L"�ߴ�.��", 0);
		const float v����ߴ�y = v����ڵ�.get<float>(L"�ߴ�.��", 0);
		const t����2 v����ߴ�{v����ߴ�x, v����ߴ�y};
		v���㹤��.m����.fs����ߴ�(v����ߴ�);
		//����
		int v��������ʶ = -1;
		int v�����ܱ�ʶ = -1;
		for (const auto &[v����1_, v�ڵ�1] : v�ڵ�0.get_child(L"����")) {
			const std::wstring v�������� = v�ڵ�1.get<std::wstring>(L"����", std::wstring(L"����") + std::to_wstring(++v��������ʶ));
			const C���Ʊ�ʶ v���Ʊ�ʶ2 = v���Ʊ�ʶ1.f������(v��������);
			const float x = v�ڵ�1.get<float>(L"x", 0);
			const float y = v�ڵ�1.get<float>(L"y", 0);
			const float v�� = v�ڵ�1.get<float>(L"��", v����ߴ�.x - x);
			const float v�� = v�ڵ�1.get<float>(L"��", v����ߴ�.y - y);
			const int v���� = v�ڵ�1.get<int>(L"����", 1);
			const int v���� = v�ڵ�1.get<int>(L"����", 1);
			const float vƫ��x = v�ڵ�1.get<float>(L"ƫ��x", 0);
			const float vƫ��y = v�ڵ�1.get<float>(L"ƫ��y", 0);
			const float v�ֿ� = v�� / (float)v����;
			const float v�ָ� = v�� / (float)v����;
			//��������
			const t����2 v����ߴ�{v�ֿ�, v�ָ�};
			v���㹤��.m����.fsӳ���_����({x, y});
			v���㹤��.m����.fs����ߴ�(v����ߴ�);
			v���㹤��.m����.fs��������ƫ��({vƫ��x, vƫ��y});
			int v�����ӱ�ʶ = -1;
			for (auto &vѭ�� : v���㹤��.fѭ��(v����, v����)) {
				const C���Ʊ�ʶ v���Ʊ�ʶ3 = v���Ʊ�ʶ2.f������(std::to_wstring(++v�����ӱ�ʶ));
				vѭ��.f�任_ƽ��(v����ߴ�);
				v���㹤��.f��������(����::f��ʶ(vͼ�α�ʶ, 0, ++v�����ܱ�ʶ));
			}
		}

		//if (const auto &v�и� = v�ڵ�0.get_child_optional(L"�����и�")) {
		//	const int v���� = v�и�->get<int>(L"����", 1);
		//	const int v���� = v�и�->get<int>(L"����", 1);
		//	v���㹤��.f�Զ���_�����и�(vͼ�α�ʶ, v����ߴ�, v����, v����);
		//} else {
		//	v���㹤��.f�Զ���_��������(vͼ�α�ʶ, v����ߴ�);
		//}
	}

}
void C����::f����(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	const boost::property_tree::wptree &va���� = a.m��.get_child(L"����");
	auto &va���� = C��Ϸ::g��Դ.fg����();
	int v����ʶ = -1;
	for (const auto &v0 : va����) {
		const auto &v�ڵ�0 = v0.second;
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const std::wstring v�������� = v�ڵ�0.get<std::wstring>(L"����", L"");
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v��������, v����ʶ);
		const int v������ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		C��ɫ����::S���� v����;
		const float v�仯�ٶ� = v�ڵ�0.get<float>(L"�仯�ٶ�", 8);
		const float vѭ���ٶ� = v�ڵ�0.get<float>(L"ѭ���ٶ�", 8);
		auto f���� = [&](C��ɫ����::S����::S�������� &a�ṹ, const boost::property_tree::wptree &a����) {
			a�ṹ.m��� = a����.get<int>(L"��ʼ", 0);
			a�ṹ.mѭ�� = a����.get<int>(L"ѭ��", 0);
			a�ṹ.m֡�� = a����.get<int>(L"֡��", 0);
			a�ṹ.m�仯�ٶ� = a����.get<float>(L"�仯�ٶ�", v�仯�ٶ�) / (float)c����Ƶ��;
			a�ṹ.mѭ���ٶ� = a����.get<float>(L"ѭ���ٶ�", vѭ���ٶ�) / (float)c����Ƶ��;
			a�ṹ.m���� = a����.get<bool>(L"����", false);
		};
		f����(v����.m����, v�ڵ�0.get_child(L"��������"));
		f����(v����.m����, v�ڵ�0.get_child(L"���ƶ���"));
		f����(v����.m����, v�ڵ�0.get_child(L"���ƶ���"));
		va����.f���(v������ʶ, new C��ɫ����::C����(std::make_shared<C��ɫ����::S����>(v����)));
	}
}
void C����::f�ӵ�(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	assert(c�ӵ���ʶ == vȫ�ֱ�ʶ);
	const boost::property_tree::wptree &va���� = a.m��.get_child(L"����");
	auto &v������ = C��Ϸ::g��Դ.fg������();
	auto &v���㹤�� = C��Ϸ::g��Դ.fg���㹤��();
	auto &va�ӵ����� = C��Ϸ::g��Դ.fg�ӵ�����();
	int v����ʶ = -1;
	for (const auto &v0 : va����) {
		const auto &v�ӵ��ڵ� = v0.second;
		v����ʶ = v�ӵ��ڵ�.get<int>(L"��ʶ", ++v����ʶ);
		const std::wstring v�ӵ����� = v�ӵ��ڵ�.get<std::wstring>(L"����", L"");
		const int v�ӵ���ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		//����
		const t�� &v����ڵ� = v�ӵ��ڵ�.get_child(L"����");
		const std::wstring v����·�� = v����ڵ�.get<std::wstring>(L"·��");
		v������.f��������(v�ӵ���ʶ, C����::f����·��(v����·��, a.m·��).native());
		//����
		const float v����ߴ�x = v����ڵ�.get<float>(L"�ߴ�.��");
		const float v����ߴ�y = v����ڵ�.get<float>(L"�ߴ�.��");
		v���㹤��.f�Զ���_��������(v�ӵ���ʶ, t����2{v����ߴ�x, v����ߴ�y});
		//����
		S�ӵ����� &v���� = va�ӵ�����.fȡ��(v�ӵ���ʶ);
		const int v�ж����� = v�ӵ��ڵ�.get<int>(L"�ж�.����");
		switch (v�ж�����) {
			case 0: {	//Բ��
				const float v����ߴ�d = (v����ߴ�x + v����ߴ�y) / 2;
				const float v�ж�r = v�ӵ��ڵ�.get<float>(L"�ж�.�ж�r", v����ߴ�d / 2);
				const float v����r = v�ӵ��ڵ�.get<float>(L"�ж�.����r", v����ߴ�d / 4);
				v����.m�ж� = t����2{v�ж�r, 0};
				v����.m�ж����� = t����2{v����r, v����r};
				break;
			}
			case 1: {	//����
				const float v�ж�x = v�ӵ��ڵ�.get<float>(L"�ж�.�ж�x", v����ߴ�x / 2);
				const float v�ж�y = v�ӵ��ڵ�.get<float>(L"�ж�.�ж�y", v����ߴ�y / 2);
				const float v����x = v�ӵ��ڵ�.get<float>(L"�ж�.����x", v����ߴ�x / 4);
				const float v����y = v�ӵ��ڵ�.get<float>(L"�ж�.����y", v����ߴ�y / 4);
				v����.m�ж� = t����2{v�ж�x, v�ж�y};
				v����.m�ж����� = t����2{v����x, v����y};
				break;
			}
			default:
				break;
		}
		v����.m���� = v�ӵ���ʶ;
		v����.m���� = v�ӵ���ʶ;
		v����.m����֡�� = 1;
		//va�ӵ�����.f���(v�ӵ���ʶ, v����);
	}
}
void C����::f�л�(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	const int vȫ�ֶ������� = a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0);
	const int vȫ�ֶ������� = a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0);
	auto &va�л����� = C��Ϸ::g��Դ.fg�л�����();
	auto &v������ = C��Ϸ::g��Դ.fg������();
	const auto &va���� = a.m��.get_child(L"����");
	int v����ʶ = -1;
	for (const auto &v0 : va����) {
		const auto &v�ڵ�0 = v0.second;
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const int v�л���ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		const std::wstring v�л����� = v�ڵ�0.get<std::wstring>(L"����", L""); 
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v�л�����, v����ʶ);
		auto &v���� = va�л�����.fȡ��(v�л���ʶ);
		v����.m�ж��뾶 = v�ڵ�0.get<float>(L"�ж��뾶", 16);
		const auto &v����·�� = v�ڵ�0.get_optional<std::wstring>(L"����.·��");
		if (v����·��) {
			v������.f��������(v�л���ʶ, C����::f����·��(*v����·��, a.m·��).native());
			v����.m���� = v�л���ʶ;
		} else {
			v����.m���� = nullptr;
		}
		C��������::f������ֵ(v����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
	}
}
void C����::f�Ի�(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	const int vȫ�ַ������� = a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0);
	const int vȫ�ֶ������� = a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0);
	const int vȫ�ֶ������� = a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0);
	const C�������� vȫ���ӵ����� = {a.m��.get<int>(L"ȫ��.�ӵ�.����.��ʶ", 0)};
	const auto &va���� = a.m��.get_child(L"����");
	auto &v������ = C��Ϸ::g��Դ.fg������();
	auto &va�Ի����� = C��Ϸ::g��Դ.fg�Ի�����();
	int v����ʶ = -1;
	for (const auto &v0 : va����) {
		const auto &v�ڵ�0 = v0.second;
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const int v�Ի���ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		const std::wstring v�Ի����� = v�ڵ�0.get<std::wstring>(L"����", L"");
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v�Ի�����, v����ʶ);
		auto &v���� = va�Ի�����.fȡ��(v�Ի���ʶ);
		//����
		const auto &v����·�� = v�ڵ�0.get_optional<std::wstring>(L"����.·��");
		if (v����·��) {
			v������.f��������(v�Ի���ʶ, C����::f����·��(*v����·��, a.m·��).native());
			v����.m���� = v�Ի���ʶ;
		} else {
			v����.m���� = nullptr;
		}
		//����
		v����.m�ж��뾶 = v�ڵ�0.get<float>(L"�ж��뾶", C�Ի�::c�ж��뾶);
		v����.m�����뾶 = v�ڵ�0.get<float>(L"�����뾶", C�Ի�::c�����뾶);
		v����.m���߰뾶 = v�ڵ�0.get<float>(L"���߰뾶", C�Ի�::c���߰뾶);
		v����.m�ƶ��ٶ� = v�ڵ�0.get<float>(L"�ƶ��ٶ�", C�Ի�::c�ƶ��ٶ�);
		C��������::f������ֵ(v����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v����.m�����ӵ�, vȫ�ַ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v����.m�ӵ�����, vȫ���ӵ�����, v�ڵ�0.get_child_optional(L"�ӵ�.����"));
	}
}
void C����::f�ӻ�(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	assert(c�ӻ���ʶ == vȫ�ֱ�ʶ);
	const C�������� vȫ���������� = {a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0)};
	const C�������� vȫ�ֶ������� = {a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0)};
	const C�������� vȫ���ƶ����� = {a.m��.get<int>(L"ȫ��.�ƶ�.����.��ʶ", 0)};
	const C�������� vȫ�ַ������� = {a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0)};
	const C�������� vȫ���ӵ����� = {a.m��.get<int>(L"ȫ��.�ӵ�.����.��ʶ", 0)};
	const auto &va���� = a.m��.get_child(L"����");
	auto &va�ӻ� = C��Ϸ::g��Դ.fg�ӻ�����();
	auto &va�ӻ��ƶ� = C��Ϸ::g��Դ.fg�ӻ��ƶ�();
	int v����ʶ = -1;
	for (const auto &v0 : va����) {
		const auto &v�ڵ�0 = v0.second;
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const int v�ӻ���ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		const std::wstring v�ӻ����� = v�ڵ�0.get<std::wstring>(L"����", L"");
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v�ӻ�����, v����ʶ);
		auto &v�ӻ����� = va�ӻ�.fȡ��(v�ӻ���ʶ);
		const int v���� = v�ڵ�0.get<int>(L"����", 0);
		//�ӻ���
		const int v�ӻ��� = v�ڵ�0.get<int>(L"�ӻ���", 0);
		v�ӻ�����.m�������� = v�ӻ���;

		C��������::f������ֵ(v�ӻ�����.m����, vȫ����������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v�ӻ�����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v�ӻ�����.m����, vȫ�ַ�������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v�ӻ�����.m�ӵ�����, vȫ���ӵ�����, v�ڵ�0.get_child_optional(L"�ӵ�.����"));
		//�ƶ�
		if (const auto &v�ӻ��ƶ��ڵ� = v�ڵ�0.get_child_optional(L"�ƶ�")) {
			if (const auto &v�ӻ��ƶ����ýڵ� = v�ӻ��ƶ��ڵ�->get_child_optional(L"����")) {
				C��������::f������ֵ(v�ӻ�����.m�ƶ�, vȫ���ƶ�����, v�ӻ��ƶ����ýڵ�);
			} else if (const auto &v�ӻ��ƶ����� = v�ӻ��ƶ��ڵ�->get_optional<int>(L"����")) {
				v�ӻ�����.m�ƶ� = v�ӻ���ʶ;
				va�ӻ��ƶ�.f���(v�ӻ���ʶ, C�����ӻ��ƶ�json::f����(*v�ӻ��ƶ�����, v�ӻ���, v�ӻ��ƶ��ڵ�->get_child(L"ֵ")).release());
			} else {
				v�ӻ�����.m�ƶ� = vȫ���ƶ�����.fgֵ();
			}
		} else {
			v�ӻ�����.m�ƶ� = vȫ���ƶ�����.fgֵ();
		}
	}
}
void C����::f�ӻ�λ��(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	assert(c�ӻ��ƶ���ʶ == vȫ�ֱ�ʶ);
	const auto &va���� = a.m��.get_child(L"����");
	auto &va�ӻ��ƶ� = C��Ϸ::g��Դ.fg�ӻ��ƶ�();
	for (const auto &v0 : va����) {
		const auto &v�ڵ�0 = v0.second;
		const int v�ӻ��ƶ���ʶ = vȫ�ֱ�ʶ + v�ڵ�0.get<int>(L"��ʶ");
		const int v���� = v�ڵ�0.get<int>(L"����", 0);
		const int v�ӻ��� = v�ڵ�0.get<int>(L"�ӻ���", 0);
		const auto &vaֵ = v�ڵ�0.get_child(L"ֵ");
		va�ӻ��ƶ�.f���(v�ӻ��ƶ���ʶ, C�����ӻ��ƶ�json::f����(v����, v�ӻ���, vaֵ).release());
	}
}
void C����::f����ӵ�(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	const C�������� vȫ�ֶ������� = {a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0)};
	const C�������� vȫ���������� = {a.m��.get<int>(L"ȫ��.����.����.��ʶ", 0)};
	const auto &va���� = a.m��.get_child(L"����");
	auto &va����ӵ����� = C��Ϸ::fg��Դ().fg����ӵ�����();
	int v����ʶ = -1;
	for (const auto &[v����0_, v�ڵ�0] : va����) {
		v����ʶ = v�ڵ�0.get<int>(L"��ʶ", ++v����ʶ);
		const std::wstring v����ӵ����� = v�ڵ�0.get<std::wstring>(L"����", L"");
		const int v����ӵ���ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ʶ, 0);
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v����ӵ�����, v����ʶ);
		auto &v����ӵ����� = va����ӵ�����.fȡ��(v����ӵ���ʶ);
		//ͼ��
		C��������::f������ֵ(v����ӵ�����.m����, vȫ����������, v�ڵ�0.get_child_optional(L"����.����"));
		C��������::f������ֵ(v����ӵ�����.m����, vȫ�ֶ�������, v�ڵ�0.get_child_optional(L"����.����"));
		if (auto v��ʧ���� = v�ڵ�0.get_child_optional(L"��ʧ����.����")) {
			C��������::f������ֵ(v����ӵ�����.m��ʧ����, vȫ����������, v��ʧ����);
		} else {
			v����ӵ�����.m��ʧ���� = v����ӵ�����.m����;
		}
		if (auto v��ʧ���� = v�ڵ�0.get_child_optional(L"��ʧ����.����")) {
			C��������::f������ֵ(v����ӵ�����.m��ʧ����, vȫ�ֶ�������, v��ʧ����);
		} else {
			v����ӵ�����.m��ʧ���� = v����ӵ�����.m����;
		}
		v����ӵ�����.m����֡�� = v�ڵ�0.get<int>(L"����֡��", 0);
		v����ӵ�����.m��ʧ֡�� = v�ڵ�0.get<int>(L"��ʧ֡��", 0);
		v����ӵ�����.m�˺� = v�ڵ�0.get<int>(L"�˺�", 10);
		//�ж�
		if (const auto &v�ж��ڵ� = v�ڵ�0.get_child_optional(L"�ж�")) {
			const int v���� = v�ж��ڵ�->get<int>(L"����", 0);
			switch (v����) {
			case 0:	//Բ��
				v����ӵ�����.m�ж�.x = v�ж��ڵ�->get<float>(L"�ж�r", 4);
				break;
			case 1:	//����
				v����ӵ�����.m�ж�.x = v�ж��ڵ�->get<float>(L"�ж�x", 4);
				v����ӵ�����.m�ж�.y = v�ж��ڵ�->get<float>(L"�ж�y", 4);
				break;
			default:
				v����ӵ�����.m�ж�.x = 4;
				break;
			}
		}
	}
}
void C����::f��ҷ���(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	assert(c��ҷ����ʶ == vȫ�ֱ�ʶ);
	const auto &va���� = a.m��.get_child(L"����");
	auto &va��ҷ��� = C��Ϸ::g��Դ.fg��ҷ���();
	for (const auto &v0 : va����) {
		const auto &v����ڵ� = v0.second;
		const int v�����ʶ = ����::f��ʶ(vȫ�ֱ�ʶ, v����ڵ�.get<int>(L"��ʶ"), 0);
		const int v������� = v����ڵ�.get<int>(L"����");
		switch (v�������) {
			case 1:
			{	//��ɢ
				const int v���� = v����ڵ�.get<int>(L"����");
				const int v��ɢ0 = v����ڵ�.get<int>(L"��ɢ0");
				const int v��ɢ1 = v����ڵ�.get<int>(L"��ɢ1");
				const int v����0 = v����ڵ�.get<int>(L"����0");
				const int v����1 = v����ڵ�.get<int>(L"����1");
				const auto v������� = ����ӵ�����::C��ɢ::S����::fc��(v����, v��ɢ0, v��ɢ1, v����0, v����1);
				//va��ҷ���.f���(v�����ʶ, new ����ӵ�����::C��ɢ::C����(v�������));
				va��ҷ���.f����<����ӵ�����::C��ɢ::C����>(v�����ʶ, v�������);
				break;
			}
			default:
				break;
		}
	}

}
void C����::f�����б�0(const S������� &a) {
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = std::wstring(L"����.") + a.m��.get<std::wstring>(L"ȫ��.����");
	const auto &va���� = a.m��.get_child(L"����");
	auto &v������ = C��Ϸ::fg��Դ().fg������();
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	int v����ʶ = -1;
	for (const auto &[v����0, v��0] : va����) {
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v����0, ++v����ʶ);
		v������.f��������(v���Ʊ�ʶ1.fg��ʶ(), C����::f����·��(v��0.get_value<std::wstring>(), a.m·��));
	}
}
void C����::fģ���б�0(const S������� &a) {
	const std::wstring cģ������ = L"ģ��";
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = std::wstring(L"ģ��.") + a.m��.get<std::wstring>(L"ȫ��.����");
	const auto &va���� = a.m��.get_child(L"����");
	auto &vģ�͹��� = C��Ϸ::fgͼ��().fgģ�͹���();
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ); 
	int v����ʶ = -1;
	for (const auto &[v����0_, v��0] : va����) {
		const std::wstring &v����0 = v��0.get<std::wstring>(L"����", cģ������ + std::to_wstring(++v����ʶ));
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v����0, v����ʶ);
		std::vector<S��ά����> va����;
		for (const auto &[v����1_, v��1] : v��0.get_child(L"����")) {
			S��ά���� v����;
			v����.m����.x = v��1.get<float>(L"����.x", 0);
			v����.m����.y = v��1.get<float>(L"����.y", 0);
			v����.m����.z = v��1.get<float>(L"����.z", 0);
			v����.m����.x = v��1.get<float>(L"����.u", 0);
			v����.m����.y = v��1.get<float>(L"����.v", 0);
			va����.push_back(v����);
		}
		std::vector<��ά::t����> va����;
		for (const auto &[v����1_, v��1] : v��0.get_child(L"����")) {
			const ��ά::t���� v���� = v��1.get_value<��ά::t����>(0);
			va����.push_back(v����);
		}
		vģ�͹���.m����.fs����(va����.data(), va����.size());
		vģ�͹���.m����.fs����(va����.data(), va����.size());
		vģ�͹���.f����ģ��(v���Ʊ�ʶ1.fg��ʶ());
	}
}
void C����::f�����б�0(const S������� &a) {
	const std::wstring cģ������ = L"ģ��";
	const int vȫ�ֱ�ʶ = a.m��.get<int>(L"ȫ��.��ʶ", ����::fc�����ʶ());
	const std::wstring vȫ������ = std::wstring(L"����.") + a.m��.get<std::wstring>(L"ȫ��.����");
	const auto &va���� = a.m��.get_child(L"����");
	auto &v�������� = C��Ϸ::fg��Ƶ().fg��������();
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	int v����ʶ = -1;
	for (const auto &[v����0, v��0] : va����) {
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v����0, ++v����ʶ);
		v��������.f��������(v���Ʊ�ʶ1.fg��ʶ(), C����::f����·��(v��0.get_value<std::wstring>(), a.m·��));
	}
}
void C����::f�����б�1(const S������� &) {

}
void C����::f�ı�(const S������� &a) {
	const int vȫ�ֱ�ʶ = ����::fc�����ʶ();
	const std::wstring vȫ������ = a.m��.get<std::wstring>(L"ȫ��.����");
	const std::wstring v���� = a.m��.get<std::wstring>(L"ȫ��.����");
	const auto &va���� = a.m��.get_child(L"����");
	auto &va�ı� = C��Ϸ::fg��Դ().f���ı�����(vȫ������, v����);
	const C���Ʊ�ʶ v���Ʊ�ʶ0 = C���Ʊ�ʶ(vȫ������, vȫ�ֱ�ʶ);
	int v����ʶ = -1;
	for (const auto &[v����0, v��0] : va����) {
		const C���Ʊ�ʶ v���Ʊ�ʶ1 = v���Ʊ�ʶ0.f������(v����0, ++v����ʶ);
		va�ı�.f���(v���Ʊ�ʶ1.fg��ʶ(), v��0.get_value<std::wstring>());
	}
}
//=============================================================================
// �ڲ�����
//=============================================================================
void C�ڲ�����::f����() {
	auto &va�������� = C��Ϸ::fg��Դ().fg��������();
	struct S��������0 {
		E���� m��ʶ;
		tf����Ч�� mЧ������;
		int mЧ��ֵ;
		float m�ж��뾶;
		float m���͸��;
		int mͼ�α�ʶ;
		int mͼ���ӱ�ʶ;
	} v�������Ա�[] = {
		//���			Ч��						ֵ �뾶 ͸��	ͼ�α�ʶ
		{E����::e�л�,		����Ч��::f�л�_ʮ��֮һ,	10, 8, 1,		0, 1},
		{E����::e�л���Ƭ,	����Ч��::f�л�_ʮ��֮һ,	3, 8, 1	,		0, 0},
		{E����::eը��,		����Ч��::fը��_ʮ��֮һ,	10, 8, 1,		0, 3},
		{E����::eը����Ƭ,	����Ч��::fը��_ʮ��֮һ,	3, 8, 1,		0, 2},
		{E����::e����,		����Ч��::f����_�ٷ�֮һ,	1, 4, 1,		1, 0},
		{E����::e�õ�,		����Ч��::f�÷�_����,		1, 4, 1,		1, 1},
		{E����::e����,	����Ч��::f����,			1000, 4, 1,		1, 2},
		{E����::e΢����,	����Ч��::f����,			10, 4, 0.2f,	1, 3},
	};
	for (auto &v : v�������Ա�) {
		S�������� &v���� = va��������.fȡ��((int)v.m��ʶ);
		v����.mfЧ�� = v.mЧ������;
		v����.mֵ = v.mЧ��ֵ;
		v����.m�ж��뾶 = v.m�ж��뾶;
		v����.m���͸���� = v.m���͸��;
		const int v����ͼ�α�ʶ = ����::f��ʶ(c���߱�ʶ, v.mͼ�α�ʶ, 0);
		v����.m���� = v����ͼ�α�ʶ;
		v����.m���� = ����::f��ʶ(v����ͼ�α�ʶ, 0, v.mͼ���ӱ�ʶ);
		v����.m���� = (int)E����::e����;
	}
}
void C�ڲ�����::f���ӵ�() {
	auto &vͼ�� = C��Ϸ::fgͼ��();
	std::pair<E���ӵ�, I���ӵ�*> v���ӵ���[] = {
		{E���ӵ�::e����, new C���ӵ�_����(vͼ��, *vͼ��.m��ά)},
		{E���ӵ�::e����, new C���ӵ�_����(*vͼ��.m��ά)},
	};
	auto &va���ӵ� = C��Ϸ::fg��Դ().fg���ӵ�();
	for (auto &v : v���ӵ���) {
		va���ӵ�.f���((int)v.first, v.second);
	}
}
void C�ڲ�����::f�ӻ�() {
	auto &va�ӻ����� = C��Ϸ::g��Դ.fg�ӻ�����();
	struct {
		E�ӻ� v����;
		int v����;
		E��ҷ��� v����;
		E�ӻ��ƶ� v�ƶ�;
	} v�ӻ����Ա�[] = {
		//���			����	����						�ƶ�
		{E�ӻ�::e����, 4, E��ҷ���::e�����յ�, E�ӻ��ƶ�::eλ��},
	};
	for (auto &v : v�ӻ����Ա�) {
		S�ӻ����� v����;
		v����.m�������� = v.v����;
		v����.m���� = (int)v.v����;
		v����.m�ƶ� = (int)v.v�ƶ�;
		va�ӻ�����.f���((int)v.v����, v����);
	}
}
void C�ڲ�����::f����ӵ�() {
	typedef std::tuple<E����ӵ�, t����2> t;
	t v����ӵ����Ա�[] = {
		//����					�ж�
		t{E����ӵ�::e�����ӵ�, {4, 4}}
	};
	auto &va����ӵ����� = C��Ϸ::g��Դ.fg����ӵ�����();
	for (auto &v : v����ӵ����Ա�) {
		S����ӵ����� &v���� = va����ӵ�����.fȡ��((int)std::get<0>(v));
		v����.m�ж� = std::get<1>(v);
		v����.m���� = nullptr;
		v����.m֡��ߴ� = {};
		v����.m����֡�� = 0;
	}
}
void C�ڲ�����::f����ӵ�����() {
	struct S���÷�������{
		E��ҷ��� m��ʶ;
		I����<C����ӵ�������> *m�������;
	};
	const S���÷������� v��ҷ����[] = {
		{E��ҷ���::e�����ӵ�, new C�򵥹���<C����ӵ�������, ����ӵ�����::C�Ի�����>()},
		{E��ҷ���::e�Ի�����, new C�򵥹���<C����ӵ�������, ����ӵ�����::C�Ի�����>()},
		{E��ҷ���::e�����յ�, new C�򵥹���<C����ӵ�������, ����ӵ�����::C�����յ�>()},
		{E��ҷ���::e���μ���, new C�򵥹���<C����ӵ�������, ����ӵ�����::C���μ���>()},
		{E��ҷ���::eħ��ɳ�ᴩ, new C�򵥹���<C����ӵ�������, ����ӵ�����::Cħ��ɳ�ᴩ>()},
		{E��ҷ���::eħ��ɳ��Χ, new C�򵥹���<C����ӵ�������, ����ӵ�����::Cħ��ɳ��Χ>()},
		{E��ҷ���::eȫ���嵯, new C�򵥹���<C����ӵ�������, C���ը���򵥷�����<���ը��::Cȫ���嵯>>()},
		{E��ҷ���::e����ը��, new C�򵥹���<C����ӵ�������, C���ը���򵥷�����<���ը��::C����¼>>()},
	};
	auto &va��ҷ��� = C��Ϸ::g��Դ.fg��ҷ���();
	for (auto &v : v��ҷ����) {
		va��ҷ���.f���((int)v.m��ʶ, v.m�������);
	}
}
void C�ڲ�����::f����() {
	struct S���ö������� {
		E���� m������ʶ;
		I����<I����> *m��������;
	};
	const S���ö������� v���ö�����[] = {
		{E����::e��̬, new C�򵥹���<I����>},
		{E����::e����, new C�򵥹���<I����, C���߶���>},
	};
	auto &va������չ = C��Ϸ::g��Դ.fg����();
	for (auto &v : v���ö�����) {
		va������չ.f���((int)v.m������ʶ, v.m��������);
	}
}
void C�ڲ�����::fģ��() {
	auto &v���Ʊ�ʶ = C��Ϸ::fg��Դ().fg���Ʊ�ʶ();
	//����
	����::C�Զ������� v����;
	v����.f��ʼ��(2, 2);
	v����.fg����(0, 0) = ��ѧ::S��ɫ(1, 0, 0);
	v����.fg����(0, 1) = ��ѧ::S��ɫ(0, 1, 0);
	v����.fg����(1, 0) = ��ѧ::S��ɫ(0, 0, 1);
	v����.fg����(1, 1) = ��ѧ::S��ɫ(1, 1, 0);
	auto &vͼ�� = C��Ϸ::fgͼ��();
	auto &v������ = vͼ��.fg������();
	tp���� v������ = v������.f��������((int)E����::e����, v����);
	v���Ʊ�ʶ[L"����.΢��"] = ����::fc�����ʶ();
	//ģ��
	auto &vģ�͹��� = vͼ��.fgģ�͹���();
	int v��ʶ = ����::fc�����ʶ();
	const std::wstring c��ʶ���� = L"ģ��.ƽ��.";
	const uint16_t cƽ������[] = {
		0, 1, 2,
		1, 3, 2
	};
	//ƽ��ģ��
	for (int x = 1; x < 8; ++x) {
		for (int y = 1; y < 8; ++y) {
			const float v�� = powf(2, x);
			const float v�� = powf(2, y);
			const std::wstring v���� = c��ʶ���� + std::to_wstring((int)v��) + L"x" + std::to_wstring((int)v��);
			const int v��ʶ0 = (v��ʶ++);
			v���Ʊ�ʶ[v����] = v��ʶ0;
			const float v��� = v�� / 2;
			const float v��� = v�� / 2;
			const S��ά���� v����[] = {
				{{-v���, v���, 0}, {0, 0}},
				{{v���, v���, 0}, {0, 1}},
				{{-v���, -v���, 0}, {1, 0}},
				{{v���, -v���, 0}, {1, 1}}
			};
			vģ�͹���.m����.fs����(v����, _countof(v����));
			vģ�͹���.m����.fs����(cƽ������, _countof(cƽ������));
			vģ�͹���.f����ģ��(v��ʶ0);
		}
	}
}
//==============================================================================
// ������
//==============================================================================
void f����() {
	const std::filesystem::path v�����ļ� = c�����ļ�;
	boost::property_tree::wptree v����;
	C��json�ļ�::f��ȡ(v����, v�����ļ�);
	C����::f����({v���� , v�����ļ�});
	C�ڲ�����::f���ӵ�();
	//C�ڲ�����::f�ӻ�();
	//C�ڲ�����::f����ӵ�();
	C�ڲ�����::f����ӵ�����();
	C�ڲ�����::f����();
	C�ڲ�����::f����();
	C�ڲ�����::fģ��();
	C����::fs��Ϸ��־((int)E��Ϸ��־::e����0);
}
}	//namespace ����ɽկ