#pragma once
#include <math.h>
namespace ����ɽկ {
//����
constexpr wchar_t c�����ļ�[] = L"~/boot/dfylc0.json";
constexpr wchar_t c���ڱ���[] = L"����������";
//ʱ��
constexpr double c����Ƶ�� = 240;
constexpr double c֡�� = 1.0 / c����Ƶ��;
//����&����
constexpr wchar_t c��������[] = L"Consolas";
constexpr wchar_t c�ı�����[] = L"΢���ź�";
//����
constexpr unsigned int c�ӵ����� = 2000;
constexpr unsigned int c����ӵ����� = 1000;
constexpr unsigned int c�������� = 2000;
constexpr unsigned int c�л����� = 100;
constexpr unsigned int cͼ������ = 5000;
//��Χ
constexpr long c��׼�ߴ�x = 640;
constexpr long c��׼�ߴ�y = 480;
constexpr float c�߿�Χx = 192;
constexpr float c�߿�Χy = 224;
const float c�߿�Χr = hypot(c�߿�Χx, c�߿�Χy);
constexpr float c�߿��� = 4;
constexpr float c��߿�Χx = c�߿�Χx + c�߿���;
constexpr float c��߿�Χy = c�߿�Χy + c�߿���;
const float c��߿�Χr = hypot(c��߿�Χx, c��߿�Χy);
constexpr float c��Ļ��Χx = 320;
constexpr float c��Ļ��Χy = 240;
constexpr float c��Ļ��Χr = 400;
constexpr float c�Ի��ƶ����Ʒ�Χ = 16;
constexpr float c�ƶ���Χx = c�߿�Χx - c�Ի��ƶ����Ʒ�Χ;
constexpr float c�ƶ���Χy = c�߿�Χy - c�Ի��ƶ����Ʒ�Χ;
const float c�ƶ���Χr = hypot(c�ƶ���Χx, c�ƶ���Χy);
constexpr float c�Ի���ʼ����y = -c�߿�Χy + 64;
//����
enum E���� {
	e�� = 0x01,
	e�� = 0x02,
	e�� = 0x04,
	e�� = 0x08,
	e���� = e�� | e��,
	e���� = e�� | e��,
	e�������� = e�� | e�� | e�� | e��,
};
//ϸ��
constexpr float c��ս����ʱ0 = 10;
constexpr float c��ս����ʱ1 = 5;
//���Գ���
#ifdef _DEBUG
constexpr bool c����_�ܿ��� = true;
#else
constexpr bool c����_�ܿ��� = false;
#endif
constexpr bool c����_�Ի��޵� = c����_�ܿ��� && true;
constexpr bool c����_������Ϣ = c����_�ܿ��� && true;

}