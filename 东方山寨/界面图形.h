#pragma once
#include "����.h"
#include "ͼ�λ���.h"
#include "����.h"
namespace ����ɽկ {
namespace ����ͼ�� {
class C��������;
class C��;
}	//namespace ����ͼ��
class C����ͼ�ο��� {
public:
	static constexpr int c���� = 200;
	enum E��־ {
		e��,
	};
	enum Eͼ�� {
		e����,
		e��,
		eǰ��,
		e��
	};
	C����ͼ�ο���();
	~C����ͼ�ο���();
	void f����();
	void f����(bool);
	void f��������(bool);
	void f��(bool);
	t��־ m��־;
	std::shared_ptr<����ͼ��::C��������> m��������;
	std::shared_ptr<����ͼ��::C��> ma��[c����];
	float m��͸���� = 0;
};
}	//namespace ����ɽկ