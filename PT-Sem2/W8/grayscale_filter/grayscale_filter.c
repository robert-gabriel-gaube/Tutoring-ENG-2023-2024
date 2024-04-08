#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BMP_HEADER_SIZE 54
#define WIDTH_POSITION 18
#define HEIGHT_POSITION 22

#define DEBUG

#ifdef DEBUG
    #define PRINT_DEBUG(type, format, ...) printf(type " " format, __VA_ARGS__)
#else 
    #define PRINT_DEBUG(type, format, ...)
#endif

typedef uint8_t byte;

typedef struct {
    byte red, green, blue;
}PIXEL;

typedef struct {
    uint32_t width;
    uint32_t height;
    PIXEL *pixels;  // size of width * height
}BITMAP;

void throwError(const char *msg) {
    perror(msg);
    exit(1);
}

void *safeAlloc(size_t byteCount) {
    void *ptr = malloc(byteCount);
    if(ptr == NULL) {
        throwError("malloc failed");
    }
    return ptr;
}

void moveCursor(FILE *file, unsigned int offset) {
    if(fseek(file, offset, SEEK_SET) == -1) {
        throwError("fseek failed");
    }
}

// Read 4 bytes from position in bitmap_file
uint32_t getBlockAtPosition(FILE *bitmap_file, unsigned int position) {
    uint32_t buffer;
    moveCursor(bitmap_file, position);

    if(fread(&buffer, 4, 1, bitmap_file) != 1) {
        throwError("fread failed");
    }
    return buffer;
}

PIXEL readPixel(FILE *bitmap_file) {
    PIXEL pixel;
    if(fread(&pixel, 3, 1, bitmap_file) != 1) {
        throwError("fread failed");
    }
    return pixel;
}

BITMAP readBitmap(FILE *bitmap_file) {
    BITMAP bitmap;

    // Read width and height
    bitmap.height = getBlockAtPosition(bitmap_file, HEIGHT_POSITION);
    bitmap.width = getBlockAtPosition(bitmap_file, WIDTH_POSITION);

    PRINT_DEBUG("[INFO]", "Width: %u, Height: %u\n", bitmap.width, bitmap.height);

    // Allocate space for pixels
    bitmap.pixels = safeAlloc(bitmap.width * bitmap.height * sizeof(PIXEL));

    // Read pixels
    moveCursor(bitmap_file, BMP_HEADER_SIZE);
    for(int i = 0; i < bitmap.width * bitmap.height; i++) {
        bitmap.pixels[i] = readPixel(bitmap_file);
    }

    return bitmap;
}   

BITMAP applyGrayscaleFilter(BITMAP bitmap) {
    for(int i = 0; i < bitmap.width * bitmap.height; i++) {
        byte gray = 0.299 * bitmap.pixels[i].red + 0.587 * bitmap.pixels[i].green + 0.114 * bitmap.pixels[i].blue;
        bitmap.pixels[i].red = gray;
        bitmap.pixels[i].green = gray;
        bitmap.pixels[i].blue = gray;
    }
    return bitmap;
}

void rewriteBitmap(FILE* bitmap_file, BITMAP bitmap) {
    // Write pixels
    moveCursor(bitmap_file, BMP_HEADER_SIZE);
    
    for(int i = 0; i < bitmap.width * bitmap.height; i++) {
        fwrite(&bitmap.pixels[i], 3, 1, bitmap_file);
    }
}

int main() {
    FILE *bitmap_file = fopen("imagine_2.bmp", "r+b");
    if(bitmap_file == NULL) {
        throwError("fopen failed");
    }

    BITMAP bitmap = readBitmap(bitmap_file);
    bitmap = applyGrayscaleFilter(bitmap);
    rewriteBitmap(bitmap_file, bitmap);

    fclose(bitmap_file);
    return 0;
}