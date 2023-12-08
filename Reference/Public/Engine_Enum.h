#pragma once

namespace Engine
{
// 	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
// 	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

}
enum class KEY_STATE {
	TAP, // 막 누른 시점
	HOLD,// 꾹 누르고 있음
	AWAY,// 막 뗀 시점
	NONE,// 걍 안눌린 상태
};
enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_MWU, DIM_MWD, DIM_END }; /* 왼쪽 오른쪽 중앙 / 위로휠 아래로 휠 */
enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };