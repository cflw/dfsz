#include "�ӻ��ƶ�_λ��.h"
#include "�ӻ�.h"
namespace ����ɽկ {
namespace �ӻ��ƶ� {
//����
Cλ��::S����::S����(const t����2 *p����) {
	const t����2 *v�������� = p����;
	const t����2 *v�������� = p���� + 10;
	for (int i = 0; i != c����; ++i) {
		v����[i] = v��������[i];
		v����[i] = v��������[i];
	}
}
const t����2 *Cλ��::S����::fg����(int p���) const {
	return v���� + f�������(p���);
}
const t����2 *Cλ��::S����::fg����(int p���) const {
	return v���� + f�������(p���);
}
//ȡ����
Cλ��::Cȡ����::Cȡ����(const S���� &a����, int a����) :
	v����{a����},
	v���{f�������(a����)},
	v����{a����.v���� + v���},
	v����{a����.v���� + v���} {
}
const t����2 &Cλ��::Cȡ����::fg����(int p���) const {
	assert(p��� < v����);
	return v����[p���];
}
const t����2 &Cλ��::Cȡ����::fg����(int p���) const {
	assert(p��� < v����);
	return v����[p���];
}
t����2 Cλ��::Cȡ����::fg��ֵ(int p���, float p��ֵ) const {
	assert(p��� < v����);
	return ��ѧ::f��ֵ<t����2>(v����[p���], v����[p���], p��ֵ);
}
//����
Cλ��::C����::C����(const std::initializer_list<t����2> &p) :
	v����(std::make_shared<S����>(p.begin())) {
	assert(p.size() == c���� * 2);
}
Cλ��::C����::C����(const std::shared_ptr<S����> &p) :
	v����(p) {
}
I�ӻ��ƶ� *Cλ��::C����::f�ӿ�_�½�() const {
	return new Cλ��(v����);
}
//����
int Cλ��::f�������(int p) {
	assert(p >= 0 && p <= 4);
	static const int c���[] = {0, 0, 1, 3, 6};
	return c���[p];
}
Cλ��::Cλ��(const std::shared_ptr<S����> &a����) : 
	v����{a����} {
}
void Cλ��::f�ӿ�_����() {
	Cȡ���� vȡ���� = fȡ����();
	for (int i = 0; i < *v�ӻ�����; ++i) {
		C�ӻ� &v�ӻ� = va�ӻ�->at(i);
		const t����2 v�������� = t����2::fc����r(5.f * (0.5f - abs(0.5f - *v���ٽ���)), v�Ի�����->f���㷽��r(v�ӻ�.fg����()));
		const t����2 vλ�� = vȡ����.fg��ֵ(i, *v���ٽ���);
		const t����2 vĿ������ = *v�Ի����� + vλ�� + v��������;
		v�ӻ�.f����_�ƶ�(vĿ������);
	}
}
void Cλ��::f�ӿ�_��λ(int a) {
	a -= 1;
	auto f���� = [
		this,
		vȡ���� = fȡ����()
	](int i) {
		C�ӻ� &v�ӻ� = va�ӻ�->at(i);
		v�ӻ�.f����_����(*v�Ի����� + vȡ����.fg��ֵ(i, *v���ٽ���));
	};
	if (a >= 0) {
		if (a <= *v�ӻ�����) {
			f����(a);
		}
	} else {
		for (int i = 0; i < *v�ӻ�����; ++i) {
			f����(i);
		}
	}
}
Cλ��::Cȡ���� Cλ��::fȡ����() const {
	return Cȡ����{*v����, *v�ӻ�����};
}
//�����ռ����
}
}