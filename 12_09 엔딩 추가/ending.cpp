#include "ending.h"
#include <stdio.h>


void badEnding() {
    Sleep(100);
    setCursorPosition(10, 10);
    printf("����� �λ��� ������ ����ϸ鼭���� ������ �ϱ� ���Ͽ����ϴ�.");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("����� ��ħ�� ������ �����Ͽ�����...");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("���� ��ó�� �ʹ� ��� �ֺ��� �ֱ� �����鿡�� �������Ͽ����ϴ�...");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("���� ���� �ʾ����� ����������� ����ħ�� ���ϵ帳�ϴ�!!");

}

void GoodEnding() {
    Sleep(100);
    setCursorPosition(10, 10);
    printf("����� ������ �Բ� ������ �����Ͽ����ϴ�!");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("����� ������ ���� �Ŀ���...");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("������ ���� �ֱ���� �ο��������ϴ�!!");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("�����ֶ��� ���� �� ����� �� ���� �����ް� �������� ���ư�...");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("������ �ý��� �����ϰ� ���� �ֺ��� ��Ű�� ��ư����ϴ�");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("����������� ����ħ�� ���ϵ帳�ϴ�!!");
}