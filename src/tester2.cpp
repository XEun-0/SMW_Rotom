/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd-lvgl/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft-lvgl/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

/*  Install the "lvgl" library version 9.2 by kisvegabor to interface with the TFT Display - https://lvgl.io/
    *** IMPORTANT: lv_conf.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE lv_conf.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <lvgl.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen - Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

// Touchscreen pins
#define XPT2046_IRQ 36  // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 39 // T_OUT
#define XPT2046_CLK 25  // T_CLK
#define XPT2046_CS 33   // T_CS

#define LV_CONF_INCLUDE_SIMPLE

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char *buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

static lv_obj_t *touch_dot;

void touch_debug_init(void)
{
    touch_dot = lv_obj_create(lv_scr_act());
    lv_obj_set_size(touch_dot, 10, 10);
    lv_obj_set_style_radius(touch_dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(touch_dot, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_border_width(touch_dot, 0, 0);
    lv_obj_add_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
}

// Global for live touch feedback
// lv_obj_t *touch_indicator = NULL;
// lv_obj_t *touch_label = NULL;

// Actual touchscreen bounds from your hardware
#define TOUCH_MIN_X 335
#define TOUCH_MAX_X 3800
#define TOUCH_MIN_Y 440
#define TOUCH_MAX_Y 3570

void touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
        TS_Point p = touchscreen.getPoint();
        
        Serial.printf("Raw: x=%d, y=%d\n", p.x, p.y);
        
        // Test all 4 rotations with CORRECT bounds
        int x0 = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, SCREEN_WIDTH);                                      
        int y0 = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, SCREEN_HEIGHT);
        
        int x1 = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, SCREEN_WIDTH);
        int y1 = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, SCREEN_HEIGHT, 0);
        
        // Real
        int x2 = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, SCREEN_WIDTH - 1);
        int y2 = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, SCREEN_HEIGHT - 1);


        
        int x3 = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, SCREEN_WIDTH, 0);
        int y3 = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, SCREEN_HEIGHT);
        
        Serial.printf("R0: x=%3d y=%3d | R1: x=%3d y=%3d | R2: x=%3d y=%3d | R3: x=%3d y=%3d\n",
                      x0, y0, x1, y1, x2, y2, x3, y3);
        
        // Adjust raw touchscreen coordinates to display
        // int xMapped = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, SCREEN_WIDTH);
        // int yMapped = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, SCREEN_HEIGHT);

        // For display rotation 180°
        // Apply 180° display rotation correction
        x = (SCREEN_WIDTH  - 1) - x2;
        y = (SCREEN_HEIGHT - 1) - y2;
        z = p.z;

        x = LV_CLAMP(0, x, SCREEN_WIDTH  - 1);
        y = LV_CLAMP(0, y, SCREEN_HEIGHT - 1);

        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = x;
        data->point.y = y;

        lv_obj_clear_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(touch_dot, x - 5, y - 5);
        
        Serial.printf("Using: x=%d, y=%d\n\n", x, y);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
        lv_obj_add_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
    }
}

int btn1_count = 0;
// Callback that is triggered when btn1 is clicked
static void event_handler_btn1(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        btn1_count++;
        LV_LOG_USER("Button clicked %d", (int)btn1_count);
    }
}

// Callback that is triggered when btn2 is clicked/toggled
static void event_handler_btn2(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_UNUSED(obj);
        LV_LOG_USER("Toggled %s", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "on" : "off");
    }
}

static lv_obj_t *slider_label;
// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
static void slider_event_callback(lv_event_t *e)
{
    lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
}

void lv_create_main_gui(void)
{
    // Create a text label aligned center on top ("Hello, world!")
    lv_obj_t *text_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP); // Breaks the long lines
    lv_label_set_text(text_label, "Hello, world!");
    lv_obj_set_width(text_label, 150); // Set smaller width to make the lines wrap
    lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);

    lv_obj_t *btn_label;
    // Create a Button (btn1)
    lv_obj_t *btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_set_size(btn1, 10, 30);

    btn_label = lv_label_create(btn1);
    lv_label_set_text(btn_label, "Button");
    lv_obj_center(btn_label);

    // Create a Toggle button (btn2)
    lv_obj_t *btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 10);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    btn_label = lv_label_create(btn2);
    lv_label_set_text(btn_label, "Toggle");
    lv_obj_center(btn_label);

    // Create a slider aligned in the center bottom of the TFT display
    lv_obj_t *slider = lv_slider_create(lv_screen_active());
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_range(slider, 0, 100);
    lv_obj_set_style_anim_duration(slider, 2000, 0);

    // Create a label below the slider to display the current slider value
    slider_label = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label, "0%");
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
#define TRI_SIZE 35

void create_border()
{
    lv_obj_t *screen = lv_scr_act();
    
    // Create 2px red border around entire screen
    lv_obj_t *border = lv_obj_create(screen);
    lv_obj_set_size(border, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_pos(border, 0, 0);
    lv_obj_set_style_border_width(border, 2, 0);
    lv_obj_set_style_border_color(border, lv_color_hex(0xFF0000), 0); // Red
    lv_obj_set_style_bg_opa(border, LV_OPA_TRANSP, 0); // Transparent background
    lv_obj_clear_flag(border, LV_OBJ_FLAG_SCROLLABLE);
    
    // Add corner labels
    lv_obj_t *tl = lv_label_create(screen);
    lv_label_set_text(tl, "TL");
    lv_obj_align(tl, LV_ALIGN_TOP_LEFT, 5, 5);
    
    lv_obj_t *tr = lv_label_create(screen);
    lv_label_set_text(tr, "TR");
    lv_obj_align(tr, LV_ALIGN_TOP_RIGHT, -5, 5);
    
    lv_obj_t *bl = lv_label_create(screen);
    lv_label_set_text(bl, "BL");
    lv_obj_align(bl, LV_ALIGN_BOTTOM_LEFT, 5, -5);
    
    lv_obj_t *br = lv_label_create(screen);
    lv_label_set_text(br, "BR");
    lv_obj_align(br, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
    
    // Center text
    lv_obj_t *center = lv_label_create(screen);
    lv_label_set_text(center, "240x320\nTouch to test");
    lv_obj_set_style_text_align(center, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(center);
}


// void lv_create_debug_gui(void)
// {
//     lv_obj_t *screen = lv_scr_act();
    
//     // Large corner labels to see orientation
//     lv_obj_t *tl = lv_label_create(screen);
//     lv_label_set_text(tl, "TL\n(0,0)");
//     lv_obj_set_style_text_font(tl, &lv_font_montserrat_20, 0);
//     lv_obj_align(tl, LV_ALIGN_TOP_LEFT, 5, 5);
    
//     lv_obj_t *tr = lv_label_create(screen);
//     lv_label_set_text(tr, "TR\n(240,0)");
//     lv_obj_set_style_text_font(tr, &lv_font_montserrat_20, 0);
//     lv_obj_align(tr, LV_ALIGN_TOP_RIGHT, -5, 5);
    
//     lv_obj_t *bl = lv_label_create(screen);
//     lv_label_set_text(bl, "BL\n(0,320)");
//     lv_obj_set_style_text_font(bl, &lv_font_montserrat_20, 0);
//     lv_obj_align(bl, LV_ALIGN_BOTTOM_LEFT, 5, -5);
    
//     lv_obj_t *br = lv_label_create(screen);
//     lv_label_set_text(br, "BR\n(240,320)");
//     lv_obj_set_style_text_font(br, &lv_font_montserrat_20, 0);
//     lv_obj_align(br, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
    
//     // Center crosshair
//     lv_obj_t *center = lv_label_create(screen);
//     lv_label_set_text(center, "+\nCENTER\n(120,160)");
//     lv_obj_set_style_text_font(center, &lv_font_montserrat_20, 0);
//     lv_obj_set_style_text_align(center, LV_TEXT_ALIGN_CENTER, 0);
//     lv_obj_center(center);
    
//     // Show current display settings
//     lv_obj_t *info = lv_label_create(screen);
//     lv_label_set_text_fmt(info, "Display: %dx%d", SCREEN_WIDTH, SCREEN_HEIGHT);
//     lv_obj_align(info, LV_ALIGN_TOP_MID, 0, 40);
// }

// void lv_create_corner_triangles() {
//     lv_obj_t *screen = lv_scr_act();

//     // Top-left
//     lv_obj_t *tl = lv_obj_create(screen);
//     lv_obj_set_size(tl, TRI_SIZE, TRI_SIZE);
//     lv_obj_set_style_bg_color(tl, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_obj_align(tl, LV_ALIGN_TOP_LEFT, 0, 0);
//     lv_obj_clear_flag(tl, LV_OBJ_FLAG_SCROLLABLE);

//     lv_obj_t *label_tl = lv_label_create(tl);
//     lv_label_set_text(label_tl, "(TL)");
//     lv_obj_center(label_tl);

//     // Top-right
//     lv_obj_t *tr = lv_obj_create(screen);
//     lv_obj_set_size(tr, TRI_SIZE, TRI_SIZE);
//     lv_obj_set_style_bg_color(tr, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_obj_align(tr, LV_ALIGN_TOP_RIGHT, 0, 0);
//     lv_obj_clear_flag(tr, LV_OBJ_FLAG_SCROLLABLE);

//     lv_obj_t *label_tr = lv_label_create(tr);
//     lv_label_set_text(label_tr, "(TR)");
//     lv_obj_center(label_tr);

//     // Bottom-left
//     lv_obj_t *bl = lv_obj_create(screen);
//     lv_obj_set_size(bl, TRI_SIZE, TRI_SIZE);
//     lv_obj_set_style_bg_color(bl, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_obj_align(bl, LV_ALIGN_BOTTOM_LEFT, 0, 0);
//     lv_obj_clear_flag(bl, LV_OBJ_FLAG_SCROLLABLE);

//     lv_obj_t *label_bl = lv_label_create(bl);
//     lv_label_set_text(label_bl, "(BL)");
//     lv_obj_center(label_bl);

//     // Bottom-right
//     lv_obj_t *br = lv_obj_create(screen);
//     lv_obj_set_size(br, TRI_SIZE, TRI_SIZE);
//     lv_obj_set_style_bg_color(br, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_obj_align(br, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
//     lv_obj_clear_flag(br, LV_OBJ_FLAG_SCROLLABLE);

//     lv_obj_t *label_br = lv_label_create(br);
//     lv_label_set_text(label_br, "(BR)");
//     lv_obj_center(label_br);
// }

// void setup()
// {
//     String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
//     Serial.begin(115200);
//     Serial.println(LVGL_Arduino);

//     // Start LVGL
//     lv_init();
//     // Register print function for debugging
//     lv_log_register_print_cb(log_print);

//     // Start the SPI for the touchscreen and init the touchscreen
//     touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
//     touchscreen.begin(touchscreenSPI);
//     // Set the Touchscreen rotation in landscape mode
//     // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 0: touchscreen.setRotation(0);
//     touchscreen.setRotation(2);

//     // Create a display object
//     lv_display_t *disp;
//     // Initialize the TFT display using the TFT_eSPI library
//     disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
//     lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);

//     // Initialize an LVGL input device object (Touchscreen)
//     lv_indev_t *indev = lv_indev_create();
//     lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
//     // Set the callback function to read Touchscreen input
//     lv_indev_set_read_cb(indev, touchscreen_read);

//     // Function to draw the GUI (text, buttons and sliders)
//     lv_create_main_gui();
//     lv_create_corner_triangles();
// }

void setup()
{
    Serial.begin(115200);
    Serial.println("\n=== Touchscreen Calibration Debug ===");
    
    lv_init();
    lv_log_register_print_cb(log_print);

    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // DO NOT rotate touch at all
    // touchscreen.setRotation(...);   // ← REMOVE

    // Setup display screen
    // typedef enum {
    //     LV_DISPLAY_ROTATION_0 = 0,
    //     LV_DISPLAY_ROTATION_90,
    //     LV_DISPLAY_ROTATION_180,
    //     LV_DISPLAY_ROTATION_270
    // } lv_display_rotation_t;
    lv_display_t *disp;
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);  // Rotation 2 = 180°

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchscreen_read);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);


    // lv_create_debug_gui();  // Use debug GUI instead of main GUI
    lv_create_main_gui();
    // create_border();
    touch_debug_init();
}

void loop()
{
    lv_task_handler(); // let the GUI do its work
    lv_tick_inc(5);    // tell LVGL how much time has passed
    delay(5);          // let this time pass
}