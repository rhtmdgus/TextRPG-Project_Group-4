#include "ending.h"
#include <stdio.h>


void japEnding() {
    system("cls");
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
    printf("당신이 왜군 장군 도요토미를 죽인 덕분에 조선은 쉽게 전쟁을 이겨냈지만");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("그 사실은 후대에 전해지지 않고 당신은 매국노로 역사에 기록이 되었습니다...");
    Sleep(200);
    setCursorPosition(10, 20);
    printf("임진투쟁기를 플레이해 주셔서 감사합니다!!");
    Sleep(100);
    setCursorPosition(10, 22);
    printf("엔딩 번호 1: 이기적인 복수");

    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}


void solEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 관군 동료들과 함께 복수를 성공하였습니다!");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("당신은 복수를 끝낸 후에도 조선을 위해 왜군들과 싸워나갔습니다!!");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("전쟁이 끝난 후 당신은 그 공을 인정받고 높은 관직을 부여받았습니다.");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("당신은 은퇴하기 전까지 후배들을 육성하며 살아갔습니다");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("후대에 당신은 존경받는 위인으로 역사에 기록이 되었습니다.");
    Sleep(200);
    setCursorPosition(10, 20);
    printf("임진투쟁기를 플레이 해 주셔서 감사합니다!!");

    Sleep(100);
    setCursorPosition(10, 22);
    printf("엔딩 번호 2: 조선의 영웅들");

    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}


void volEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 의병 동료들과 함께 복수를 성공하였습니다!");
    Sleep(200);
    setCursorPosition(10, 12);
    printf("당신은 복수를 끝낸 후에도 조선을 위해 왜군들과 싸워나갔습니다!!");
    Sleep(200);
    setCursorPosition(10, 14);
    printf("전쟁은 조선의 승리로 돌아갔고, 당신은 전쟁이 끝난 후 고향으로 돌아가");
    Sleep(200);
    setCursorPosition(10, 16);
    printf("망가졌던 마을을 재건하고, 근처 산에 가족들의 무덤을 만들고");
    Sleep(200);
    setCursorPosition(10, 18);
    printf("무덤 옆에 판자집을 만들어 평생을 가족들을 지키며 살아갔습니다");
    Sleep(200);
    setCursorPosition(10, 20);
    printf("임진투쟁기를 플레이 해 주셔서 감사합니다!!");

    Sleep(100);
    setCursorPosition(10, 22);
    printf("엔딩 번호 3: 조선의 숨은 영웅들");

    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}


void deadEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 전투중 사망하였습니다!");
    Sleep(100);
    setCursorPosition(10, 12);
    printf("더 많은 적들을 잡고, 퀘스트, 렌덤 이벤트를 진행하시면");
    Sleep(100);
    setCursorPosition(10, 14);
    printf("좀더 원활한 플레이가 가능하실 것 같습니다!");
    Sleep(100);
    setCursorPosition(10, 16);
    printf("엔딩 번호 4: 이루지 못하게 된 복수");

    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}

void potionEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 히든 엔딩에 도달하였습니다!");
    Sleep(100);
    setCursorPosition(10, 12);
    printf("물약을 너무 많이 먹어 중독당해 사망하였습니다");
    Sleep(100);
    setCursorPosition(10, 14);
    printf("물약 10개 이상을 한번에 마시면 중독당해 죽어버리니 주의해주세요");
    Sleep(100);
    setCursorPosition(10, 16);
    printf("엔딩 번호 5: 물약중독");


    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}

void exeEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 히든 엔딩에 도달하였습니다!");
    Sleep(100);
    setCursorPosition(10, 12);
    printf("당신은 조선을 배신하고 왜구편에서 복수를 행하려고 했습니다");
    Sleep(100);
    setCursorPosition(10, 14);
    printf("당신은 관군에게 사로잡혀 처형당하였습니다");
    Sleep(100);
    setCursorPosition(10, 16);
    printf("엔딩 번호 6: 배신자의 말로");


    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}

void runEnding() {
    system("cls");
    Sleep(100);
    setCursorPosition(10, 10);
    printf("당신은 히든 엔딩에 도달하였습니다!");
    Sleep(100);
    setCursorPosition(10, 12);
    printf("당신은 기절에서 깨어나자마자 두려움에 사로잡혀");
    Sleep(100);
    setCursorPosition(10, 14);
    printf("가족들을 찾을 생각조차 못하고 도망쳤습니다");
    Sleep(100);
    setCursorPosition(10, 16);
    printf("당신은 목숨은 부지하였지만 평생을 죄책감에 갇혀 살아갔습니다.");
    Sleep(100);
    setCursorPosition(10, 18);
    printf("엔딩 번호 7: 나라도 살아야지...");


    getchar();  // 사용자로부터 Enter 입력 대기

    exit(0);
}

//1. 관군 루트 진엔딩
//2. 의병 루트 엔딩
//3. 왜군 루트의 엔딩
//4. 사망시 배드엔딩
//5. 물약 과도하게 사용하면 과도복용하면 죽음
//6. 왜군 루트를 탈 경우 지정된 장소에가면 처단되어서 죽음
//7. 프롤로그에서 도망치는 엔딩