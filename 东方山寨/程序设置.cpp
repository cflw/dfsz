#include <locale>
#include <filesystem>
#include <boost/property_tree/json_parser.hpp>
#include <cflw�Ӵ�.h>
#include <cflw�ļ�_json.h>
#include "��������.h"
#include "����.h"
namespace ����ɽկ {
namespace �Ӵ� = cflw::�Ӵ�;
using t�����ļ� = cflw::�ļ�::json::C�ļ�;
using t������ = boost::property_tree::wptree;
//����
const std::wstring C��������::c���������ļ��� = std::wstring(L"setting0-") + �Ӵ�::C����::fg���������() + L".json";
const std::wstring C��������::c��Ϸ�����ļ��� = L"stg0.json";
//const std::filesystem::path C��������::c�����ļ�Ŀ¼ = L"%UserProfile%/AppData/Roaming/cflw/public";	//Ӧ������Ŀ¼
const std::filesystem::path C��������::c�����ļ�Ŀ¼ = �Ӵ�::C����::fg����Ŀ¼();	//��ǰĿ¼
const std::filesystem::path C��������::c���������ļ�·�� = c�����ļ�Ŀ¼ / c���������ļ���;
const std::filesystem::path C��������::c��Ϸ�����ļ�·�� = c�����ļ�Ŀ¼ / c��Ϸ�����ļ���;
//����
bool fд�����ļ�(const std::filesystem::path &a·��, const t������ &a��) {
	t�����ļ� v�ļ�;
	if (v�ļ�.f��(a·��, std::ios::out)) {
		v�ļ�.fд��(a��);
		return true;
	}
	return false;
}
C�������� &C��������::fg��() {
	static C�������� v��;
	return v��;
}
void C��������::f��ʼ����() {
	const auto f����Ĭ������ = [&, vĬ������ = �Ӵ�::C��������::fg��������()](std::wstring &a����) {
		if (a����.empty()) {
			a���� = vĬ������;
			mi����������� = true;
		}
	};
	f����Ĭ������(m�ı�����);
	f����Ĭ������(m��������);
}
bool C��������::f������() {
	const bool v�򿪳������� = f�򿪳�������();
	const bool v����Ϸ���� = f����Ϸ����();
	return v�򿪳������� && v����Ϸ����;
}
bool C��������::f��������() {
	const bool v����������� = f�����������();
	const bool v������Ϸ���� = f������Ϸ����();
	return v����������� && v������Ϸ����;
}
bool C��������::f�򿪳�������() {
	t�����ļ� v�ļ�;
	if (v�ļ�.f��(c���������ļ�·��)) {
		v�ļ�.f��ȡ(m����������);
		if (auto vp���� = m����������.get_child_optional(L"����")) {
			m�ı����� = vp����->get<std::wstring>(L"����.�ı�����", L"");
			m�������� = vp����->get<std::wstring>(L"����.��������", L"");
		}
		//����
		mi����������� = false;
		return true;
	}
	return false;
}
bool C��������::f����Ϸ����() {
	t�����ļ� v�ļ�;
	if (v�ļ�.f��(c��Ϸ�����ļ�·��)) {
		v�ļ�.f��ȡ(m��Ϸ������);
		if (auto vp���� = m��Ϸ������.get_child_optional(L"����")) {

		}
		//����
		mi������Ϸ���� = false;
		return true;
	}
	return false;
}
bool C��������::f�����������() {
	if (!mi�����������) {
		return true;
	}
	if (m����������.empty()) {
		t������ vȫ��, v����;
		vȫ��.add(L"����", L"��������");
		vȫ��.add(L"����", L"��������");
		m����������.add_child(L"ȫ��", vȫ��);
		v����.add(L"�������", L"");
		v����.add_child(L"����", {});
		v����.add_child(L"ͼ��", {});
		v����.add_child(L"����", {});
		m����������.add_child(L"����", v����);
	}
	t������ &v���� = m����������.get_child(L"����");
	v����.put(L"�������", m�������);
	t������ &v���� = v����.get_child(L"����");
	v����.put(L"�ı�����", m�ı�����);
	v����.put(L"��������", m��������);
	t������ &vͼ�� = v����.get_child(L"ͼ��");
	//�����ļ�
	const bool v������ = fд�����ļ�(c���������ļ�·��, m����������);
	mi����������� = !v������;
	return v������;
}
bool C��������::f������Ϸ����() {
	if (!mi������Ϸ����) {
		return true;
	}
	if (m��Ϸ������.empty()) {
		t������ vȫ��, v����;
		vȫ��.add(L"����", L"stg0");
		vȫ��.add(L"����", L"��������");
		m��Ϸ������.add_child(L"ȫ��", vȫ��);
		v����.add_child(L"�ֱ�", {});
		m��Ϸ������.add_child(L"����", v����);
	}
	t������ &v���� = m��Ϸ������.get_child(L"����");
	t������ &v�ֱ� = v����.get_child(L"�ֱ�");
	v�ֱ�.put<int>(L"���", (int)ca�ֱ�ӳ��.at(E����::e���));
	v�ֱ�.put<int>(L"ը��", (int)ca�ֱ�ӳ��.at(E����::eը��));
	v�ֱ�.put<int>(L"����", (int)ca�ֱ�ӳ��.at(E����::e����));
	//v�ֱ�.put<int>(L"�ͷ�", (int)ca�ֱ�ӳ��.at(E����::e�ͷ�));
	//�����ļ�
	const bool v������ = fд�����ļ�(c��Ϸ�����ļ�·��, m��Ϸ������);
	mi����������� = !v������;
	return v������;
}
const std::wstring &C��������::fg�ı�����() const {
	return m�ı�����;
}
const std::wstring &C��������::fg��������() const {
	return m��������;
}
}