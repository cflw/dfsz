#pragma once
#include <map>
#include <memory>
#include <string>
#include <filesystem>
#include <Windows.h>
namespace ����ɽկ {
enum class E��Ϸ״̬ {
	e��,
	e������,
	e���˵�,
	e��Ϸ��,
	e��Ϸ�˵�,
	e�˳�,
};
enum class E��Ϸ��־ {
	e����0,
	e����1,
	e����,
};
class C��Ϸ;
class C��������;
class Cͼ������;
class C��Ƶ����;
class C����ͼ�ο���;
class C���� {
public:
	static void f��ʼ��(HINSTANCE);
	static void f����();
	static void f����();
	static C��Ϸ &fg��Ϸ();
	static C�������� &fg����();
	static Cͼ������ &fgͼ��();
	static C��Ƶ���� &fg��Ƶ();
	static C����ͼ�ο��� &fg����ͼ��();
	static std::filesystem::path f����·��(const std::filesystem::path &Ŀ��, const std::filesystem::path & p��ǰ�ļ� = L"");
	static const std::filesystem::path &fg����Ŀ¼();
	static void f���뷨����(bool);
	static int fg��Ⱦ���();
	static void f�л���Ϸ״̬(E��Ϸ״̬);
	static void fs��Ϸ��־(int ��־, bool ֵ = true);
	static void f��־(int ����, const std::wstring &);
private:
	class Cʵ��;
	static std::unique_ptr<Cʵ��> mʵ��;
};
}	//namespace ����ɽկ