#pragma once
#include <string>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
namespace ����ɽկ {
class C�������� {
public:
	static const std::wstring c���������ļ���;
	static const std::wstring c��Ϸ�����ļ���;
	static const std::filesystem::path c�����ļ�Ŀ¼;
	static const std::filesystem::path c���������ļ�·��;
	static const std::filesystem::path c��Ϸ�����ļ�·��;
	static C�������� &fg��();
	void f��ʼ����();	//�� f������ ʧ�ܺ����
	bool f������();
	bool f��������();
	const std::wstring &fg�ı�����() const;
	const std::wstring &fg��������() const;
public:
	bool f�򿪳�������();
	bool f����Ϸ����();
	bool f�����������();
	bool f������Ϸ����();
	bool mi����������� = true, mi������Ϸ���� = true;	//����ָʾ,���޸Ĳ�����
	boost::property_tree::wptree m����������, m��Ϸ������;
	std::wstring m�������;
	std::wstring m�ı�����;
	std::wstring m��������;
};
}