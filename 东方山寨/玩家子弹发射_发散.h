#pragma once
#include "����ӵ��������.h"
namespace ����ɽկ {
namespace ����ӵ����� {
class C��ɢ : public C����ӵ������� {
public:
	struct S���� {
		static S���� fc���(int ����, float ��ɢ0, float ��ɢ1, float ����0, float ����1);
		static S���� fc��(int ����, float ��ɢ0, float ��ɢ1, float ����0, float ����1);
		S����(int ����, std::pair<float, float> ��ɢ, std::pair<float, float> ���);
		int m����;
		std::pair<float, float> m�����ſ��Ƕ�;
		std::pair<float, float> mˮƽ������;
	};
	class C���� : public I����<C����ӵ�������> {
	public:
		C����(const S���� &);
		C����ӵ������� *f�ӿ�_�½�() const override;
		std::shared_ptr<S����> m����;
	};
	C��ɢ(const std::shared_ptr<S����> &);
	void f�ӿ�_�����ӵ�() override;
private:
	std::shared_ptr<S����> m����;
};
}
}