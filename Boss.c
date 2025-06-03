// boss.c
#include "boss.h"
#include <ncurses.h>
#include <stdint.h>

#define WIDTH 47
#define HEIGHT 82

// 헤더 파일에서 선언한 변수들의 실제 정의 //
Boss boss;
int boss_active = 0; // 보스 활성화 여부(0: 비활성화, 1: 활성화)
int round = 1; // 현재 라운드
int enemies_remaining = 0; // 남아있는 적의 수
Bullet bullets[MAX_BULLETS];

// 보스 외형 //
const char *boss_shape[3] = {
    " /-^-\\ ",
    "<     >",
    " \\-o-/ "
};

void init_boss() {
    boss.x = 30;
    boss.y = 2; // 보스의 초기위치
    boss.width = 7;
    boss.height = 3; // 보스 크기 7*3
    boss.direction 수 //
void update_boss() {
    if (boss_active == 0) return; // 보스가 비활성화되면 아무것도 안 함
    boss.x += boss.direction; // 방향에 따라 x 위치 갱신
    if (boss.x <= 0 || boss.x + boss.width >= WIDTH) {
        boss.direction *= -1; // 벽에 닿으면 방향 반전
    }

    // 발사 쿨다운 감소 및 발사
    if (--boss.fire_cooldown <= 0) {
        if (boss.hp > boss.max_hp / 2) {
	    // 체력 많을 때: 중앙에서 한 발
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active == 0) {
                    bullets[i].x = boss.x + boss.width / 2;
                    bullets[i].y = boss.y + boss.height;
                    bullets[i].active = 1;
                    break;
                }
            }
        } else {
	    // 체력 적을 때: 양쪽에서 두 발 (고정 위치)
            int offset1 = 1;
            int offset2 = boss.width - 2;
            int fired = 0;
            for (int i = 0; i < MAX_BULLETS && fired < 2; i++) {
                if (bullets[i].active == 0) {
                    bullets[i].x = boss.x + (fired == 0 ? offset1 : offset2);
                    bullets[i].y = boss.y + boss.height;
                    bullets[i].active = 1;
                    fired++;
                }
            }
        }
        boss.fire_cooldown = 10; // 쿨다운은 상황에 맞게 조절 가능
    }
}

// 보스 출력 //
void draw_boss() {
    for (int i = 0; i < boss.height; i++) {
        for (int j = 0; j < boss.width; j++) {
            int bx = boss.x + j;
            int by = boss.y + i;
            if (bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT) {
                mvaddch(by, bx, boss_shape[i][j]); // 해당 좌표에 문자 출력하는 ncurses 함수
            }
        }
    }
}

// ========== 보스 총알 이동 ========== //
void update_boss_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y++; // 아래로 이동동
            if (bullets[i].y >= HEIGHT) {
                bullets[i].active = 0; // 화면 밖으로 나가면 비활성화(사라짐)
            }
        }
    }
}

// 보스 총알 출력 //
void draw_boss_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            mvaddch(bullets[i].y, bullets[i].x, '|');
        }
    }
}

