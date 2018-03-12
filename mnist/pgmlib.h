// gray scale image library
#include <stdlib.h>
#include <string.h>

#define MAX_IMAGESIZE 1280
#define MAX_BRIGHTNESS 255
#define GRAYLEVEL 256
#define MAX_FILENAME 256
#define MAX_BUFFERSIZE 256
#define MAX_NUM_OF_IMAGES 5

unsigned char image[MAX_NUM_OF_IMAGES][MAX_IMAGESIZE][MAX_IMAGESIZE];
int width[MAX_NUM_OF_IMAGES], height[MAX_NUM_OF_IMAGES];

void load_image(int n, char name[]);
void save_image(int n, char name[]);
void copy_image(int n1, int n2);
void init_image(int n, unsigned char value); //画像No.nの全画素の階調値を強制的にvalue(0~255)にする


void load_image(int n, char name[])
{
	char file_name[MAX_FILENAME];
	char buffer[MAX_BUFFERSIZE];
	FILE *fp;
	int max_gray;
	int x, y;

	if (name[0] == '\0') {
		printf("input file name (*.pgm) : ");
		scanf("%s", file_name);
	} else strcpy(file_name, name);

	if ((fp = fopen(file_name, "rb")) == NULL) {
		printf("file does not exist.\n");
		exit(1);
	}

	fgets(buffer, MAX_BUFFERSIZE, fp);
	if (buffer[0] != 'P' || buffer[1] != '5') {
		printf("file format does not match P5\n");
		exit(1);
	}

	width[n] = 0;
	height[n] = 0;
	while(width[n]==0 || height[n]==0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			sscanf(buffer, "%d %d", &width[n], &height[n]);
		}
	}

	max_gray = 0;
	while(max_gray==0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			sscanf(buffer, "%d", &max_gray);
		}
	}

	printf("pixel size of width = %d, pixel size of height = %d\n", width[n], height[n]);
	printf("maximum gray scale = %d\n", max_gray);
	if (width[n] > MAX_IMAGESIZE || height[n] > MAX_IMAGESIZE) {
		printf("exceeding expected size of %d x %d\n", MAX_IMAGESIZE, MAX_IMAGESIZE);
		printf("use a smaller sized image\n");
		exit(1);
	}

	if (max_gray != MAX_BRIGHTNESS) {
		printf("maximum scale value is inadequet.\n");
		exit(1);
	}

	for (y=0; y<height[n]; y++) {
		for (x=0; x<width[n]; x++) {
			image[n][x][y] = (unsigned char)fgetc(fp);
		}
	}

	fclose(fp);
	printf("image was read successfully.\n");
}

void save_image(int n, char name[])
{
	char file_name[MAX_FILENAME];
	FILE *fp;
	int x, y;

	if (name[0] == '\0') {
		printf("output file name (*.pgm) : ");
		scanf("%s", file_name);
	} else strcpy(file_name, name);

	if ( (fp=fopen(file_name, "wb"))==NULL ) {
		printf("could not open file\n");
		exit(1);
	}

	fputs("P5\n", fp);
	fputs("# Created by Image Processing\n", fp);
	fprintf(fp, "%d %d\n", width[n], height[n]);
	fprintf(fp, "%d\n", MAX_BRIGHTNESS);
	for (y=0; y<height[n]; y++)
		for (x=0; x<width[n]; x++)
			fputc(image[n][x][y], fp);
		fclose(fp);
		printf("Image was saved successfully\n");
}

//copy n1 to n2
void copy_image(int n1, int n2)
{
	int x, y;

	width[n2] = width[n1];
	height[n2] = height[n1];

	for (y=0; y<height[n1]; y++)
		for (x=0; x<width[n1]; x++)
			image[n2][x][y] = image[n1][x][y];
}

void init_image(int n, unsigned char value)
{
	int x, y;

	for (y=0; y<height[n]; y++)
		for (x=0; x<width[n]; x++)
			image[n][x][y] = value;

}
