#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common_ny.h"
#include "io_ny.h"
#include "display_ny.h"

void init(void);
void intro(void);
void outro(void);
void cursor_move(DIRECTION dir);
void sample_obj_move(void);
POSITION sample_obj_next_position(void);

/* ================= control =================== */
int sys_clock = 0;		// system-wide clock(ms)
CURSOR cursor = { { 1, 1 }, {1, 1} };

/* ================= game data =================== */
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

RESOURCE resource = {
	.spice = 0,
	.spice_max = 100,
	.population = 10,
	.population_max = 50
};

OBJECT_SAMPLE obj = {
	.pos = {1, 1},
	.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
	.repr = 'o',
	.speed = 300,
	.next_move_time = 300
};

/*========= map data ==========*/
BUILD_1x1 rock1 = {
	.pos = {3,43},
	.build = true,
	.name = 'R',
	.type = 6
};

BUILD_1x1 rock2 = {
	.pos = {11, 9},
	.build = true,
	.name = 'R',
	.type = 6
};

BUILD_1x1 rock3 = {
	.pos = {16,50},
	.build = true,
	.name = 'R',
	.type = 6
};

BUILD_2x2 rock4 = {
	.pos1_1 = {4, 17},
	.pos1_2 = {4, 18},
	.pos2_1 = {5, 17},
	.pos2_2 = {5, 18},
	.name = 'R',
	.build = true,
	.type = 6
};

BUILD_2x2 rock5 = {
	.pos1_1 = {11, 34},
	.pos1_2 = {11, 35},
	.pos2_1 = {12, 34},
	.pos2_2 = {12, 35},
	.name = 'R',
	.build = true,
	.type = 6
};
/*========= game data ==========*/
BUILD_1x1 spice_1 = {
	.pos = {7,2},
	.build = true,
	.name = '5',
	.type = 4
};

BUILD_1x1 spice_2 = {
	.pos = {10,57},
	.build = true,
	.name = '5',
	.type = 4
};

BUILD_1x1 sandwam1 = {
	.build = true,
	.name = 'W',
	.pos = {4, 7},
	.type = 3
};

BUILD_1x1 sandwam2 = {
	.build = true,
	.name = 'W',
	.pos = {12, 52},
	.type = 3
};

/*========= haconen data ==========*/

BUILD_2x2 haconen_base = {
	.pos1_1 = {2, 57},
	.pos1_2 = {2, 58},
	.pos2_1 = {3, 57},
	.pos2_2 = {3, 58},
	.name = 'B',
	.build = true,
	.type = 2
};

BUILD_2x2 haconen_p1 = {
	.pos1_1 = {2, 55},
	.pos1_2 = {2, 56},
	.pos2_1 = {3, 55},
	.pos2_2 = {3, 56},
	.name = 'P',
	.build = true,
	.type = 5
};

BUILD_1x1 haconen_hb1 = {
	.pos = {4,58},
	.name = 'H',
	.build = true,
	.type = 2
};

/*========= player data ==========*/

BUILD_2x2 player_base = {
	.pos1_1 = {16, 1},
	.pos1_2 = {16, 2},
	.pos2_1 = {17, 1},
	.pos2_2 = {17, 2},
	.name = 'B',
	.build = true,
	.type = 1
};

BUILD_2x2 player_p1 = {
	.pos1_1 = {14, 1},
	.pos1_2 = {14, 2},
	.pos2_1 = {15, 1},
	.pos2_2 = {15, 2},
	.name = 'P',
	.build = true,
	.type = 5
};

BUILD_1x1 player_hb1 = {
	.pos = {17,3},
	.name = 'H',
	.build = true,
	.type = 1
};

/*=============  =============*/

int main(void) {
	srand((unsigned int)time(NULL));

	init();
	intro();
	display(resource, map, cursor, haconen_base, player_base,haconen_p1,player_p1,haconen_hb1,player_hb1,spice_1,spice_2,sandwam1,sandwam2,rock1,rock2,rock3,rock4,rock5);

	while (1) {
		KEY key = get_key();

		if (is_arrow_key(key)) {
			cursor_move(ktod(key));
		}
		else {
			switch (key) {
			case k_quit: outro();
			default: break;
			}
		}

		sample_obj_move();

		display(resource, map, cursor, haconen_base,player_base,haconen_p1,player_p1,haconen_hb1,player_hb1,spice_1,spice_2, sandwam1, sandwam2, rock1, rock2, rock3, rock4, rock5);
		Sleep(TICK);
		sys_clock += 10;
	}
}

