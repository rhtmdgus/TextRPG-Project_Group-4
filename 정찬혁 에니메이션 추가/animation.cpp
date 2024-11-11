#include "animation.h"
#include <stdio.h>

// 플레이어 모습 구현
char swordAttack[][12][12] = {
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,'/',0},
      {0,0,0, 0, 'p', 0,0,0,0,'/',0,0},
      {0,0,0, '/', '|', '\\',0,0,'/',0,0,0},
      {0,0,0, '\\', '|', 0,'\\','x',0,0,0,0},
      {0,0,0, 0, '|', 0,'/',0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,'|',0,0,0},
      {0,0,0, 0, 0, 0,0,0,'|',0,0,0},
      {0,0,0, 0, 'p', '_','_','_','+',0,0,0},
      {0,0,0, '/', '|', 0,0,0,'|',0,0,0},
      {0,0,0, '\\', '|', 0,0,0,0,0,0,0},
      {0,0,0, 0, '|', 0,0,0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {'\\',0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,'\\',0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,'x', 0, 0, 0,0,0,0,0,0,0},
      {0,'p',0, '\\', 0, 0,0,0,0,0,0,0},
      {0,0,'\\', '/', 0, 0,0,0,0,0,0,0},
      {0,0,'/', '\\', 0, 0,0,0,0,0,0,0},
      {0,0,'|', 0, '\\', 0,0,0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,'|',0,0,0},
      {0,0,0, 0, 0, 0,0,0,'|',0,0,0},
      {0,0,0, 0, 'p', '_','_','_','+',0,0,0},
      {0,0,0, '/', '|', 0,0,0,'|',0,0,0},
      {0,0,0, '\\', '|', 0,0,0,0,0,0,0},
      {0,0,0, 0, '|', 0,0,0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,'/',0},
      {0,0,0, 0, 'p', 0,0,0,0,'/',0,0},
      {0,0,0, '/', '|', '\\',0,0,'/',0,0,0},
      {0,0,0, '\\', '|', 0,'\\','x',0,0,0,0},
      {0,0,0, 0, '|', 0,'/',0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      }
};

char swordDamaged[][12][12] = {

   {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 'p', 0,0,0,0,'/',0,0},
      {0,0,0, '/', '|', '\\',0,0,'/',0,0,0},
      {'(','(',0, '\\', '|', 0,'\\','x',0,')',')',0},
      {0,0,0, '(', '|', 0,'/',0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 'p', 0, 0,0,0,'/',0,0,0},
      {0,0,'/', '|', '\\', 0,0,'/',0,0,0,0},
      {'(','(','\\', '|', 0, '\\','x',0,')',')',0,0},
      {0,0,0, '|', 0, '/',0,0,0,0,0,0},
      {0,0,'/', 0, '\\', 0,0,0,0,0,0,0},
      {0,'/',0, 0, 0, '\\',0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 'p',0,0,0,0,'/',0},
      {0,0,0, 0, '/', '|','\\',0,0,'/',0,0},
      {0,'(','(', 0, '\\', '|',0,'\\','x',0,')',')'},
      {0,0,0, 0, 0, '|',0,'/',0,0,0,0},
      {0,0,0,0, '/', 0,'\\',0,0,0,0,0},
      {0,0,0, '/', 0, 0,0,'\\',0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 'p', 0, 0,0,0,'/',0,0,0},
      {0,0,'/', '|', '\\', 0,0,'/',0,0,0,0},
      {'(','(','\\', '|', 0, '\\','x',0,')',')',0,0},
      {0,0,0, '|', 0, '/',0,0,0,0,0,0},
      {0,0,'/', 0, '\\', 0,0,0,0,0,0,0},
      {0,'/',0, 0, 0, '\\',0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
      {
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 'p', 0,0,0,0,'/',0,0},
      {0,0,0, '/', '|', '\\',0,0,'/',0,0,0},
      {'(','(',0, '\\', '|', 0,'\\','x',0,')',')',0},
      {0,0,0, '(', '|', 0,'/',0,0,0,0,0},
      {0,0,0, '/', 0, '\\',0,0,0,0,0,0},
      {0,0,'/', 0, 0, 0,'\\',0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0},
      {0,0,0, 0, 0, 0,0,0,0,0,0,0}
      },
};

