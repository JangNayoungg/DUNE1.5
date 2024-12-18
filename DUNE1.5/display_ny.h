/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common_ny.h"

// 표시할 색상 정의. 대충 맞춰 뒀는데, 취향껏 추가하거나 변경하기
#define COLOR_DEFAULT	15
#define COLOR_CURSOR	112
#define COLOR_RESOURCE  112

// 지금은 자원, 맵, 커서만 표시
// 앞으로 화면에 표시할 내용들 여기에 추가하기
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor,
	BUILD_2x2 haconen_base,
	BUILD_2x2 player_base,
	BUILD_2x2 haconen_p1,
	BUILD_2x2 player_p1,
	BUILD_1x1 haconen_hb1,
	BUILD_1x1 player_hb1,
	BUILD_1x1 spice_1,
	BUILD_1x1 spice_2,
	BUILD_1x1 sandwam1,
	BUILD_1x1 sandwam2,
	BUILD_1x1 rock1,
	BUILD_1x1 rock2,
	BUILD_1x1 rock3,
	BUILD_2x2 rock4,
	BUILD_2x2 rock5
);

#endif