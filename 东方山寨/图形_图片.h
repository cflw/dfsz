#pragma once
#include "����_����.h"
#include "ͼ�λ���.h"
#include "ͼ������.h"
#include "�����ӿ�.h"
namespace ����ɽկ {
struct Sͼ�β���;
struct SͼƬ��������;
//==============================================================================
// ʵ��
//==============================================================================
class C��ͼƬ���� {
public:
	static void f��ʾͼƬ(const t����2 &����, const tp���� &����, const S������� *����, const I���� &����);
	static void f��ʾͼƬ2(const tp���� &����, const S������� &����, const t����2 &ƽ��, float ��ת, const t����2 &����, float ͸��);
	static void f��ʾͼƬ3(const tp���� &����, const S������� &����, const t����2 &ƽ��, const t����3 &��ת, const t����3 &����, float ͸��);
};
//==============================================================================
// ���㶯��,���ϻ�ͼƬ�Ĵ���
//==============================================================================
class C����ͼƬ���� {
public:
	//����
	virtual const SͼƬ�������� &fgͼƬ��������() const = 0;
	virtual const t����2 &fg����() const = 0;
	bool fi����() const;
	const S������� &fg�������() const;
	//����
	virtual void f��ʾ() const;
	void f��ʾͼƬ() const;
public:
	std::unique_ptr<I����> m���� = nullptr;
};
//����
struct SͼƬ�������� {
	t����ָ��<tp����> m����;
	t����ָ��<S�������> m����;
	t��չָ��<I����<I����>> m����;
	std::unique_ptr<I����> fc����(void * = nullptr) const;
};
//==============================================================================
// ͼƬͼ��
//==============================================================================
class C��άͼƬͼ�� : public I����, public I�¼�, public I���� {
public:
	C��άͼƬͼ��() = default;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_��ʼ��(const Sͼ�β��� &) override;
	t����3 f�ӿ�_g��ת() const override;
	t����3 f�ӿ�_g����() const override;
	float f�ӿ�_g͸����() const override;
	bool fi����() const;
	const S������� &fg�������() const;
	void f��ʾͼƬ() const;
protected:
	float m��ת = 0;
	t����2 m���� = t����2::cһ;
	const tp���� *m���� = nullptr;
	const S������� *m���� = nullptr;
};
//��ά
class C��άͼƬͼ�� : public I����, public I�¼�, public I���� {
public:
	C��άͼƬͼ��() = default;
	void f�ӿ�_����() override;
	void f�ӿ�_��ʾ() const override;
	void f�ӿ�_��ʼ��(const Sͼ�β��� &) override;
	t����3 f�ӿ�_g��ת() const override;
	t����3 f�ӿ�_g����() const override;
	float f�ӿ�_g͸����() const override;
	bool fi����() const;
	const S������� &fg�������() const;
	void f��ʾͼƬ() const;
protected:
	t����3 m��ת = t����3::c��;
	t����3 m���� = t����3::cһ;
	const tp���� *m���� = nullptr;
	const S������� *m���� = nullptr;
};

}	//namespace ����ɽկ