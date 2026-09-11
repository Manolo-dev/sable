#include <sable/div.h>
#include <sable/render.h>
#include <sable/shapes.h>
#include <sable/mat.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

static int g_screen_w = 2048;
static int g_screen_h = 2048;

static Div domino, bar, cc, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12;

#define VW(pct) ((int)(g_screen_w * (pct) / 100.0f))
#define VH(pct) ((int)(g_screen_h * (pct) / 100.0f))

static void build_scene(float g_angle) {
    domino = make_div(
        make_squircle(VW(22), VW(44), 6),
        STYLE_INIT(.color=0xFFD0E8ED, .left=VW(39), .top=VH(28), .transform=mat_mul(rotate(g_angle), scale(2, 2)), .anchor=CENTER)
    );

    bar = make_div(
        make_squircle(VW(20), VW(1) / 2, 8),
        STYLE_INIT(.color=0xFF000A00, .left=VW(1), .top=VW(21) + VW(1) / 2 + VW(1) / 4)
    );
    cc = make_div(
        make_circle(VW(1) / 2),
        STYLE_INIT(.color=0xFF00D7FF, .left=VW(10) + VW(1) / 2, .top=VW(21) + VW(1) / 2)
    );
    c1  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(4)));
    c2  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(9)));
    c3  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(14)));
    c4  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(4)));
    c5  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(9)));
    c6  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(14)));
    c7  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(26)));
    c8  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(31)));
    c9  = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(4),  .top=VW(36)));
    c10 = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(26)));
    c11 = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(31)));
    c12 = make_div(make_circle(VW(2)), STYLE_INIT(.color=0xFF000000, .left=VW(14), .top=VW(36)));

    div_add_child(&domino, &bar);
    div_add_child(&domino, &cc);
    div_add_child(&domino, &c1);
    div_add_child(&domino, &c2);
    div_add_child(&domino, &c3);
    div_add_child(&domino, &c4);
    div_add_child(&domino, &c5);
    div_add_child(&domino, &c6);
    div_add_child(&domino, &c7);
    div_add_child(&domino, &c8);
    div_add_child(&domino, &c9);
    div_add_child(&domino, &c10);
    div_add_child(&domino, &c11);
    div_add_child(&domino, &c12);
}

int main(void) {
    uint32_t *pixels = calloc((size_t)g_screen_w * g_screen_h, 4);
    Buffer buf = { .bits = pixels, .width = g_screen_w, .height = g_screen_h, .stride = g_screen_w };

    build_scene(PI/4);

    Div *divs[] = { &domino };
    render_frame(&buf, 1, divs, 0xFF202020);

    FILE *f = fopen("out.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", g_screen_w, g_screen_h);
    for (int i = 0; i < g_screen_w * g_screen_h; i++) {
        uint32_t p = pixels[i]; // format interne: r | g<<8 | b<<16 | a<<24
        fputc((p)      & 0xFF, f);
        fputc((p >> 8) & 0xFF, f);
        fputc((p >> 16)& 0xFF, f);
    }

    fclose(f);
    free(pixels);
    return 0;
}