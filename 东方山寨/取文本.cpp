#include "ȡ�ı�.h"
#include "��Ϸ.h"
namespace ����ɽկ {
namespace ���� {
std::wstring f�ı�����ǰ׺(const std::wstring &a����, const std::wstring &a����) {
	return a���� + L"." + a����;
}
}	//namespace ����
const std::wstring c���ı� = L"(��)";
Cȡ�ı�::Cȡ�ı�(const C��������<std::wstring> &a����, const std::wstring &a����):
	ma�ı�(&a����), m����(a���� + L".") {
}
const std::wstring &Cȡ�ı�::operator [](const std::wstring &a����) const {
	const std::wstring v���� = f��������(a����);
	const auto &va���Ʊ�ʶ = C��Ϸ::fg��Դ().fg���Ʊ�ʶ();
	if (auto v�� = va���Ʊ�ʶ.find(v����); v�� != va���Ʊ�ʶ.end()) {
		return ma�ı�->fg����(v��->second);
	} else {
		return c���ı�;
	}
}
std::wstring Cȡ�ı�::f��������(const std::wstring &a����) const {
	return m���� + a����;
}

}	//namespace ����ɽկ