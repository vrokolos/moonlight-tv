#include "lvgl/font/symbols_material_icon.h"
#include "settings.controller.h"

#include "util/i18n.h"

lv_obj_t *settings_win_create(struct lv_obj_controller_t *self, lv_obj_t *parent) {
    settings_controller_t *controller = (settings_controller_t *) self;
    /*Create a window*/
    lv_obj_t *win = lv_win_create(parent, lv_dpx(50));

    lv_obj_t *header = lv_win_get_header(win);
    lv_obj_clear_flag(header, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_ver(header, lv_dpx(10), 0);
    lv_obj_set_style_pad_hor(header, lv_dpx(20), 0);

    lv_obj_t *icon = lv_label_create(header);
    lv_obj_set_size(icon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_get_style_text_align(icon, LV_TEXT_ALIGN_CENTER);
    lv_obj_set_style_text_font(icon, LV_ICON_FONT_DEFAULT, 0);
    lv_label_set_text_static(icon, MAT_SYMBOL_SETTINGS);

    lv_obj_t *title = lv_win_add_title(win, locstr("Settings"));
    lv_obj_set_style_text_font(title, lv_theme_get_font_large(win), 0);

    lv_obj_t *close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, lv_dpx(25));
    lv_obj_add_flag(close_btn, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_style_size(close_btn, lv_dpx(25), 0);
    lv_obj_set_style_radius(close_btn, LV_RADIUS_CIRCLE, 0);
    lv_group_remove_obj(close_btn);
    controller->close_btn = close_btn;

    lv_obj_t *content = lv_win_get_content(win);
    lv_obj_set_style_pad_ver(content, 0, 0);
    lv_obj_set_style_bg_color(content, lv_color_lighten(lv_color_black(), 30), 0);
    if (controller->pending_mini) {
        lv_obj_set_style_pad_hor(content, 0, 0);
        controller->tabview = lv_tabview_create(content, LV_DIR_BOTTOM, LV_DPX(60));
    } else {
        static const lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};
        static const lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
        lv_obj_set_grid_dsc_array(content, col_dsc, row_dsc);
        lv_obj_t *nav = lv_list_create(content);
        lv_obj_set_style_clip_corner(nav, false, 0);
        lv_obj_set_style_radius(nav, 0, 0);
        lv_obj_set_style_border_width(nav, 0, 0);
        controller->nav = nav;
        lv_obj_set_grid_cell(nav, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

        lv_obj_t *detail = lv_obj_create(content);
        lv_obj_set_style_clip_corner(detail, false, 0);
        lv_obj_set_style_radius(detail, 0, 0);
        lv_obj_set_style_border_width(detail, 0, 0);
        lv_obj_set_grid_cell(detail, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        controller->detail = detail;
    }
    controller->mini = controller->pending_mini;

    return win;
}