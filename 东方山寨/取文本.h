#pragma once
#include <string>
#include "����_����.h"
namespace ����ɽկ {
namespace ���� {
std::wstring f�ı�����ǰ׺(const std::wstring &a����, const std::wstring &a����);
}
class Cȡ�ı� {
public:
	Cȡ�ı�(const C��������<std::wstring> &����, const std::wstring &����);
	const std::wstring &operator [](const std::wstring &) const;
	std::wstring f��������(const std::wstring &) const;
	const C��������<std::wstring> *ma�ı�;
	std::wstring m����;
};
}