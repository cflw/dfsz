#pragma once
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <filesystem>
#include <memory>
namespace ����ɽկ {
struct S������� {
	const boost::property_tree::wptree &m��;
	const std::filesystem::path &m·��;
};
class C���� {
public:
	typedef std::unique_ptr<boost::property_tree::wptree> tp��;
	typedef boost::property_tree::wptree t��;
	typedef void(*tf��������)(const S������� &);
	static std::map<int, tf��������> g���뺯��;
	static void f����(const S������� &);
	static void f�ӵ�(const S������� &);
	static void fͼ��(const S������� &);
	static void f����(const S������� &);
	static void f�Ի�(const S������� &);
	static void f�л�(const S������� &);
	static void f�ӻ�(const S������� &);
	static void f�ӻ�λ��(const S������� &);
	static void f����ӵ�(const S������� &);
	static void f��ҷ���(const S������� &);
	static void f�����б�0(const S������� &);
	static void fģ���б�0(const S������� &);
	static void f�����б�0(const S������� &);
	static void f�����б�1(const S������� &);
	static void f�ı�(const S������� &);
};
class C�ڲ����� {
public:
	static void f����();
	static void f���ӵ�();
	static void f�ӻ�();
	static void f����ӵ�();
	static void f����ӵ�����();
	static void f����();
	static void fģ��();
};
}