char arrowAttack[][12][12] = {
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, '/', '|','\\','|',0,'|',0,0,0},
      {0,0, 0, '\\', '|',0,'\\',0,'|',0,0,0},
      {0, 0, 0, 0, '|', 0, '|', 0, '|', 0, 0, 0},
      {0,0, 0, '/', 0,'\\','|','/',0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, 0, '|','-','+','-','+','-','>',0},
      {0,0, 0, 0, '|',0,'|',0,'|',0,0,0},
      {0, 0, 0, 0, '|', 0, '|', '/', 0, 0, 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'/','\\',0,0,0,0},
      {0,0, 0, 0, 'p','/',0,0,'|',0,0,0},
      {0,0, 0, '<', '|','-','+','-','+','>',0,0},
      {0,0, 0, 0, '|','\\',0,0,'|',0,0,0},
      {0, 0, 0, 0, '|', 0, '\\', '/', 0, 0, 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, '/', '|','-','+',0,'+','-','-','>'},
      {0,0, 0, '|', '|',0,'|',0,'|',0,0,0},
      {0, 0, 0, 0, '|', 0, '|', '/', 0, 0, 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, '/', '|','-','+',0,'|',0,0,0},
      {0,0, '/', 0, '|',0,'|',0,'|',0,0,0},
      {0, 0, 0, 0, '|', 0, '|', '/', 0, 0, 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      }
};
char arrowDamaged[][12][12] = {

   {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, '/', '|','\\','|',0,'|',0,0,0},
      {0,'(', '(', '\\', '|',0,'\\',0,'|',')',')',0},
      {0, 0, 0, 0, '|', 0, '|', 0, '|', 0, 0, 0},
      {0,0, 0, '/', 0,'\\','|','/',0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,'|','\\',0,0,0,0,0},
      {0,0, 0, 'p', 0,'|',0,'|',0,0,0,0},
      {0,0, '/', '|', '\\','|',0,'|',0,0,0,0},
      {'(','(', '\\', '|', 0,'\\',0,'|',')',')',0,0},
      {0, 0, 0, '|', 0, '|', 0, '|', 0, 0, 0, 0},
      {0,0, '/', 0, '\\','|','/',0,0,0,0,0},
      {0,'/', 0, 0, 0,'\\',0,0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,0,'|','\\',0,0,0},
      {0,0, 0, 0, 0,'p',0,'|',0,'|',0,0},
      {0,0, 0, 0, '/','|','\\','|',0,'|',0,0},
      {0,0, '(', '(', '\\','|',0,'\\',0,'|',')',')'},
      {0, 0, 0, 0, 0, '|', 0, '|', 0, '|', 0, 0},
      {0,0, 0, 0, '/',0,'\\','|','/',0,0,0},
      {0,0, 0, '/', 0,0,0,'\\',0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,'|','\\',0,0,0,0,0},
      {0,0, 0, 'p', 0,'|',0,'|',0,0,0,0},
      {0,0, '/', '|', '\\','|',0,'|',0,0,0,0},
      {'(','(', '\\', '|', 0,'\\',0,'|',')',')',0,0},
      {0, 0, 0, '|', 0, '|', 0, '|', 0, 0, 0, 0},
      {0,0, '/', 0, '\\','|','/',0,0,0,0,0},
      {0,'/', 0, 0, 0,'\\',0,0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0,0,0,'|','\\',0,0,0,0},
      {0,0, 0, 0, 'p',0,'|',0,'|',0,0,0},
      {0,0, 0, '/', '|','\\','|',0,'|',0,0,0},
      {0, 0 , 0 , '\\', '|',0,'\\',0,'|',0 ,0 ,0},
      {0, 0, 0, 0, '|', 0, '|', 0, '|', 0, 0, 0},
      {0,0, 0, '/', 0,'\\','|','/',0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
};

char shieldAttack[][12][12] = {
   {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0,0, 0,0,'_','_','_',0,0,0},
      {0,0, 0, 0, 'p',0,'|','|','|',0,0,0},
      {0,0, 0, '/', '|','\\','|','+','|',0,0,0},
      {0, 0,0, '\\', '|',0,'|','|','|',0,0,0},
      {0,0, 0, 0, '|',0,'|','|','|',0,0,0},
      {0,0, 0, '/', 0,'\\','|','|','|',0,0,0},
      {0,0, '/', 0, 0,0,'\\','-','-',0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, '/', '\\', 0, 0, 0, 0},
      {0, 0, 0,0, 0,'/','\\',0,'\\',0,0,0},
      {0,0, 0, 0, 'p','\\',0,'x',0,'\\',0,0},
      {0,0, 0, '/', '|','/','\\',0,'\\',0,'\\',0},
      {0, 0,0, '\\', '|',0,0,'\\',0,'\\','/',0},
      {0, 0, 0, 0, '|', 0, 0, 0, '\\', '/', 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, '_', '_', '_', '_', '_', '_', '_', '_', '_', 0},
      {0, 0, '|', 0, 0, 0,0,0,0,0, '|', 0},
      {0, 0, '|','-', '-', '+', '-', '-', '-', '-', '|', 0},
      {0, 0, '-','-', '-','-','-','-','-','-','-',0},
      {0,0, 0, 0, 'p',0,'|',0,0,0,0,0},
      {0,0, 0, '/', '|','/',0,0,0,0,0,0},
      {0, 0,0, '\\', '|',0,0,0,0,0,0,0},
      {0, 0, 0, 0, '|', 0, 0, 0, 0, 0, 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, '/', '\\', 0, 0, 0, 0},
      {0, 0, 0,0, 0,'/','\\',0,'\\',0,0,0},
      {0,0, 0, 0, 'p','\\',0,'x',0,'\\',0,0},
      {0,0, 0, '/', '|','/','\\',0,'\\',0,'\\',0},
      {0, 0,0, '\\', '|',0,0,'\\',0,'\\','/',0},
      {0, 0, 0, 0, '|', 0, 0, 0, '\\', '/', 0, 0},
      {0,0, 0, '/', 0,'\\',0,0,0,0,0,0},
      {0,0, '/', 0, 0,0,'\\',0,0,0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0,0, 0,0,'_','_','_',0,0,0},
      {0,0, 0, 0, 'p',0,'|','|','|',0,0,0},
      {0,0, 0, '/', '|','\\','|','+','|',0,0,0},
      {0, 0,0, '\\', '|',0,'|','|','|',0,0,0},
      {0,0, 0, 0, '|',0,'|','|','|',0,0,0},
      {0,0, 0, '/', 0,'\\','|','|','|',0,0,0},
      {0,0, '/', 0, 0,0,'\\','-','-',0,0,0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
};

char enemySwordAttack[][12][12] =
{
   {
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,'\\',0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,'\\',0,0,0,0,'E',0,0,0,0},
   {0,0,0,'\\',0,0,'/','|','\\',0,0,0},
   {0,0,0,0,'x','/',0,'|','/',0,0,0},
   {0,0,0,0,0,'\\',0,'|',0,0,0,0},
   {0,0,0,0,0,0,'/',0,'\\',0,0,0},
   {0,0,0,0,0,'/',0,0,0,'\\',0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, '|', 0, 0,0,0,0,0,0,0},
   {0,0,0, '|', 0, 0,0,0,0,0,0,0},
   {0,0,0, '+','_','_','_','E',0,0,0,0},
   {0,0,0, '|', 0, 0,0,'|','\\',0,0,0},
   {0,0,0, 0, 0, 0,0,'|','/',0,0,0},
   {0,0,0, 0, 0, 0,0,'|',0,0,0,0},
   {0,0,0, 0, 0, 0,'/', 0, '\\',0,0,0},
   {0,0,0, 0, 0, '/',0,0,0,'\\',0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,'/'},
   {0,0,0, 0, 0, 0,0,0,0,0,'/',0},
   {0,0,0, 0, 0, 0,0,0,0,'x',0,0},
   {0,0,0, 0, 0, 0,0,0,'/',0,'E',0},
   {0,0,0, 0, 0, 0,0,0,'\\','/',0,0},
   {0,0,0, 0, 0, 0,0,0,'/','\\',0,0},
   {0,0,0, 0, 0, 0,0,'/',0,0,'\\',0},
   {0,0,0, 0, 0, 0,'/',0,'\\',0,0,0},
   {0,0,0, 0, 0, '/',0,0,0,'\\',0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, '|', 0, 0,0,0,0,0,0,0},
   {0,0,0, '|', 0, 0,0,0,0,0,0,0},
   {0,0,0, '+','_','_','_','E',0,0,0,0},
   {0,0,0, '|', 0, 0,0,'|','\\',0,0,0},
   {0,0,0, 0, 0, 0,0,'|','/',0,0,0},
   {0,0,0, 0, 0, 0,0,'|',0,0,0,0},
   {0,0,0, 0, 0, 0,'/', 0, '\\',0,0,0},
   {0,0,0, 0, 0, '/',0,0,0,'\\',0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,'\\',0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,'\\',0,0,0,0,'E',0,0,0,0},
   {0,0,0,'\\',0,0,'/','|','\\',0,0,0},
   {0,0,0,0,'x','/',0,'|','/',0,0,0},
   {0,0,0,0,0,'\\',0,'|',0,0,0,0},
   {0,0,0,0,0,0,'/',0,'\\',0,0,0},
   {0,0,0,0,0,'/',0,0,0,'\\',0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0},
   {0,0,0, 0, 0, 0,0,0,0,0,0,0}
   }
};

char enemySwordDamaged[][12][12] =
{
   {
    {0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,'\\',0, 0, 0, 0,0,0,0,0,0,0},
{0,0,'\\',0,0,0,0,'E',0,0,0,0},
{0,0,0,'\\',0,0,'/','|','\\',0,0,0},
{0,0,0,0,'x','/',0,'|','/',0,0,0},
{0,0,0,0,0,'\\',0,'|',0,0,0,0},
{0,0,0,0,0,0,'/',0,'\\',0,0,0},
{0,0,0,0,0,'/',0,0,0,'\\',0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
    {0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,'\\',0, 0, 0, 0,0,0,0,0,0},
{0,0,0,'\\',0,0,0,0,'E',0,0,0},
{0,0,0,0,'\\',0,0,'/','|','\\',0,0},
{0,0,0,'(','(','x','/',0,'|','/',')',')'},
{0,0,0,0,0,0,'\\',0,'|',0,0,0},
{0,0,0,0,0,0,0,'/',0,'\\',0,0},
{0,0,0,0,0,0,'/',0,0,0,'\\',0},
{0,0,0, 0, 0, 0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0}
   },
   {
    {0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{'\\',0, 0, 0, 0,0,0,0,0,0,0,0},
{0,'\\',0,0,0,0,'E',0,0,0,0,0},
{0,0,'\\',0,0,'/','|','\\',0,0,0,0},
{0,'(','(','x','/',0,'|','/',')',')',0,0},
{0,0,0,0,'\\',0,'|',0,0,0,0,0},
{0,0,0,0,0,'/',0,'\\',0,0,0,0},
{0,0,0,0,'/',0,0,0,'\\',0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0}
   },
   {
 {0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,'\\',0, 0, 0, 0,0,0,0,0,0},
{0,0,0,'\\',0,0,0,0,'E',0,0,0},
{0,0,0,0,'\\',0,0,'/','|','\\',0,0},
{0,0,0,'(','(','x','/',0,'|','/',')',')'},
{0,0,0,0,0,0,'\\',0,'|',0,0,0},
{0,0,0,0,0,0,0,'/',0,'\\',0,0},
{0,0,0,0,0,0,'/',0,0,0,'\\',0},
{0,0,0, 0, 0, 0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0}
   },
   {
 {0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,'\\',0, 0, 0, 0,0,0,0,0,0,0},
{0,0,'\\',0,0,0,0,'E',0,0,0,0},
{0,0,0,'\\',0,0,'/','|','\\',0,0,0},
{0,0,0,0,'x','/',0,'|','/',0,0,0},
{0,0,0,0,0,'\\',0,'|',0,0,0,0},
{0,0,0,0,0,0,'/',0,'\\',0,0,0},
{0,0,0,0,0,'/',0,0,0,'\\',0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0},
{0,0,0, 0, 0, 0,0,0,0,0,0,0}
   }
};


void printPlayer() {

    int playerWidth = 12;
    int playerHeight = 12;

    // 전투 맵의 중앙 계산
    int centerX = 15;
    int centerY = (MAP_HEIGHT - playerHeight) / 2;

    if (player.job == 1) 
    {
        setCursorPosition(centerX, centerY);
        for (int i = 0; i < 12; i++)
        {
            setCursorPosition(centerX, centerY + i);
            for (int j = 0; j < 12; j++)
            {
                if (swordAttack[0][i][j] == 0)
                {
                    printf(" ");
                }
                printf("%c", swordAttack[0][i][j]);
            }
            printf("\n");
        }
    }
    else if (player.job == 2)
    {
        setCursorPosition(centerX, centerY);
        for (int i = 0; i < 12; i++)
        {
            setCursorPosition(centerX, centerY + i);
            for (int j = 0; j < 12; j++)
            {
                if (arrowAttack[0][i][j] == 0)
                {
                    printf(" ");
                }
                printf("%c", arrowAttack[0][i][j]);
            }
            printf("\n");
        }
    }
}

void playerAttackAnimation()
{

    int playerWidth = 12;
    int playerHeight = 12;

    // 전투 맵의 중앙 계산
    int centerX = 15;
    int centerY = (MAP_HEIGHT - playerHeight) / 2;

    if (player.job == 1) // player.h의 player 구조체에 job 변수 추가 -> job == 1은 전사 job == 2는 궁수...
    {
        setCursorPosition(centerX, centerY); // 캐릭터 애니메이션을 전투 화면의 중앙에 출력
        // 애니메이션 출력
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 12; i++)
            {
                setCursorPosition(centerX, centerY + i);
                for (int j = 0; j < 12; j++)
                {
                    if (swordAttack[k][i][j] == 0)
                    {
                        printf(" ");
                    }
                    printf("%c", swordAttack[k][i][j]);
                }
                printf("\n");
            }
            Sleep(50);
        }
        
    }
    else if (player.job == 2) 
    {
        setCursorPosition(centerX, centerY); // 캐릭터 애니메이션을 전투 화면의 중앙에 출력
        // 애니메이션 출력
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 12; i++)
            {
                setCursorPosition(centerX, centerY + i);
                for (int j = 0; j < 12; j++)
                {
                    if (arrowAttack[k][i][j] == 0)
                    {
                        printf(" ");
                    }
                    printf("%c", arrowAttack[k][i][j]);
                }
                printf("\n");
            }
            Sleep(50);
        }
    

        // 화면을 지우지 않고 계속 애니메이션 진행
         // 잠시 대기 (애니메이션 효과를 위해)
    }

}


