#ifndef PSO_MISC_SMALLFONTDRAWING_H
#define PSO_MISC_SMALLFONTDRAWING_H

// Both entry points ignore incoming argument registers. The wrapper at
// 0x800FC3E0 calls the texture-list binder at 0x800FC400.
extern "C" {
void begin_small_font_draw();
void bind_small_font_texture_list();
}

#endif
