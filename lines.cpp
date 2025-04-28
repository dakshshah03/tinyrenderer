// Different implementations of line drawing, following the tinyrenderer tutorial:
// https://haqr.eu/tinyrenderer/bresenham/

// Barycentric coordinates
void line1(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    for(float t = 0; t < 1; t += 0.05) {
        int x = std::round(ax + t*(bx - ax));
        int y = std::round(ay + t*(by - ay));
        framebuffer.set(x, y, color);
    }
}

// Drawn in terms of t(x) = (x-ax)/(bx - ax)
// and draw y(t) using the above t(x)
void line2(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
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

    for(int x = ax; x <= bx; x += 1) {
        float t = (x - ax)/static_cast<float>(bx - ax);
        int y = std::round(ay + t*(by - ay));
        if(steep) {
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }
    }
}


// optimized version, which reduces the mathematical computations needed:
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