void intro(void) {
	printf("\t\t\t\t\t\tDUNE 1.5\n");
	printf("\t\t\t\t\t\tHello. New Player.\n\n\n");
	printf("\t\t\t\t\t\tStarting ...\n");
	Sleep(2000);
	system("cls");
}

void outro(void) {
	printf("\n\nExiting...\n");
	Sleep(1500);
	system("cls");
	printf("\nThankyou for playing.\n");
	exit(0);
}

void init(void) {
	for (int j = 0; j < MAP_WIDTH; j++) {
		map[0][0][j] = '#';
		map[0][MAP_HEIGHT - 1][j] = '#';
	}

	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		map[0][i][0] = '#';
		map[0][i][MAP_WIDTH - 1] = '#';
		for (int j = 1; j < MAP_WIDTH - 1; j++) {
			map[0][i][j] = ' ';
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[1][i][j] = -1;
		}
	}

	map[1][obj.pos.row][obj.pos.column] = 'o';
}

// (가능하다면) 지정한 방향으로 커서 이동
void cursor_move(DIRECTION dir) {
	POSITION curr = cursor.current;
	POSITION new_pos = pmove(curr, dir);

	// validation check
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}
/*void cursor_move(DIRECTION dir) {
    int current_time = sys_clock;

    // 이전 입력과 현재 입력 시간 차이를 계산
    if (last_dir == dir && (current_time - last_key_time) < DOUBLE_KEY_THRESHOLD) {
        // 방향키가 연속적으로 두 번 입력되었을 때
        POSITION curr = cursor.current;
        POSITION new_pos = pmove(curr, dir);  // 한 칸 이동
        for (int i = 0; i < 4; i++) {  // 5칸 이동
            new_pos = pmove(new_pos, dir);
        }

        // 유효한 위치로 이동
        if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
            1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {
            cursor.previous = cursor.current;
            cursor.current = new_pos;
        }
    } else {
        // 단일 방향 입력: 한 칸 이동
        POSITION curr = cursor.current;
        POSITION new_pos = pmove(curr, dir);

        // 위치 이동
        if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
            1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {
            cursor.previous = cursor.current;
            cursor.current = new_pos;
        }
    }

    // 현재 입력된 방향 시간을 저장
    last_dir = dir;
    last_key_time = current_time;
}
*/

/* ================= sample object movement =================== */
POSITION sample_obj_next_position(void) {
	// 현재 위치와 목적지를 비교해서 이동 방향 결정	
	POSITION diff = psub(obj.dest, obj.pos);
	DIRECTION dir;

	// 목적지 도착. 지금은 단순히 원래 자리로 왕복
	if (diff.row == 0 && diff.column == 0) {
		if (obj.dest.row == 1 && obj.dest.column == 1) {
			// topleft --> bottomright로 목적지 설정
			POSITION new_dest = { MAP_HEIGHT - 2, MAP_WIDTH - 2 };
			obj.dest = new_dest;
		}
		else {
			// bottomright --> topleft로 목적지 설정
			POSITION new_dest = { 1, 1 };
			obj.dest = new_dest;
		}
		return obj.pos;
	}

	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
	if (abs(diff.row) >= abs(diff.column)) {
		dir = (diff.row >= 0) ? d_down : d_up;
	}
	else {
		dir = (diff.column >= 0) ? d_right : d_left;
	}

	// validation check
	// next_pos가 맵을 벗어나지 않고, (지금은 없지만)장애물에 부딪히지 않으면 다음 위치로 이동
	// 지금은 충돌 시 아무것도 안 하는데, 나중에는 장애물을 피해가거나 적과 전투를 하거나... 등등
	POSITION next_pos = pmove(obj.pos, dir);
	if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
		1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
		map[1][next_pos.row][next_pos.column] < 0) {

		return next_pos;
	}
	else {
		return obj.pos;  // 제자리
	}
}

void sample_obj_move(void) {
	if (sys_clock <= obj.next_move_time) {
		// 아직 시간이 안 됐음
		return;
	}

	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
	map[1][obj.pos.row][obj.pos.column] = -1;
	obj.pos = sample_obj_next_position();
	map[1][obj.pos.row][obj.pos.column] = obj.repr;

	obj.next_move_time = sys_clock + obj.speed;
}
