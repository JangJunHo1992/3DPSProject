#pragma once

namespace Engine
{
// 	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
// 	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

}
enum class KEY_STATE {
	TAP, // �� ���� ����
	HOLD,// �� ������ ����
	AWAY,// �� �� ����
	NONE,// �� �ȴ��� ����
};
enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_MWU, DIM_MWD, DIM_END }; /* ���� ������ �߾� / ������ �Ʒ��� �� */
enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };