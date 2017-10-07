#include "Util.h"


double erand48()
{	 
	return (double)rand() / RAND_MAX;
}

int toInt(double x)
{
	return int(pow(clamp(x), 1 / 2.2) * 255 + .5);  // 0-1 to 0-255 with Gamma Correction
}

double clamp(double x) // into 0-1
{
	return x < 0 ? 0 : x>1 ? 1 : x;
}

#pragma pack(2)
typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short WORD;

struct BMPFILEHEADER_T {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
};

struct BMPINFOHEADER_T {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
};


void savebmp(unsigned char * pdata, char * bmp_file, int width, int height)
{
	int size = width*height * 3 * sizeof(char); // ÿ�����ص�3���ֽ�  
	// λͼ��һ���֣��ļ���Ϣ  
	BMPFILEHEADER_T bfh;
	bfh.bfType = (WORD)0x4d42;  //bm  
	bfh.bfSize = size  // data size  
		+ sizeof(BMPFILEHEADER_T) // first section size  
		+ sizeof(BMPINFOHEADER_T) // second section size  
		;
	bfh.bfReserved1 = 0; // reserved  
	bfh.bfReserved2 = 0; // reserved  
	bfh.bfOffBits = sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T);//���������ݵ�λ��  

	// λͼ�ڶ����֣�������Ϣ  
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = -height;//BMPͼƬ�����һ���㿪ʼɨ�裬��ʾʱͼƬ�ǵ��ŵģ�������-height������ͼƬ������  
	bih.biPlanes = 1;//Ϊ1�����ø�  
	bih.biBitCount = 24;
	bih.biCompression = 0;//��ѹ��  
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 2835;//����ÿ��  
	bih.biYPelsPerMeter = 2835;
	bih.biClrUsed = 0;//���ù�����ɫ��24λ��Ϊ0  
	bih.biClrImportant = 0;//ÿ�����ض���Ҫ  
	FILE * fp = fopen(bmp_file, "wb");
	if (!fp) return;

	fwrite(&bfh, 8, 1, fp);//����linux��4�ֽڶ��룬����Ϣͷ��СΪ54�ֽڣ���һ����14�ֽڣ��ڶ�����40�ֽڣ����ԻὫ��һ���ֲ���Ϊ16�Լ���ֱ����sizeof����ͼƬʱ�ͻ�����premature end-of-file encountered����  
	fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);
	fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);
	fwrite(&bih, sizeof(BMPINFOHEADER_T), 1, fp);
	fwrite(pdata, size, 1, fp);
	fclose(fp);
}
