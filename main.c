#include "actrwasm.h"
#include "actrui.h"

[[clang::export_name("actr_init")]]
void actr_init(int w, int h)
{
    actr_ui_init(w, h);
}

[[clang::export_name("actr_pointer_tap")]]
void actr_pointer_tap(int x, int y)
{
    struct ActrUIControl *tapped = actr_ui_tap(x, y);
}

[[clang::export_name("actr_resize")]]
void actr_resize(int w, int h)
{
    actr_ui_resize(w, h);
    actr_ui_invalidate();
}

[[clang::export_name("actr_pointer_down")]]
void actr_pointer_down(int x, int y)
{
}

[[clang::export_name("actr_pointer_up")]]
void actr_pointer_up(int x, int y)
{
}

[[clang::export_name("actr_pointer_move")]]
void actr_pointer_move(int x, int y)
{
    struct ActrUIControl *target = actr_ui_move(x, y);
}

double stage = 0;
[[clang::export_name("actr_step")]]
void actr_step(double delta)
{
    float segments = 2048;
    float length = actr_ui_state->canvas_size.w / segments;
    float half = actr_ui_state->canvas_size.h / 2.0;
    float step = 256; 
    
    actr_ui_invalidate();
    actr_ui_draw(delta);
    actr_canvas2d_stroke_style(255, 0, 255, 100);
    actr_canvas2d_begin_path();
    for (int i = 0; i <= segments; i++)
    {
        float value = length * i;
        float y = half + half * actr_cos(stage * i * 0.01) ;
        if (i == 0)
            actr_canvas2d_moveto(value, y);
        else
            actr_canvas2d_lineto(value, y);
    }
    actr_canvas2d_stroke();
    stage += delta;
}
