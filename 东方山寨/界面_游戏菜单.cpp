#include <span>
#include "����_��Ϸ�˵�.h"
#include "�������.h"
#include "����.h"
namespace ����ɽկ {
W��Ϸ�˵�::W��Ϸ�˵�(E������ a������) {
	const auto &va�����ı� = C��Ϸ::fg��Դ().fg�����ı�();
	using t��ťԪ�� = std::tuple<int, std::wstring>;
	const t��ťԪ�� va��ť[] = {
		{e�ص���Ϸ, va�����ı�[L"main.returntogame"]},
		{e�ص����˵�, va�����ı�[L"main.returntotitle"]},
		{e����¼��, va�����ı�[L"main.savereplay"]},
		{e���¿�ʼ��Ϸ, va�����ı�[L"main.gamerestart"]},
		{eѡ��, va�����ı�[L"main.option"]},
	};
	const int va��Ϸ�а�ť[] = {
		e�ص���Ϸ,
		e�ص����˵�,
		e����¼��,
		e���¿�ʼ��Ϸ,
		eѡ��,
	};
	const int va��Ϸ������ť[] = {
		e�ص���Ϸ,
		e�ص����˵�,
		e����¼��,
		e���¿�ʼ��Ϸ,
		eѡ��,
	};
	const std::span<const int> vaĿ�갴ť���[] = {
		std::span(va��Ϸ�а�ť),
		std::span(va��Ϸ������ť),
	};
	const std::wstring va�˵�����[] = {
		va�����ı�[L"menu.gamepause"],
		va�����ı�[L"menu.gameover"],
	};
	�û�����::C�����ƶ����� v����;
	constexpr float c����� = -120;
	v����.f����_s���񲼾�(t����2(c�����, 50), t����2(100, 30));
	v����.f����_s�����ƶ�(0, -1);
	for (const int v��ť��� : vaĿ�갴ť���[a������]) {
		const auto &[v��ʶ, v�ı�] = va��ť[v��ť���];
		std::unique_ptr<�û�����::W��ť> v��ť = std::make_unique<�û�����::W��ť>(v��ʶ, 0);
		v��ť->f����_s�ı�(v�ı�, 16, �û�����::e����);
		v��ť->f����_s����(v����.f�ƶ����ɾ���());
		v��ť->m��־[W����::e��ʾ�߿�] = false;
		v��ť->m��־[W����::e��ʾ����] = false;
		ma��ť.push_back(std::move(v��ť));
	}
	w��Ϸ����.f����_s�ı�(va�˵�����[a������], 24, �û�����::e����);
	w��Ϸ����.f����_s����({t����2(c�����, 100), t����2(100, 20)});
}
void W��Ϸ�˵�::f�¼�_����(�û�����::W���� &a����, const �û�����::S�������� &a����) {
	if (a����.m���� == �û�����::E����::eȷ��) {
		switch (a����.m��ʶ) {
		case E��ʶ::e�ص���Ϸ:
			C����::f�л���Ϸ״̬(E��Ϸ״̬::e��Ϸ��);
			break;
		case E��ʶ::e�ص����˵�:
			C����::f�л���Ϸ״̬(E��Ϸ״̬::e���˵�);
			break;
		case E��ʶ::eѡ��:
			C��������::g��->f�л��¸�����(E����::eѡ��);
			break;
		}
	}
}
void W��Ϸ�˵�::f��Ӧ_��ʼ��() {
	for (auto &vp��ť : ma��ť) {
		f����_��Ӵ���(*vp��ť);
		vp��ť->f����_��ʾ();
	}
	f����_��Ӵ���(w��Ϸ����);
	w��Ϸ����.f����_��ʾ();
	f����_��ʾ();
}
}	//namespace ����ɽկ