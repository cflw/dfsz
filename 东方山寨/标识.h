#pragma once
namespace ����ɽկ {
namespace ���� {
constexpr int f��ʶ(int a, int a��, int aС) {
	return a + a�� + (aС << 16);
}
int fc�����ʶ();	//Ϊ�˱���ײ��,ʵ���ϲ������
}	//namespace ����
//����
constexpr int c��ʶ���� = 2147483647;	//0x7fffffff
//����
constexpr int c�ӵ���ʶ = 1329182951;//0x4f39b8e7
constexpr int c�ӵ���չ��ʶ = 1208143544;//0x4802ceb8
constexpr int c���ӵ���ʶ = 1321863430;	//0x4eca0906
constexpr int c�ӵ������ʶ = 487792821;	//0x1d1320b5
constexpr int c�Ի���ʶ = 670299935;	//0x27f3f71f
constexpr int c���ö�����ʶ = 0;
constexpr int c������ʶ = 358166379;	//0x15592f6b
constexpr int c�ӻ���ʶ = 744384505;	//0x2c5e67f9
constexpr int c�ӻ��ƶ���ʶ = 916599177;	//0x36A23189
constexpr int c����ӵ���ʶ = 1642107557;	//0x61e092a5
constexpr int c���ը����ʶ = 1792698507;	//0x6ada688b
constexpr int c��ҷ����ʶ = 1096709819;	//0x415e76bb
constexpr int c���ͼ�� = 1950318609;	//0x743f8011
constexpr int c�л���ʶ = 660212840;	//0x275a0c68
constexpr int c�ɻ������ʶ = 1937597986;	//0x737d6622
constexpr int c���߱�ʶ = 190639115;	//0x0b5cec0b
constexpr int cЧ����ʶ = 573865576;	//0x22347e68
constexpr int cģ�ͱ�ʶ = 502188807;	//0x1deecb07
constexpr int c�����ʶ = 1776032171;	//0x69dc19ab
enum class E�ӵ� {
	e��ⵯ = c�ӵ���ʶ,
	e��Բ��,
	e����,
	e�׵�,
	e�۵�,
	e���߼���
};
enum class E���ӵ� {
	e���� = c���ӵ���ʶ,
	e����,
};
enum class E���� {
	e�� = 0,
	e���� = 1,
	e�ӵ�0 = c�ӵ������ʶ,	//bullet16x16_00.bmp
};
enum class E�ӵ���չ {
	e�����ӵ� = c�ӵ���չ��ʶ,
	e��ͨ�ӵ�,
	eֱ�߼���,
	e���߼���,
	e���ӵ�,
	e�����ӵ�,
	e���߼���,
};
enum class E�Ի� {
	e���� = c�Ի���ʶ,
	e����,
	eħ��ɳ,
};
enum class E���� {
	e�Ի� = c�ɻ������ʶ,
	e�ӻ�,
	e�л�0
};
enum class E���� {
	e��̬ = c���ö�����ʶ,
	e����0,
	e����,
	e�Ի� = c������ʶ,
	e�л�,
};
enum class E�ӻ� {
	e���� = c�ӻ���ʶ - 1,
	e���μ���,
	e�����յ�,
	eħ��ɳ�ᴩ,
	eħ��ɳ��Χ,
};
enum class E�ӻ��ƶ� {
	eλ�� = c�ӻ��ƶ���ʶ,
};
enum class E����ӵ� {
	e�����ӵ� = c����ӵ���ʶ,
	e���λ���,
	eħ��ɳ����,
	e�����յ�,
	e���μ���,
	eħ��ɳ�ᴩ,
	eħ��ɳ��Χ,
};
enum class E���ը�� {
	e��ͨ = c���ը����ʶ,
	eȫ���嵯,
};
enum class E��ҷ��� {
	//�ӵ�
	e�����ӵ� = c��ҷ����ʶ - 1,
	e�Ի�����,
	e���μ���,
	e�����յ�,
	eħ��ɳ�ᴩ,
	eħ��ɳ��Χ,
	//ը��
	eȫ���嵯,
	e����ը��,
};
enum class E�л� {
	e���� = c�л���ʶ,
	e�л�00��
};
enum class E���� {
	e�л� = c���߱�ʶ,
	e�л���Ƭ,
	eը��,
	eը����Ƭ,
	e����,
	e�õ�,
	e����,
	e΢����,
};
enum class Eͼ�� {
	eЧ��0 = cЧ����ʶ,
	e����0 = c���߱�ʶ,
	e����1
};
enum class Eģ�� {
	e����ƽ�� = 1
};
}	//namespace ����ɽկ