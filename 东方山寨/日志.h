#pragma once
#include <string>
#include <deque>
#include <cflwʱ��.h>
#include <cflwͼ��_d2d.h>
namespace ʱ�� = cflw::ʱ��;
namespace ��ά = cflw::ͼ��::d2d;
namespace ����ɽկ {
class C��־ {
public:
	enum E���� {
		e����,
		e����,
		e����,
		e��Ϣ,
	};
	struct S��־ {
		ʱ��::tʱ��� mʱ��;
		E���� m����;
		std::wstring m�ı�;
		float m���� = 0;
		float m��ʧ = 0;
		float fg͸����() const;
	};
	static constexpr float c�о� = 12;
	C��־(��ά::C��ά &);
	void f���(E����, const std::wstring &);
	void f����();
	void f��ʾ() const;
	std::deque<S��־> ma��־;
	std::shared_ptr<��ά::C���ı�> m���ı�;
	float m��ʾλ��y = -240;
};
}	//namespace ����ɽկ