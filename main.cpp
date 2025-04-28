#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    // to handle if the line is steep, we take the transpose
    bool steep = std::abs(ax - bx) < std::abs(ay-by);
    if(steep) {
        std::swap(ax, by);
        std::swap(ay, bx);
    }

    // if bx < ax, then swap them to render from left to right
    if(bx < ax) {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    
    int y = ay;
    int ierror = 0;

    for(int x = ax; x <= bx; x += 1) {
        if(steep) {
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }

        ierror += 2 * std::abs(by-ay);
        // If the error is high enough,  
        y += (by > ay ? 1 : -1) * (ierror > bx - ax);
        ierror -= 2 * (bx - ax) * (ierror > bx - ax);
        
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    line(ax, ay, bx, by, framebuffer, blue);
    line(cx, cy, bx, by, framebuffer, green);
    line(cx, cy, ax, ay, framebuffer, yellow);
    line(ax, ay, cx, cy, framebuffer, red);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

