#pragma once
#include "����ӵ��������.h"
#include "����ӵ���չ.h"
namespace ����ɽկ::����ӵ����� {
class C�Ի����� : public C����ӵ������� {
public:
	void f�ӿ�_�����ӵ�() override;
};
class C�����յ� : public C����ӵ������� {
public:
	static constexpr float c�ٶȴ�С = 800;
	static constexpr float c������ = 0.06f;
	C�����յ�();
	void f�ӿ�_�����ӵ�() override;
};
class C���μ��� : public C����ӵ������� {
public:
	void f�ӿ�_�����ӵ�() override;
};
class Cħ��ɳ�ᴩ : public C����ӵ������� {
public:
	void f�ӿ�_����() override;
	void f�ӿ�_�����ӵ�() override;
	bool fi���ӵ�() const;
private:
	std::shared_ptr<����ӵ�::C�ᴩ> m�ӵ�;
};
class Cħ��ɳ��Χ : public C����ӵ������� {
public:
	static constexpr float c������ = 0.1f;
	static constexpr float c�ٶȴ�С = 600;
	Cħ��ɳ��Χ();
	void f�ӿ�_�����ӵ�() override;
};
}