#include "DxLib.h"
#include "math.h"
//�z��̐��̒�`
#define field_number 36
#define delx 32
#define pix  32


int main_field[field_number + 1]{
	0,0,0,0,0,0,
	0,1,0,0,1,0,
	1,0,1,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,1,0,
	0,0,0,0,1,0,0
};

//�J���Ă��邩�ǂ����̔���
int field_status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0
};


//����̔��e�̐��̕\��
int status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0
};


//�����Ă鏈���̂��
int flag_status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0

};




//�t�B�[���h�̃��[�g�Ƃ������́i1�����̔z���񎟌��ɕϊ����邽�߂Ɂj
int feald_sqart = 6;

//�}�E�X�������ꂽ��P������Ă��Ȃ����0
int muse_input_status = 0;

//�Q�[�����������邩�̔���@�����Ă���@�O�@����ł���@�P �N���A�Q
int game_status = 0;

//���e�̐��̒�
int bakudan = 6;



//�\���p�̂��
void draw(int bomb, int field, int safe,int flag) {

	int x = 0, y = 0;

	int a = 0;

	for (int i = 0; i < field_number; ++i) {

		y = i / feald_sqart;
		x = i % feald_sqart;


		if (field_status[i] == 1) {

			field_status[i] = 1;

			//���e�������甚�e�̉摜���o��
			if (main_field[i] == 1) {
				DrawGraph(delx + pix * x, delx + pix * y, bomb, TRUE); // ���e�̉摜�`��
				game_status = 1;
			}

			else DrawGraph(delx + pix * x, delx + pix * y, safe, TRUE); // �Ԃ��^�C���̕\��

			//�J�����t�B�[���h�̐��𐔂���B
			a += 1;


			if (a == (field_number - bakudan)) {
				//�Q�[���N���A�̔���
				game_status = 2;
			}


		}

		else {

			field_status[i] = 0;
			DrawGraph(delx + pix * x, delx + pix * y, field, TRUE); // �����^�C���̕\��	


			if (flag_status[i] == 1) {

				DrawGraph(delx + pix * x, delx + pix * y, flag, TRUE); // ���e�̉摜�`��

			}

		}




		int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

		DrawFormatString(delx * 10 + 8 + pix * x, delx + 8 + pix * y, Green, "%d", field_status[i], TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

	}

}




void text_mouse(int x,int y) {

	int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

	DrawFormatString(100, 100, Green, "���W[%d,%d]", x, y); // ������`�悷��

}


//����̔��e�̐���\������
void debug_text(int text, int x, int y) {

	int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

	DrawFormatString(delx + 8 + pix * x, delx + 8 + pix * y, Green, "%d", text, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

}


void game_over() {

	int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

	DrawFormatString(300,100, Green, "game over", TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

}


void game_clear() {

	int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

	DrawFormatString(300, 100, Green, "game clear", TRUE); // �f�[�^�n���h�����g���ĉ摜��`��


}


//���͏�񂩂����Ă���
//���͂����ӏ��̎���̔��e�̐���\��
void check(int x, int y) {


	int a = y * feald_sqart + x;

	//�e�_�̈ʒu�̂�B
	int b[4];

	//0:�� 1:��@2:�E�@3:��
	b[0] = a - 1;
	b[1] = a - feald_sqart;
	b[2] = a + 1;
	b[3] = a + feald_sqart;


	for (int i = 0; i < 4; ++i) {

		//�㉺��I�[�o�[�t���[�������̂���
		if ((b[i] < 0) || (b[i] > field_number)) {
			b[i] = 0;

		}

		//���[�̎��p
		if (((a % feald_sqart) == 0)) {
			b[0] = 0;

		}
		//�E�[�̎��p
		if ((a % feald_sqart) == (feald_sqart - 1)) {

			b[2] = 0;
		}

	}

	status[a] = main_field[b[0]] + main_field[b[1]] + main_field[b[2]] + main_field[b[3]];


}


void bomb_number() {
	//�I�񂾃p�l���̎���̐�����\��
	for (int i = 0; i < field_number; ++i)
		//�p�l�����󂢂Ă��邩�A���e�ł͂Ȃ��ꍇ
		if ((field_status[i] == 1) && (main_field[i] != 1))
			if (status[i] != 0) {

				int yy = i / feald_sqart;
				int xx = i % feald_sqart;

				debug_text(status[i], xx, yy);

			}
}

//�}�E�X������ēy��̏���
void muse_input_left() {

	int mouse_x = 0;
	int mouse_y = 0;


	GetMousePoint(&mouse_x, &mouse_y);
	int x = -1 + mouse_x / pix;
	int y = -1 + mouse_y / pix;
	if (field_status[y * feald_sqart + x] != 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			field_status[y * feald_sqart + x] = 1;

			check(x, y);

		}
	}
}


//�}�E�X������ēy��̏���
void muse_input_rigtt() {

	int mouse_x = 0;
	int mouse_y = 0;


	GetMousePoint(&mouse_x, &mouse_y);
	int x = -1 + mouse_x / pix;
	int y = -1 + mouse_y / pix;


	//��񉟂����������悤�ɂ���
	if (flag_status[y * feald_sqart + x] == 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			flag_status[y * feald_sqart + x] = 0;

		}


	}

	if (field_status[y * feald_sqart + x] != 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			flag_status[y * feald_sqart + x] = 1;

		}
	}
}


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	DxLib_Init(); // DX���C�u��������������


	int bomb;     // �f�[�^�n���h���i�[�p�ϐ�
	bomb = LoadGraph("pictures/bomb.jpg"); // �摜�����[�h

	int field;
	field = LoadGraph("pictures/field.jpg"); // �摜�����[�h

	int safe;
	safe = LoadGraph("pictures/safe.png");

	int flag;
	flag = LoadGraph("pictures/flag.jpg");




	while (1) {

		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}


		if (game_status == 0) {
			ClearDrawScreen(); // ��ʂ�����
			draw(bomb, field, safe, flag);

			int Mouse;
			Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾


			//���̃}�E�X����
			if (Mouse & MOUSE_INPUT_LEFT) {

				if (muse_input_status == 0)
				{
					muse_input_left();
				}
				//�}�E�X�������ꂽ��X�e�[�^�X�̕ύX
				if (muse_input_status == 0)
				{
					muse_input_status = 1;
				}

			}
			else
			{
				muse_input_status = 0;
			}


			//�E�̃}�E�X����
			if (Mouse & MOUSE_INPUT_RIGHT) {

				if (muse_input_status == 0)
				{
					muse_input_rigtt();
				}
				//�}�E�X�������ꂽ��X�e�[�^�X�̕ύX
				if (muse_input_status == 0)
				{
					muse_input_status = 1;
				}

			}

			else
			{
				muse_input_status = 0;
			}


			bomb_number();


		}


		else if (game_status == 1) game_over();

		else if (game_status == 2) game_clear();


		ScreenFlip(); //����ʂ�\��ʂɔ��f

	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
