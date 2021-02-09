#include "DxLib.h"


int main_field[25]{
	0,0,0,0,0,
	0,1,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,1


};


int field_status[25]{
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0


};

//����̔��e�̐��̕\��
int status[25]{
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0


};



void draw(int bomb,int field,int safe) {

	int x = 0, y = 0;
	for (int i = 0; i < 25; ++i) {


		y = i / 5;
		x = i % 5;

		if (field_status[i] == 1) {

			//���e�������甚�e�̂���o��
			if (main_field[i] == 1) {
				DrawGraph(32 * x, 32 * y, bomb, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
			}


			else DrawGraph(32 * x, 32 * y, safe, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

		}
			

		else DrawGraph( 32 * x,32 * y, field, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��


	}


}

//���͏�񂩂����Ă���
void check() {






}


void text_mouse(int x,int y) {

	


	int Green = GetColor(0, 255, 0);      // �΂̐F�R�[�h���擾

	DrawFormatString(100, 100, Green, "���W[%d,%d]", x, y); // ������`�悷��
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
	field= LoadGraph("pictures/field.jpg"); // �摜�����[�h

	int safe;
	safe = LoadGraph("pictures/safe.png");

	int mouse_x=0;
	int mouse_y=0;

	

	while (1) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}
		ClearDrawScreen(); // ��ʂ�����
		draw(bomb, field,safe);

		int Mouse;
		Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
		

		GetMousePoint(&mouse_x, &mouse_y);
		text_mouse(mouse_x, mouse_y);
		//�}�E�X���͓r��
		if (Mouse & MOUSE_INPUT_LEFT) {


			
			int x = mouse_x / 32;
			int y = mouse_y / 32;

			field_status[y * 5 + x] = 1;

		}


		

		ScreenFlip(); //����ʂ�\��ʂɔ��f


	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}




