#include "DxLib.h"
#include "math.h"
//�z��̐��̒�`
#define field_number 36
#define delx 32
#define pix  32


int main_field[field_number]{
	0,0,0,0,0,0,
	0,1,0,0,1,0,
	1,0,1,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,1,0,
	0,0,0,0,1,0

};


int field_status[field_number]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,

};


//����̔��e�̐��̕\��
int status[field_number]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,

};

//�t�B�[���h�̃��[�g�Ƃ������́i1�����̔z���񎟌��ɕϊ����邽�߂Ɂj
int feald_sqart = 6;


//�\���p�̂��
void draw(int bomb, int field, int safe) {

	int x = 0, y = 0;
	for (int i = 0; i < field_number; ++i) {

		y = i / feald_sqart;
		x = i % feald_sqart;


		if (field_status[i] == 1) {

			field_status[i] = 1;

			//���e�������甚�e�̉摜���o��
			if (main_field[i] == 1) {
				DrawGraph(delx + pix * x, delx + pix * y, bomb, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
			}

			else DrawGraph(delx + pix * x, delx + pix * y, safe, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

		}

		else {
			field_status[i] = 0;
			DrawGraph(delx + pix * x, delx + pix * y, field, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
		
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


//���͏�񂩂����Ă���
//���͂����ӏ��̎���̔��e�̐���\��
void check(int x,int y) {


	int a = y * feald_sqart + x;

	//�e�_�̈ʒu�̂�B
	int b [4];

	//0:�� 1:��@2:�E�@3:��
	b[0] = a - 1;
	b[1] = a - feald_sqart;
	b[2] = a + 1;
	b[3] = a + feald_sqart;



	for (int i = 0; i < 4; ++i) {

		//�㉺��I�[�o�[�t���[�������̂���
		if ((b[i] < 0) || (b[i] >= field_number)) {
			b[i] = 0;

		}

		//���[�̎��p
		if (((a % feald_sqart) == 0) ) {
			b[0] = 0;

		}
		//�E�[�̎��p
		if ((a % feald_sqart) == (feald_sqart - 1)) {

			b[2] = 0;
		}

	}



	status[a] = main_field[b[0]] + main_field[b[1]] + main_field[b[2]] + main_field[b[3]];
	
	//�I�񂾃p�l���̎���̐�����\��
	for (int i = 0; i < field_number; ++i) {

		//�p�l�����󂢂Ă��邩�A���e�ł͂Ȃ��ꍇ
		if ((field_status[i] == 1)&&(main_field[i]!=1)) {
			
			if (status[i] != 0) {

				int yy = i / feald_sqart;
				int xx = i % feald_sqart;


				debug_text(status[i], xx, yy);


			}

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

	int mouse_x = 0;
	int mouse_y = 0;



	while (1) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}
		ClearDrawScreen(); // ��ʂ�����
		draw(bomb, field, safe);

		int Mouse;
		Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾


		GetMousePoint(&mouse_x, &mouse_y);
		int x = -1 + mouse_x / 32;
		int y = -1 + mouse_y / 32;

		//�}�E�X���͓r��
		if (Mouse & MOUSE_INPUT_LEFT) {

			if (field_status[y * feald_sqart + x] != 1) {
				if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y))
					field_status[y * feald_sqart + x] = 1;
			}

			text_mouse(x, y);

		}

		check(x, y);

		ScreenFlip(); //����ʂ�\��ʂɔ��f

	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}




