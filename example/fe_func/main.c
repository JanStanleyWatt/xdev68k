/*
	FE �t�@���N�V�����𗘗p���������������Z�����s���܂��B

	[���]
		���̃T���v���R�[�h�ł́AFE �t�@���N�V�����ƌĂ΂��@�\�𗘗p����
		�����������Z���s����������܂��B

		FE �t�@���N�V�����́AFLOAT2.X FLOAT3.X FLOAT4.X �Ȃǂ̕��������_���Z
		�p�b�P�[�W��g�ݍ��ނ��Ƃŗ��p�\�ɂȂ镂�������_���Z�@�\�ł��B
		FE �t�@���N�V�����́A0xFE ����n�܂� 16 �r�b�g�̖���`���߂����[�U�[
		�v���O�����Ɏ��s�����邱�ƂŁA���������_���Z�p�b�P�[�W���̃R�[�h�ɕ��򂵁A
		���Z�����s���܂��B
		�d�g�ݏ�A�傫�ȃI�[�o�[�w�b�h���������܂��񂪁A���s���ɓ��ڂ����
		���� FPU �̃X�y�b�N�ȂǂɈˑ����Ȃ��݊����̍����v���O�������쐬�\�ł��B

	[!!!!! ���� !!!!!]
		�{�R�[�h�����s����ɂ́A���O�ɕ��������_���Z�p�b�P�[�W��g�ݍ���ł���
		�K�v������܂��B
*/

#include <stdlib.h>
#include <stdio.h>

static inline float my_fadd(float a, float b) {
	register float reg_d0 asm ("d0") = a;
	register float reg_d1 asm ("d1") = b;
	asm volatile (
			".dc.w	0xfe5b\n"		/* 0xfe5b = __FADD */
	:	/* �o�� */	"=d" (reg_d0),	/* out %0 */	/* FE call 0xfe5b �� d0/d1 �Ɍ��ʂ�Ԃ� */
					"=d" (reg_d1)	/* out %1 */	/* FE call 0xfe5b �� d0/d1 �Ɍ��ʂ�Ԃ� */
	:	/* ���� */	"irm" (reg_d0),	/* in %2 */		/* FE call 0xfe5b �� d0.l �����Z���Ƃ��Ď󂯎�� */
					"irm" (reg_d1)	/* in %3 */		/* FE call 0xfe5b �� d1.l �����Z���Ƃ��Ď󂯎�� */
	);
	return reg_d0;
}

float a = 1.0;
float b = 2.0;
int main(int argc, char *argv[]){
	float c = my_fadd(a, b);
	printf("%f + %f = %f\n", a, b, c);
	return 0;
}

