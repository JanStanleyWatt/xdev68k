/*
	�C�����C���A�Z���u���R�[�h�𗘗p���A������Z���Z���߂𐶐����܂��B

	[���]
		gcc �́A�����̏�Z���Z���r���g�C���֐��Ŏ��s����R�[�h�𐶐����܂��B
		�r���g�C���֐��ɂ�鐮���̏�Z���Z�́A32bit vs 32bit �ōs���邽�߁A
		�I�[�o�[�w�b�h���傫���ł��B

		���̖����������ɂ́A�C�����C���A�Z���u���R�[�h�𗘗p���ACPU ��
		�{�������Ă��鐮����Z���Z���߂𒼐ڐ�������悤�ɂ��܂��B
*/

#include <stdlib.h>
#include <stdio.h>

unsigned int mulu(unsigned short a, unsigned short b) {
	/* �R���p�C���ɂ�� reordering ������ */
	unsigned int ret;
	/*
		mulu a,b �́A�^���R�[�h�Ŏ����ƁAb = b * a �ƂȂ�B
		�܂�Aa �� b ���󂯎��Ab �����ʂŏ㏑������悤�ȓ���ł���B
		�]���āA���̓��X�g�ɂ� a b �̓�̈����������K�v������B
		�o�̓��X�g�ɂ͌��ʎ󂯎��p�̕ϐ� ret ���w�肷��B
		ret �� b ������̃��W�X�^�����L���Ă���|�� gcc �ɋ�����K�v������B
	*/
	asm (
		"	mulu %1,%0\n"
	:	/* �o�� */	"=d"	(ret)	/* out %0 (�߂�l) */
	:	/* ���� */	"d"		(a),	/* in  %1 (����) */
					"0"		(b)		/* in  %2 (����) = %0 �Ɠ������W�X�^�Ɋ��蓖�� */
	);
	return ret;
}
int muls(short a, short b) {
	/* �R���p�C���ɂ�� reordering ������ */
	unsigned int ret;
	asm (
		"	muls %1,%0\n"
	:	/* �o�� */	"=d"	(ret)	/* out %0 (�߂�l) */
	:	/* ���� */	"d"		(a),	/* in  %1 (����) */
					"0"		(b)		/* in  %2 (����) = %0 �Ɠ������W�X�^�Ɋ��蓖�� */
	);
	return ret;
}
unsigned short divu(unsigned int a, unsigned short b) {
	/* �R���p�C���ɂ�� reordering ������ */
	unsigned short ret;
	asm (
		"	divu %1,%0\n"
	:	/* �o�� */	"=d"	(ret)	/* out %0 (�߂�l) */
	:	/* ���� */	"d"		(a),	/* in  %1 (����) */
					"0"		(b)		/* in  %2 (����) = %0 �Ɠ������W�X�^�Ɋ��蓖�� */
	);
	return ret;
}
short divs(int a, short b) {
	/* �R���p�C���ɂ�� reordering ������ */
	unsigned short ret;
	asm (
		"	divs %1,%0\n"
	:	/* �o�� */	"=d"	(ret)	/* out %0 (�߂�l) */
	:	/* ���� */	"d"		(a),	/* in  %1 (����) */
					"0"		(b)		/* in  %2 (����) = %0 �Ɠ������W�X�^�Ɋ��蓖�� */
	);
	return ret;
}


int main(int argc, char *argv[]){
	printf(
		"mulu(2,3) = %d (expected value = 6)\n",
		mulu(2,3)
	);
	printf(
		"muls(2,-3) = %d (expected value = -6)\n",
		muls(2,-3)
	);
	printf(
		"divu(3,6) = %d (expected value = 2)\n",
		divu(3,6)
	);
	printf(
		"divs(3,-6) = %d (expected value = -2)\n",
		divs(3,-6)
	);
	return 0;
}
