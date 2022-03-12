/*
	�C�����C���A�Z���u���R�[�h�𗘗p���A�����������Z���߂����s���܂��B

	[���]
		�C�����C���A�Z���u�����g���AFPU �̐��w�֐������s���܂��B
		�֐��ďo�����̃I�[�o�[�w�b�h���󂯂��A�����ɐ��w�֐������s�ł��܂��B

		asm �\���� Constranits �� fp ���W�X�^���w�肷��ꍇ�� "f" ���g���܂��B

	[!!!!! ���� !!!!!]
		�{�R�[�h�����s����ɂ́AFPU �𓋍ڂ��� X68030 �����K�v�ł��B����ȊO
		�̊��Ŏ��s����ƁA�N���ł��Ȃ����N���b�V�����܂��B
		�܂� CPU ���������Ă���ꍇ�����ӂ��K�v�ł��B�㔭�� 68040 �ȍ~�� CPU 
		�ł� FPU �� CPU �����ƂȂ�܂������A�ꕔ�̕��������_���Z���߂��T�|�[�g
		����Ă��Ȃ����߁A�R���p�C���I�v�V������ -m68881 ���w�肵�Đ�������
		�R�[�h�͓��삷��ۏ؂�����܂���B68040 �ȍ~�Ή��̃R�[�h�𐶐�����ꍇ
		�� -m68881 �͎w�肹���A-m68040 �� -m68060 �Ȃǂ� CPU �̎�ނ��w�肷��
		�I�v�V�����݂̂��w�肵�܂��B
*/

#include <stdlib.h>
#include <stdio.h>

float fpu_acosf(float x)
{
	float value;
	/*
		�����Ŏ��s����R�[�h�́A�����ɃX�e�[�g����؎����Ȃ��̂ŁA���s������
		�ǂ̂悤�ɓ���ւ��Ă����ʂ͕ω����Ȃ��B���̂悤�ȃR�[�h�̓R���p�C����
		reordering �����邱�ƂŁA���ǂ��R�[�h��������ꍇ������B
		asm �\���� volatile ���w�肵�Ȃ����Ƃ� reordering ��������B
	*/
	asm (
		"facos.x %1,%0"
	:	/* �o�� */	"=f"	(value)
	:	/* ���� */	"f"		(x)
	);
	return value;
}

double fpu_acos(double x)
{
	double value;
	/* �R���p�C���ɂ�� reordering ��������i�ڍׂ͑O�q�j*/
	asm (
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
