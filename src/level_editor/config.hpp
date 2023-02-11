#ifndef INCLUDE_LE_CONFIG_HPP
#define INCLUDE_LE_CONFIG_HPP


namespace level_editor
{
    /* UI textures */
    const auto BRUSH_MENU_TEXTURE
        = "assets/menu/brushes_menu.png";

    const auto TOOLBAR_TEXTURE
        = "assets/menu/level_edit_menu.png";


    /* Resizing */
    const bool CONFIRM_DATA_LOSS = false;
    const int resize_delta_limit = 32;

    /* Moving */
    const float shift_speedup_multiplier = 2.5;
}

#endif // INCLUDE_LE_CONFIG_HPP
