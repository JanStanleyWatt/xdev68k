/*
	�A�Z���u���Œ��ڋL�q�����֐����AC �֐��̌ďo���K��𗘗p�����A�C�����C��
	�A�Z���u�����璼�ڃR�[��������@���܂Ƃ߂܂��B

	[���]
		C �֐��̌ďo���K��́A�ȉ��̗��R����I�[�o�[�w�b�h���傫���ł��B

			1) ��������ɃX�^�b�N�o�R�Ŏ󂯓n�����Ȃ���΂Ȃ�Ȃ�
			2) ��Ƀ��W�X�^ d0-d2/a0-a2 ���j�󃌃W�X�^�Ƃ��Ĉ�����
			3) ��Ƀ������o���A��������

		�C�����C���A�Z���u���𗘗p���Ē��ڊ֐��R�[�����邱�ƂŁA���̃I�[�o�[
		�w�b�h������ł���ꍇ������܂��B
*/

#include <stdlib.h>
#include <stdio.h>


/*
	strlcpy �́A������R�s�[���s���֐��ł���B

		�錾
			size_t strlcpy(char *dst, const char *src, size_t siz);

		����
			siz = ������R�s�[��̃������̈�̃T�C�Y
			src = ������R�s�[��
			dst = ������R�s�[��

		�߂�l
			�R�s�[��ɍ쐬�����݂�������̒����i�I�[ \0 �������j�B
			�߂�l >= siz �Ȃ�A������R�s�[��̃�����̈悪�s��
			���Ă������Ƃ������B

	my_strlcpy �́Astrlcpy �݊��֐��̃A�Z���u���R�[�h�����ł���B
	���́A�o�́A�j�󃌃W�X�^�͈ȉ��̂Ƃ���ł���B

		����
			d0.l = siz
			a0.l = src
			a1.l = dst

		�o��
			d0.l = �߂�l

		�j��
			d0 d1 d2
			a0 a1
*/


#define FORCE_INLINE __attribute__((__always_inline__)) inline
static FORCE_INLINE size_t my_strlcpy(char *dst, const char *src, size_t siz) {
	/*
		my_strlcpy �͓��o�͂��Œ�̃��W�X�^�ōs���̂ŁA
		���̎󂯓n���p�� register �����������ϐ����K�v�B
	*/
	register       size_t reg_d0 asm ("d0") = siz;
	register const char * reg_a0 asm ("a0") = src;
	register       char * reg_a1 asm ("a1") = dst;

	/*
		asm �\���ł́A���o�̓��X�g�A�j�󃊃X�g�A�������o���A�����w�肷��B
		���o�̓��X�g�� Constranits�A�j�󃊃X�g�� Clobbers �ƌĂ΂��B

		�܂��A���o�̓��X�g�Ɣj�󃊃X�g�̎w����s���B
		�����ł͘b��P���ɂ��邽�߁Aasm �\���̓��o�̓��W�X�^���A�ȉ��� 3 ��
		�̃J�e�S���ɕ����čl����B

			1) out
				�E�A�Z���u���R�[�h���ŏ������ݐ�p
				�E�o�̓��X�g�ɋL�q
				�EConstranits : "=r"

			2) in out
				�E�A�Z���u���R�[�h���œǂݏ���
				�E�o�̓��X�g�ɋL�q
				�EConstranits : "+r"

			3) in
				�E�A�Z���u���R�[�h���œǂݎ���p
				�E���̓��X�g�ɋL�q
				�EConstranits : "r"

		my_strlcpy �� d0 a0 a1 �́A���͂��X�V�܂��͔j�󂳂�郌�W�X�^�Ȃ̂�
		(2) �� in out ���W�X�^�ɕ��ނ���Bd0 a0 a1 �̂��� d0 �̏o�݂͂̂����p
		����Aa0 a1 �͔j������Ă���ƍl����B

		�j�󃊃X�g�ɋL�q���郌�W�X�^�́A���o�̓��W�X�^�Ƃ��ďo�������A�j�󂾂�
		�������̂Ɍ���Bmy_strlcpy �ł́Ad1 d2 ���Y������B

		a0 a1 ��j�󃊃X�g�ɋL�q����ƁAConstranits �� Clobbers ���Փ˂��Ă���
		�Ƃ����R���p�C���G���[�ɂȂ�B�O�q�̂Ƃ���Aa0 a1 �͔j�󃌃W�X�^�ł�
		�Ȃ� in out ���W�X�^�ƌ��Ȃ����ƂŁA���̖���������邱�Ƃ��ł���B

		���ɁA�������o���A�̎w����s���B
		���� a0.l ���w���̈悩��A���W�X�^��ȂǂɃL���b�V�����ꂽ�f�[�^��
		���菑���߂����K�v�ȏꍇ�A�����߂��� my_strlcpy ���s�O�Ɋ�������K�v��
		����B�܂��A���� a1.l ���w���̈�� my_strlcpy �ďo���ɂ���ď�������
		����̂ŁA�ďo���O�ɂ��̗̈悩�烌�W�X�^���ɃL���b�V�������f�[�^�́A
		�ēǂݍ��݂��K�v�ɂȂ�B
		���̂悤�ȑΏ����K�v�ł��邱�Ƃ��R���p�C���ɓ`����ɂ́A�j�󃊃X�g��
		"memory" ���w�肵�ă������o���A��v������K�v������B

		�����]�k�ɂȂ邪�A���� my_strlcpy ���^����ꂽ�������̈�� read only
		�݂̂ŃA�N�Z�X����؏��������Ȃ����삾�Ƃ��Ă��Amy_strlcpy ���s�O��
		�����̃������̈�ւ̃f�[�^�������݂��m���Ɋ������Ă��邱�Ƃ�ۏ؂���
		���߁A�������o���A��v������K�v������Bread only �ɂ��ւ�炸�A�j��
		���X�g�� "memory" ���w�肷��̂͒����ɔ����邩������Ȃ����A�w���ӂ�
		�Ɛ���ɓ��삵�Ȃ��R�[�h����������Ă��܂��B

		�������o���A�̎w��͑傫�ȃI�[�o�[�w�b�h�𔺂��̂ŁA�K�v�Ȃ��P�[�X�ł�
		�ȗ����邱�Ƃ��]�܂����B�������ɁA�֐����Ń������A�N�Z�X���s���Ă��Ă�
		����炪�֐��Ăяo�������猩���Ȃ��̈�i���̊֐����� static �ϐ��Ȃǁj
		�ɑ΂��Ă̂ݍs����ꍇ�́A�������o���A�͕s�v�ł���B
	*/
	asm volatile (
			"	jbsr	_my_strlcpy\n"
	:	/* �o�� */	"+r"	(reg_d0),	/* in out %0 (���́��߂�l) */
					"+r"	(reg_a0),	/* in out %1 (���́��j��) */
					"+r"	(reg_a1)	/* in out %2 (���́��j��) */
	:	/* ���� */
	:	/* �j�� */	"memory",			/* �������o���A��v�� */
					"d1", "d2"
	);
	return reg_d0;
}


int main(int argc, char *argv[]){

	char dst[256];
	char src[] = "test string";

	int siz = sizeof(dst);
	int ret = my_strlcpy(dst, src, siz);
	printf(
		"dst = %s\n"
		"siz = %d\n"
		"ret = %d\n"
		"%s",
		dst,
		siz,
		ret,
		(ret >= siz)? "buffer shortage": "succeeded"
	);

	return 0;
}
