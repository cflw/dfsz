#pragma once
#include "�����ӿ�.h"
namespace ����ɽկ {
//=============================================================================
// ��ɫ����
//=============================================================================
class C��ɫ���� : public I���� {
public:
	struct S���� {
		struct S�������� {
			int m���;
			int mѭ��;
			int m֡��;
			float m�仯�ٶ�;
			float mѭ���ٶ�;
			bool m����;
		};
		S�������� m����, m����, m����;
	};
	class C���� : public I����<I����> {
	public:
		C����(std::shared_ptr<S����>);
		I���� *f�ӿ�_�½�() const override;
		std::shared_ptr<S����> m����;
	};
	C��ɫ����(std::shared_ptr<S����>);
	void f�ӿ�_����() override;
	void f�ӿ�_����(const E�������� &, const t��������ֵ &) override;
	int f�ӿ�_g�������() const override;
	t����3 f�ӿ�_g����() const override;
	float f�ӿ�_g͸����() const override;
	void f����_����();
	void f����_ˮƽ�ƶ�(float);
	void f����_����();
	void f����_����();
	void f����_͸����(float);
private:
	std::shared_ptr<S����> m���� = nullptr;
	float m����֡ = 0;
	float m͸���� = 0;
	const S����::S�������� *m�������� = nullptr;
	const S����::S�������� *mĿ�귽�� = nullptr;
};
//=============================================================================
// �任����
//=============================================================================
class C��ά�任���� : public I���� {
public:
	using tf���� = std::function<void(C��ά�任���� &)>;
	C��ά�任����() = default;
	C��ά�任����(float a��ת, const t����2 &a����, const tf���� &af����);
	void f�ӿ�_����() override;
	t����3 f�ӿ�_g��ת() const override;
	t����3 f�ӿ�_g����() const override;
public:
	float m��ת = 0;
	t����2 m���� = t����2::cһ;
	tf���� mf���� = nullptr;
};
class C��ά�任���� : public I���� {
public:
	using tf���� = std::function<void(C��ά�任���� &)>;
	C��ά�任����() = default;
	C��ά�任����(const t����3 &a��ת, const t����3 &a����, const tf���� &a����);
	void f�ӿ�_����() override;
	t����3 f�ӿ�_g��ת() const override;
	t����3 f�ӿ�_g����() const override;
public:
	t����3 m��ת = t����3::c��;
	t����3 m���� = t����3::cһ;
	tf���� mf���� = nullptr;
};

}