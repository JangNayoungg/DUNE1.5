/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display_ny.h"
#include "io_ny.h"

// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };

const POSITION system_message_pos = { MAP_HEIGHT + 2, 0 };
const POSITION object_info_pos = { 1, MAP_WIDTH + 2 };
const POSITION commands_pos = { MAP_HEIGHT + 10, MAP_WIDTH + 2 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

// 함수 정의
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_buildings_2x2(BUILD_2x2 haconen_base);
void display_system_message(void);
void display_object_info(void);
void display_commands(void);

void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor,
	BUILD_2x2 haconen_base,
	BUILD_2x2 player_base
)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	display_buildings_2x2(haconen_base);
	display_buildings_2x2(player_base);
	display_system_message();
	display_object_info();
	display_commands();
}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// 2x2 크기 프린트 함수
void display_buildings_2x2(BUILD_2x2 obj) {
	int prColor = 0;
	if (obj.build) {
		switch (obj.type)
		{
		case 1:
			set_color(9); // 플레이어 진영 파란색
			prColor = 9;
			break;
		case 2:
			set_color(12); // 상대 진영 빨간색
			prColor = 12;
			break;
		case 3:
			set_color(14); // 샌드웜 노란색
			prColor = 14;
			break;
		case 4:
			set_color(6); // 스파이스 주황색
			prColor = 6;
			break;
		case 5:
			set_color(8); // 장판 검정색
			prColor = 8;
			break;
		case 6:
			set_color(7); // 기타 진영 회색
			prColor = 7;
			break;
		}
		printc(obj.pos1_1, obj.name, prColor);
		printc(obj.pos1_2, obj.name, prColor);
		printc(obj.pos2_1, obj.name, prColor);
		printc(obj.pos2_2, obj.name, prColor);
	}
}

// 1x1 프린트 함수
void display_buildings_1x1(BUILD_1x1 obj) {
	int prColor = 0;
	if (obj.build) {
		switch (obj.type)
		{
		case 1:
			set_color(9); // 플레이어 진영 파란색
			prColor = 9;
			break;
		case 2:
			set_color(12); // 상대 진영 빨간색
			prColor = 12;
			break;
		case 3:
			set_color(14); // 샌드웜 노란색
			prColor = 14;
			break;
		case 4:
			set_color(6); // 스파이스 주황색
			prColor = 6;
			break;
		case 5:
			set_color(8); // 장판 검정색
			prColor = 8;
			break;
		case 6:
			set_color(7); // 기타 진영 회색
			prColor = 7;
			break;
		}
		printc(obj.pos, obj.name, prColor);
	}
}

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = { i, j };
				printc(padd(map_pos, pos), backbuf[i][j], COLOR_DEFAULT);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}
}

void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}

void display_system_message() {
	set_color(COLOR_DEFAULT);
	gotoxy(system_message_pos);
	printf("System Message: Welcome to Dune 1.5");
}

void display_object_info() {
	set_color(COLOR_DEFAULT);
	gotoxy(object_info_pos);
	printf("Object Info: Displaying detailed stats...");
}

void display_commands() {
	set_color(COLOR_DEFAULT);
	gotoxy(commands_pos);
	printf("Commands: Use arrow keys to navigate, 'q' to quit.");
}
