#pragma once
#include <string>
#include <memory>
#include <vector>
namespace ����ɽկ {
class C���Ʊ�ʶ {
public:
	static int f��������(const std::wstring &����);
	static void f�������Ʊ�ʶ(const std::wstring &��, const std::wstring &��);
	C���Ʊ�ʶ(const std::wstring &����, int ��ʶ = 0);
	C���Ʊ�ʶ(const std::wstring &����, int ��ʶ, C���Ʊ�ʶ const*);
	C���Ʊ�ʶ(const C���Ʊ�ʶ &) = delete;
	C���Ʊ�ʶ(C���Ʊ�ʶ &&);
	~C���Ʊ�ʶ();
	void fs����(const std::wstring &����);
	C���Ʊ�ʶ f������(const std::wstring &����, int ��ʶ = 0) const;
	int fg��ʶ() const;
	int fg�����ʶ() const;
	int fg����ʶ() const;
	int fg�ӱ�ʶ() const;
private:
	void f�������Ʊ�ʶ() const;
	std::wstring m����;
	std::shared_ptr<std::vector<int>> m��ʶ;
	int m�� = 0;
	bool mi�ɴ���;
};
}