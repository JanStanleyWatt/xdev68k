/*
	2 �o�C�g�ڂ� 0x5c �� Shift-JIS �R�[�h�������R���\�[���ɏo�͂��܂��B

	[���]
		2 �o�C�g�ڂ� 0x5c �� Shift-JIS �R�[�h�����́A0x5c ���G�X�P�[�v
		�V�[�P���X�̊J�n�ƌ�F������邽�߁Am68k-elf-gcc �̃f�t�H���g
		�ݒ�ł͐������R���p�C���ł��܂���B

		�{�T���v���R�[�h�ł́Am68k-elf-gcc �̃R���p�C���I�v�V������
			-finput-charset=cp932 -fexec-charset=cp932
		���w�肷�邱�ƂŁA���̖�肪����ł��邱�Ƃ������܂��B

		�Ȃ��A�� X68K gcc �ł́A�\�[�X�R�[�h�� Shift-JIS �ŃG���R�[�h
		����Ă��邱�Ƃ�O��Ƃ�������ɂȂ��Ă��邽�߁A���̂悤�ȑΏ���
		�s�v�ł����B
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	printf("0x5c�����e�X�g�i��������j\n");
	printf("	�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\n");
	printf("	IBM�g�������iX68K �ł͕\������Ȃ��j: �\�\\n");
	printf("	NEC��`��IBM�g�������iX68K �ł͕\������Ȃ��j: �x�x\n");
	printf("0x5c�����e�X�g�i�����܂Łj\n");
	return 0;
}

