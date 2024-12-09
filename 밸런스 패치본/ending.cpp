#include "ending.h"
#include <stdio.h>


void badEnding() {
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 민생과 국가를 배신하면서까지 복수를 하길 원하였습니다.");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("당신은 마침내 복수를 성공하였지만...");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("입은 상처가 너무 깊어 주변의 왜군 잡졸들에게 유린당하였습니다...");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("끝이 좋지 않았지만 임진투쟁기의 끝마침을 축하드립니다!!");

}

void GoodEnding() {
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 동료들과 함께 복수를 성공하였습니다!");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("당신은 복수를 끝낸 후에도...");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("조선을 위해 왜군들과 싸워나갔습니다!!");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("임진왜란이 끝난 후 당신은 그 공을 인정받고 고향으로 돌아가...");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("가족의 시신을 수습하고 무덤 주변을 지키며 살아갔습니다");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("임진투쟁기의 끝마침을 축하드립니다!!");
}