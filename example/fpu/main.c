/*
	浮動小数演算命令を利用します。

	[解説]
		このサンプルコードでは、浮動小数演算命令を利用し、簡単な計算を行う
		例を示します。

		浮動小数演算命令は、MC68881 や MC68882 などの FPU を搭載した X68030
		以上の環境で利用可能です。FLOAT2.X FLOAT3.X などの浮動小数点演算
		パッケージが提供する FE ファンクションとは異なり、オーバーヘッドが
		ないため、高速な演算が可能です。

		浮動小数演算命令を利用する場合は、コンパイルオプションに
			-m68030 -m68881
		を指定する必要があります。-m68030 の代わりに -m68020 を指定しても、
		生成される命令セットに違いはありません。

	[!!!!! 注意 !!!!!]
		本コードを実行するには、FPU を搭載した X68030 環境が必要です。
		それ以外の環境で実行すると、起動できないかクラッシュします。
		また CPU を換装している場合も注意が必要です。後発の 68040 以降の
		CPU では FPU が CPU 内蔵となりましたが、一部の浮動小数点演算命令が
		サポートされていないため、-m68881 を指定して生成したコードは動作
		する保証がありません。
*/

#include <stdlib.h>
#include <stdio.h>

float a = 1.0;
float b = 2.0;
int main(int argc, char *argv[]){
	float c = a + b;
	printf("%f + %f = %f\n", a, b, c);
	return 0;
}

