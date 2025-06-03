// boss.h
#define BOSS_H

#define MAX_BULLETS 50

typedef struct {
    int x, y; // 보스의 위치
    int width, height; // 보스의 크기(너비, 높이)
    int direction; // 이동방향(1:오른쪽, -1:왼쪽)
    int fire_cooldown; // 발사 대기 시간
    int hp; // 보스 현재 체력
    int max_hp; // 보스 최대 체력
} Boss;

// 보스 총알 정의 //
typedef struct {
    int x, y; // 총알 위치
    int active; // 1: 사용 중, 0: 비활성화(안 쓰는 총알)
} Bullet;

// 전역 변수 선언 //
extern Boss boss;
extern int boss_active; // 보스가 현재 활성화 상태인지 아닌지 나타냄
extern int round; // 몇번째 라운드인지 나타냄
extern int enemies_remaining; // 남아있는 적의 수를 나타냄
extern Bullet bullets[MAX_BULLETS]; // 보스가 발사하는 총알 정보 구조체

// 보스 관련 함수들 //
void init_boss();
void update_boss();
void update_boss_bullets();
void draw_boss();
void draw_boss_bullets();
