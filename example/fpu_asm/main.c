/*
	�C�����C���A�Z���u���R�[�h�𗘗p���A�����������Z���߂����s���܂��B

	[���]
		�C�����C���A�Z���u�����g���AFPU �̐��w�֐������s���܂��B
		�֐��ďo���I�[�o�[�w�b�h�Ȃ����w�֐������s�ł��܂��B

		asm �\���� fp ���W�X�^����o�͎w�肷��ꍇ "f" ���g���܂��B

	[!!!!! ���� !!!!!]
		�{�R�[�h�����s����ɂ́AFPU �𓋍ڂ��� X68030 �����K�v�ł��B
		����ȊO�̊��Ŏ��s����ƁA�N���ł��Ȃ����N���b�V�����܂��B
		�܂� CPU ���������Ă���ꍇ�����ӂ��K�v�ł��B�㔭�� 68040 �ȍ~��
		CPU �ł� FPU �� CPU �����ƂȂ�܂������A�ꕔ�̕��������_���Z���߂�
		�T�|�[�g����Ă��Ȃ����߁A-m68881 ���w�肵�Đ��������R�[�h��
		FPU �̐��w�֐����p�����R�[�h�͓��삷��ۏ؂�����܂���B
*/

#include <stdlib.h>
#include <stdio.h>

float fpu_acosf(float x)
{
	float value;
    asm volatile (
    	"facos.x %1,%0"
    :	/* �o�� */	"=f"	(value)
    :	/* ���� */	"f"		(x)
    );
    return value;
}

double fpu_acos(double x)
{
	double value;
    asm volatile (
    	"facos.x %1,%0"
    :	/* �o�� */	"=f"	(value)
    :	/* ���� */	"f"		(x)
    );
    return value;
}

int main(int argc, char *argv[]){
	printf(
		"fpu_acosf(-1.0f) = %.10f (expected value = 3.141592653...)\n",
		fpu_acosf(-1.0f)
	);
	printf(
		"fpu_acos(-1.0) = %.10f (expected value = 3.141592653...)\n",
		fpu_acos(-1.0)
	);
	return 0;
}