void playerAttackedAnimation()
{

    int playerWidth = 12;
    int playerHeight = 12;

    // 전투 맵의 중앙 계산
    int centerX = 15;
    int centerY = (MAP_HEIGHT - playerHeight) / 2;

    if (player.job == 1) // player.h의 player 구조체에 job 변수 추가 -> job == 1은 전사 job == 2는 궁수...
    {
        setCursorPosition(centerX, centerY); // 캐릭터 애니메이션을 전투 화면의 중앙에 출력
        // 애니메이션 출력
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 12; i++)
            {
                setCursorPosition(centerX, centerY + i);
                for (int j = 0; j < 12; j++)
                {
                    if (swordDamaged[k][i][j] == 0)
                    {
                        printf(" ");
                    }
                    printf("%c", swordDamaged[k][i][j]);
                }
                printf("\n");
            }
            Sleep(50);
        }
        
    }
    else if (player.job == 2)
    {
        setCursorPosition(centerX, centerY); // 캐릭터 애니메이션을 전투 화면의 중앙에 출력
        // 애니메이션 출력
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 12; i++)
            {
                setCursorPosition(centerX, centerY + i);
                for (int j = 0; j < 12; j++)
                {
                    if (arrowDamaged[k][i][j] == 0)
                    {
                        printf(" ");
                    }
                    printf("%c", arrowDamaged[k][i][j]);
                }
                printf("\n");
            }
            Sleep(50);
        }


        // 화면을 지우지 않고 계속 애니메이션 진행
         // 잠시 대기 (애니메이션 효과를 위해)
    }

}

void printEnemy()
{
    for (int i = 0; i < 12; i++)
    {
        setCursorPosition(60, 10 + i);
        for (int j = 0; j < 12; j++)
        {
            if (enemySwordDamaged[0][i][j] == 0)
            {
                printf(" ");
            }
            printf("%c", enemySwordDamaged[0][i][j]);
        }
        printf("\n");
    }
    Sleep(50);
}




void enemyAttackedAnimation() 
{
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < 12; i++)
        {
            setCursorPosition(60, 10 + i);
            for (int j = 0; j < 12; j++)
            {
                if (enemySwordDamaged[k][i][j] == 0)
                {
                    printf(" ");
                }
                printf("%c", enemySwordDamaged[k][i][j]);
            }
            printf("\n");
        }
        Sleep(50);
    }
    
}




void enemyAttackAnimation() {
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < 12; i++)
        {
            setCursorPosition(60, 10 + i);
            for (int j = 0; j < 12; j++)
            {
                if (enemySwordAttack[k][i][j] == 0)
                {
                    printf(" ");
                }
                printf("%c", enemySwordAttack[k][i][j]);
            }
            printf("\n");
        }
        Sleep(50);
    }
    
}

