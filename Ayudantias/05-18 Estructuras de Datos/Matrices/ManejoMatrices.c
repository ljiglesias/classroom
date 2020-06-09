/* ================================================== *
 *                GENERAL INFORMATION                 *
 * ================================================== *

Autor: Mayron Barahona Ruiz
Basado en el trabajo de Jonathan Frech (2017)
Blog de Jonathan Frech: https://jonathanfrech.wordpress.com

 * ======================================= *
 *                  DEFINICIONES           *
 * ======================================= */

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef unsigned char byte;

//Struct que guarda valores RGB del pixel
typedef struct rgb
{
    byte R;
    byte G;
    byte B;
} RGB;

//Struct que guarda info de imagen y matrix pixeles
typedef struct image
{
    int width;
    int height;
    RGB **px;
} image;


/* ======================= *
 *  DECLARACIONES          * 
 * ======================= */

/* I) Imagen            */
image *newimage(int, int);
void freeimage(image *);
char ascii(byte grayScale);

/* II) Leer */
image *readbmp(char[]);

/* ====== *
 *  MAIN  *
 * ====== */
int main()
{
    // leemos la imagen y la guardamos en la estructura
    image *img = readbmp("img.bmp");

    //creamos un puntero a un archivo
    FILE *archivo;
    archivo = fopen("ascii.txt", "w");

    //procesamos la info de la matrix de la imagen
    for (int row = 0; row < (img -> height); row++)
	{
		for (int col = 0; col < (img -> width); col++)
		{
			byte gray =  (byte)(0.2989*img ->px[row][col].R + 
                                0.5870*img ->px[row][col].G + 
                                0.1140*img ->px[row][col].B);
			img ->px[row][col].R = gray;
            img ->px[row][col].G = gray;
            img ->px[row][col].B = gray;
            
            char c = ascii(gray);

            //guardamos en el archivo el caracter
            fwrite(&c, 1, 1, archivo);
		}
        //espacio por el cambio de fila
        char c = '\n';
        fwrite(&c, 1, 1, archivo);
	}
    //cerramos el archivo
    fclose(archivo);

    //liberamos la memoria que guardaba la estructura de la imagen
    freeimage(img);
}

/* =========================== *
 *  I) IMAGEN *
 * =========================== */

// Retorna un struct image, inicializado 
// en memoria y con sus valores de pixeles en 0
image *newimage(int width, int height)
{   
    //asigna memoria
    image *img = malloc(sizeof(image));
    img->width = width;
    img->height = height;  
    //asigna memoria para un array de arrays de structs e inicializa en 0
    img->px = calloc(height, sizeof(RGB *));

    for (int row = 0; row < height; row++)
    {
        //asigna memoria para un array de structs e inicializa en 0
        img->px[row] = calloc(width, sizeof(RGB));
        for (int col = 0; col < width; col++)
        {
            img->px[row][col].R = 0;
            img->px[row][col].G = 0;
            img->px[row][col].B = 0;
        }
    } 
    return img; //retorna el puntero
}

// libera la memoria asignada
void freeimage(image *img)
{
    for (int row = 0; row < img->height; row++)
    {
        free(img -> px[row]);
    }
    free(img->px);
    free(img);
}

//convierte de nivel de gris a letra
char ascii(byte grayScale)
{
    if (grayScale < 25) return '@';
    if (grayScale < 50) return '%';
    if (grayScale < 75) return '#';
    if (grayScale < 100) return '*';
    if (grayScale < 125) return '+';
    if (grayScale < 150) return '=';
    if (grayScale < 175) return '-';
    if (grayScale < 200) return ':';
    if (grayScale < 225) return '.';
    return ' ';
}

/* ============================ *
 *  II) LEER BMP                *
 * ============================ */

// read a bitmap file
image *readbmp(char fn[])
{
    FILE *f = fopen(fn, "r");
    fseek(f, 0, SEEK_END);
    int s = ftell(f);
    byte *data = malloc(s);
    fseek(f, 0, SEEK_SET);
    fread(data, 1, s, f);
    fclose(f);

    int k = 54;                                                               // tamano header
                                                                              
    int w = (data[21] << 24) | (data[20] << 16) | (data[19] << 8) | data[18]; // Ancho
    int h = (data[25] << 24) | (data[24] << 16) | (data[23] << 8) | data[22]; // Largo

    image *img = newimage(w, h);
    int i = 0; 
    int pad = (4 - (3 * w) % 4) * ((3 * w) % 4 != 0); //padding: fila debe ser multiplo de 4
    for (int y = h - 1; y >= 0; y--)
    {
        for (int x = 0; x < w; x++)
        {   
            //lee pixeles de la imagen
            img->px[y][x].R = data[k + i];
            img->px[y][x].G = data[k + i + 1];
            img->px[y][x].B = data[k + i + 2];
            i += 3;
        }
        i += pad;
    }
    free(data); //libera memoria
    return img; //retorna un puntero de imagen
}

/* FIN */