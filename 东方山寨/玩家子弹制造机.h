#pragma once
#include <optional>
#include "����.h"
#include "����_����.h"
#include "����ӵ�����.h"
namespace ����ɽկ {
typedef std::optional<float> t����;
class C���;
struct S����ӵ�����;
class I��ҷ��价��;
class C����ӵ�;
class C���ը��;
struct S����ӵ����� {
	t����2 m����, m�ٶ�;
	const I��ҷ��价�� *m���价�� = nullptr;
	const S����ӵ����� *m�ӵ����� = nullptr;
};
class C����ӵ������ {
public:
	static const int c���� = 5;
	class Cѭ�� : public ѭ��::Iѭ��<Cѭ��> {
	public:
		Cѭ��(int ����, S����ӵ����� *);
		//ѭ������
		void fѭ������_����();
		bool fѭ������_i����();
		//ѭ����������
		int fg����() const;
		int fg����() const;
		float fg�ٷֱ�() const;
		//����
		float f����(t��־) const;
		t����2 f����_�ٶȱ任(float ��С, float ����, float ���� = 1) const;
		//�任
		void f�任_����(int = -1);
		void f�任_��ԭ(int = -1);
		void f�任_�ٶ�(float ��С, float ����, float ���� = 1);
		void f�任_����ƽ��(const t����2 &�ƶ�, float ����);
		void f�任ģ��_��ɢ(std::shared_ptr<I��ҷ��价��>, const std::pair<float, float> &�Ƕȼ��, const std::pair<float, float> &����x���);
	private:
		int m����, m����;
		S����ӵ����� m��������, *mp����;
	};
	class Cʵ�� {
	public:
		void f��ʼ��_����(const C��Ϸ�ٶ� &);
		void f��ʼ��_����(C��������<C����ӵ�> &);
		void f�����ӵ�(std::shared_ptr<C����ӵ�>, const S����ӵ����� &);
		void f����ը��(std::shared_ptr<C���ը��>, const S����ӵ����� &);
		bool fi�п�() const;
		const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
		C��������<C����ӵ�> *ma�ӵ�;
	};
	C����ӵ������(Cʵ�� &);
	template<typename t, typename...t����> std::shared_ptr<t> f�����ӵ�(const t���� &...);
	template<typename t, typename...t����> std::shared_ptr<t> f����ը��(const t���� &...);
	Cѭ�� fѭ��(int);
	S����ӵ����� m����;
private:
	Cʵ�� * mʵ�� = nullptr;
};
template<typename t, typename...t����> std::shared_ptr<t> C����ӵ������::f�����ӵ�(const t���� &...a����) {
	static_assert(std::is_base_of<C����ӵ�, t>::value);
	if (mʵ��->fi�п�()) {
		std::shared_ptr<t> v���ӵ� = std::make_shared<t>(a����...);
		mʵ��->f�����ӵ�(v���ӵ�, m����);
		return v���ӵ�;
	}
	return nullptr;
}
template<typename t, typename...t����> std::shared_ptr<t> C����ӵ������::f����ը��(const t���� &...a����) {
	static_assert(std::is_base_of<C���ը��, t>::value);
	std::shared_ptr<t> v���ӵ� = std::make_shared<t>(a����...);
	mʵ��->f����ը��(v���ӵ�, m����);
	return v���ӵ�;
}
}