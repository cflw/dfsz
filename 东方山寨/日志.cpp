#include "����.h"
#include "��ѧ����.h"
#include "��־.h"
namespace ����ɽկ {
float C��־::S��־::fg͸����() const {
	return std::min<float>(m����, 1 - m��ʧ);
}
C��־::C��־(��ά::C��ά &a��ά):
	m���ı�(a��ά.fc���ı�()) {
	��ά::C�ı����� v�ı�����;
	v�ı�����.f��ʼ��();
	��ά::S�ı���ʽ���� v��ʽ;
	v��ʽ.fs�ֺ�(12);
	v��ʽ.fsˮƽ����(��ά::E�ı�ˮƽ����::e��);
	v��ʽ.fs��ֱ����(��ά::E�ı���ֱ����::e��);
	m���ı�->m��ʽ = v�ı�����.fc�ı���ʽ(v��ʽ);
}
void C��־::f���(E���� a����, const std::wstring &a�ı�) {
	S��־ v��־;
	v��־.mʱ�� = ʱ��::C����ʱ��::f����();
	v��־.m���� = a����;
	v��־.m�ı� = a�ı�;
	ma��־.push_back(v��־);
	m��ʾλ��y -= c�о�;
}
void C��־::f����() {
	constexpr float c�����ٶ� = 4;
	constexpr float c������ = c֡�� * c�����ٶ�;
	int i = 0;
	const int v���� = ma��־.size();
	const int v��ʧ = v���� - 5;
	for (S��־ &v��־ : ma��־) {
		v��־.m���� += c֡��;
		if (i < v��ʧ) {
			v��־.m��ʧ += c������;
		} else if (v��־.m���� >= 5) {
			v��־.m��ʧ += c֡��;	//������ʧ
		}
		++i;
	}
	//���������־
	while (!ma��־.empty()) {
		const S��־ &v��־ = ma��־.front();
		if (v��־.m��ʧ >= 1) {
			ma��־.pop_front();
		} else {
			break;
		}
	}
	m��ʾλ��y = ��ѧ::f��������<float>(m��ʾλ��y, -c��Ļ��Χy, 0.01f, c֡��);
}
void C��־::f��ʾ() const {
	float v��ʾλ��y = m��ʾλ��y;
	//�Ӻ�סǰ
	for (auto v = ma��־.crbegin(); v != ma��־.crend(); ++v) {
		const S��־ &v��־ = *v;
		const float v͸���� = v��־.fg͸����();
		m���ı�->fs��ɫ({1, 1, 1, v͸����});
		m���ı�->fs����(-c��Ļ��Χx, v��ʾλ��y);
		m���ı�->f�����ı�(v��־.m�ı�);
		v��ʾλ��y += c�о�;
	}
}
}