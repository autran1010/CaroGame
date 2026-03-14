#include "ui_setting.h"
#include "src/Model/config.h"
#include "src/Model/colors.h"
#include "src/View/ui_background.h"
#include "src/View/ui_panel.h"
#include "src/View/ui_fx.h"
#include "src/audio_manager.h"

#include <string>
#include <cstdio>
#include <algorithm>

namespace
{
    // ===== LAYOUT CHÍNH =====
    constexpr Rectangle SETTINGS_OUTER = { 420, 122, 760, 662 };
    constexpr Rectangle SETTINGS_INNER = { 430, 132, 740, 642 };
    constexpr Rectangle BACK_BUTTON = { 710, 800, 180, 62 };

    // Cột trái / phải
    constexpr float LABEL_X = 450.0f;
    constexpr float CONTROL_X = 770.0f;

    // Kích thước control
    constexpr float ARROW_W = 40.0f;
    constexpr float SLIDER_W = 200.0f;
    constexpr float VALUE_W = 82.0f;
    constexpr float TOGGLE_W = 220.0f;
    constexpr float CONTROL_H = 36.0f;
    constexpr float CONTROL_GAP = 8.0f;

    // Canh dòng
    constexpr float TITLE_Y = 58.0f;
    constexpr float ROW_GAP = 50.0f;

    enum DragSliderId
    {
        DRAG_NONE = -1,
        DRAG_NEON_GLOW = 0,
        DRAG_UI_BRIGHTNESS,
        DRAG_MUSIC_VOLUME,
        DRAG_SFX_VOLUME
    };

    static DragSliderId gActiveSlider = DRAG_NONE;

    enum SettingsTab
    {
        TAB_GRAPHICS = 0,
        TAB_AUDIO,
        TAB_GAME_UI
    };

    static SettingsTab gCurrentTab = TAB_GRAPHICS;

    constexpr Rectangle TAB_GRAPHICS_BTN = { 475, 175, 190, 44 };
    constexpr Rectangle TAB_AUDIO_BTN = { 705, 175, 190, 44 };
    constexpr Rectangle TAB_GAME_UI_BTN = { 935, 175, 190, 44 };

    struct SliderParts
    {
        Rectangle leftArrow;
        Rectangle track;
        Rectangle rightArrow;
        Rectangle valueBox;
        Rectangle knob;
        Rectangle trackInner;
    };

    std::string PercentText(float value)
    {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%d%%", static_cast<int>(value * 100.0f + 0.5f));
        return std::string(buffer);
    }

    std::string OnOffText(bool value)
    {
        return value ? "ON" : "OFF";
    }

    void StepFloat(float& value, float step)
    {
        value += step;
        value = std::clamp(value, 0.0f, 1.0f);
    }

    SliderParts MakeSliderParts(float y, float value)
    {
        SliderParts p{};
        p.leftArrow = { CONTROL_X, y - 4.0f, ARROW_W, CONTROL_H };
        p.track = { CONTROL_X + ARROW_W + CONTROL_GAP, y - 4.0f, SLIDER_W, CONTROL_H };
        p.rightArrow = { p.track.x + p.track.width + CONTROL_GAP, y - 4.0f, ARROW_W, CONTROL_H };
        p.valueBox = { p.rightArrow.x + p.rightArrow.width + CONTROL_GAP, y - 4.0f, VALUE_W, CONTROL_H };

        p.trackInner = {
            p.track.x + 12.0f,
            p.track.y + p.track.height * 0.5f - 3.0f,
            p.track.width - 24.0f,
            6.0f
        };

        float knobX = p.trackInner.x + p.trackInner.width * value;

        p.knob = {
            knobX - 6.0f,
            p.track.y + 7.0f,
            12.0f,
            p.track.height - 14.0f
        };

        return p;
    }

    Rectangle MakeToggleBox(float y)
    {
        return Rectangle{ CONTROL_X + ARROW_W + CONTROL_GAP, y - 4.0f, TOGGLE_W, CONTROL_H };
    }

    void DrawMiniBox(Rectangle rect, Color accent, bool hovered)
    {
        DrawGlowRect(rect, accent, hovered ? 5 : 3, 0.02f, 2.0f);
        DrawRectangleRounded(rect, 0.18f, 10, FadeColorEx(Color{ 8, 16, 30, 255 }, 0.96f));
        DrawCutCornerFrame(rect, 8.0f, 1.3f, accent, hovered ? 0.90f : 0.72f);

        Rectangle inner{ rect.x + 3.0f, rect.y + 3.0f, rect.width - 6.0f, rect.height - 6.0f };
        DrawRectangleRounded(inner, 0.16f, 10, FadeColorEx(Color{ 5, 10, 18, 255 }, 0.98f));
    }

    void DrawArrowBox(Font font, Rectangle rect, const char* text, Color accent, bool hovered)
    {
        DrawMiniBox(rect, accent, hovered);

        Vector2 s = MeasureTextEx(font, text, 18.0f, 1.0f);
        DrawTextEx(
            font,
            text,
            Vector2{
                rect.x + rect.width * 0.5f - s.x * 0.5f,
                rect.y + rect.height * 0.5f - s.y * 0.5f
            },
            18.0f,
            1.0f,
            COLOR_TEXT_MAIN
        );
    }

    void DrawPercentSlider(
        Font font,
        const MouseState& mouse,
        float y,
        float value,
        Color accent,
        bool active
    )
    {
        SliderParts p = MakeSliderParts(y, value);

        DrawArrowBox(font, p.leftArrow, "<", accent, IsMouseOverRect(mouse, p.leftArrow));
        DrawArrowBox(font, p.rightArrow, ">", accent, IsMouseOverRect(mouse, p.rightArrow));

        DrawMiniBox(p.track, accent, IsMouseOverRect(mouse, p.track) || active);

        DrawRectangleRounded(p.trackInner, 0.5f, 8, FadeColorEx(COLOR_TEXT_DIM, 0.22f));

        Rectangle fillRect = p.trackInner;
        fillRect.width = p.trackInner.width * value;
        DrawRectangleRounded(fillRect, 0.5f, 8, FadeColorEx(accent, 0.85f));

        DrawGlowRect(p.knob, accent, active ? 6 : 4, 0.3f, 1.4f);
        DrawRectangleRounded(p.knob, 0.4f, 8, FadeColorEx(COLOR_TEXT_MAIN, 0.95f));

        DrawMiniBox(p.valueBox, accent, IsMouseOverRect(mouse, p.valueBox));
        DrawTextEx(
            font,
            PercentText(value).c_str(),
            Vector2{ p.valueBox.x + 18.0f, p.valueBox.y + 9.0f },
            18.0f,
            1.0f,
            COLOR_TEXT_MAIN
        );
    }

    void DrawToggleControl(
        Font font,
        const MouseState& mouse,
        float y,
        bool value,
        Color accent
    )
    {
        Rectangle box = MakeToggleBox(y);
        DrawMiniBox(box, accent, IsMouseOverRect(mouse, box));

        DrawTextEx(
            font,
            OnOffText(value).c_str(),
            Vector2{ box.x + 18.0f, box.y + 9.0f },
            18.0f,
            1.0f,
            COLOR_TEXT_MAIN
        );
    }

    void DrawSliderRow(
        Font font,
        const MouseState& mouse,
        const char* label,
        float value,
        float y,
        bool active,
        Color accent = COLOR_NEON_CYAN
    )
    {
        DrawTextEx(
            font,
            label,
            Vector2{ LABEL_X, y },
            20.0f,
            1.0f,
            FadeColorEx(COLOR_TEXT_MAIN, 0.95f)
        );

        DrawPercentSlider(font, mouse, y, value, accent, active);
    }

    void DrawToggleRow(
        Font font,
        const MouseState& mouse,
        const char* label,
        bool value,
        float y,
        Color accent = COLOR_NEON_CYAN
    )
    {
        DrawTextEx(
            font,
            label,
            Vector2{ LABEL_X, y },
            20.0f,
            1.0f,
            FadeColorEx(COLOR_TEXT_MAIN, 0.95f)
        );

        DrawToggleControl(font, mouse, y, value, accent);
    }

    void DrawTabButton(Font font, const MouseState& mouse, Rectangle rect, const char* text, bool active)
    {
        bool hovered = IsMouseOverRect(mouse, rect);
        Color accent = active ? COLOR_NEON_CYAN : COLOR_NEON_BLUE;

        DrawGlowRect(rect, accent, active ? 7 : (hovered ? 5 : 3), 0.02f, 2.0f);
        DrawRectangleRounded(
            rect,
            0.18f,
            10,
            FadeColorEx(active ? Color{ 18, 40, 70, 255 } : Color{ 8, 16, 30, 255 }, 0.96f)
        );
        DrawCutCornerFrame(rect, 8.0f, 1.4f, accent, active ? 0.95f : (hovered ? 0.80f : 0.62f));

        Vector2 s = MeasureTextEx(font, text, 20.0f, 1.0f);
        DrawTextEx(
            font,
            text,
            Vector2{
                rect.x + rect.width * 0.5f - s.x * 0.5f,
                rect.y + rect.height * 0.5f - s.y * 0.5f
            },
            20.0f,
            1.0f,
            COLOR_TEXT_MAIN
        );
    }

    void UpdateTabButtons(const MouseState& mouse, AudioAssets& audio, const AppSettings& settings)
    {
        if (IsMouseClickedRect(mouse, TAB_GRAPHICS_BTN))
        {
            if (gCurrentTab != TAB_GRAPHICS)
                PlayMenuClick(audio, settings);

            gCurrentTab = TAB_GRAPHICS;
            gActiveSlider = DRAG_NONE;
        }
        else if (IsMouseClickedRect(mouse, TAB_AUDIO_BTN))
        {
            if (gCurrentTab != TAB_AUDIO)
                PlayMenuClick(audio, settings);

            gCurrentTab = TAB_AUDIO;
            gActiveSlider = DRAG_NONE;
        }
        else if (IsMouseClickedRect(mouse, TAB_GAME_UI_BTN))
        {
            if (gCurrentTab != TAB_GAME_UI)
                PlayMenuClick(audio, settings);

            gCurrentTab = TAB_GAME_UI;
            gActiveSlider = DRAG_NONE;
        }
    }

    void SetSliderValueFromMouse(float& value, const SliderParts& p, float mouseX)
    {
        float t = (mouseX - p.trackInner.x) / p.trackInner.width;
        value = std::clamp(t, 0.0f, 1.0f);
    }

    void HandleSliderControl(
        const MouseState& mouse,
        float y,
        float& value,
        DragSliderId id,
        AudioAssets& audio,
        const AppSettings& settings
    )
    {
        SliderParts p = MakeSliderParts(y, value);

        if (IsMouseClickedRect(mouse, p.leftArrow))
        {
            StepFloat(value, -0.01f);
            gActiveSlider = DRAG_NONE;
            PlayMenuClick(audio, settings);
            return;
        }

        if (IsMouseClickedRect(mouse, p.rightArrow))
        {
            StepFloat(value, 0.01f);
            gActiveSlider = DRAG_NONE;
            PlayMenuClick(audio, settings);
            return;
        }

        if (mouse.leftPressed && (IsMouseOverRect(mouse, p.knob) || IsMouseOverRect(mouse, p.track)))
        {
            gActiveSlider = id;
            SetSliderValueFromMouse(value, p, mouse.position.x);
            return;
        }

        if (gActiveSlider == id && mouse.leftDown)
        {
            SetSliderValueFromMouse(value, p, mouse.position.x);
            return;
        }
    }

    void HandleToggleControl(
        const MouseState& mouse,
        float y,
        bool& value,
        AudioAssets& audio,
        const AppSettings& settings
    )
    {
        Rectangle box = MakeToggleBox(y);

        if (IsMouseClickedRect(mouse, box))
        {
            value = !value;
            PlayMenuClick(audio, settings);
        }
    }
}

void UpdateSettingsUI(AppSettings& settings, const MouseState& mouse, ScreenState& currentScreen, AudioAssets& audio)
{
    if (!mouse.leftDown)
    {
        gActiveSlider = DRAG_NONE;
    }

    UpdateTabButtons(mouse, audio, settings);

    if (gCurrentTab == TAB_GRAPHICS)
    {
        HandleSliderControl(mouse, 285.0f, settings.neonGlow, DRAG_NEON_GLOW, audio, settings);
        HandleToggleControl(mouse, 340.0f, settings.gridAnimation, audio, settings);
        HandleToggleControl(mouse, 395.0f, settings.backgroundGrid, audio, settings);
        HandleSliderControl(mouse, 450.0f, settings.uiBrightness, DRAG_UI_BRIGHTNESS, audio, settings);
    }
    else if (gCurrentTab == TAB_AUDIO)
    {
        HandleSliderControl(mouse, 285.0f, settings.musicVolume, DRAG_MUSIC_VOLUME, audio, settings);
        HandleSliderControl(mouse, 340.0f, settings.sfxVolume, DRAG_SFX_VOLUME, audio, settings);
        HandleToggleControl(mouse, 395.0f, settings.menuClickSound, audio, settings);
    }
    else if (gCurrentTab == TAB_GAME_UI)
    {
        HandleToggleControl(mouse, 285.0f, settings.highlightLastMove, audio, settings);
        HandleToggleControl(mouse, 340.0f, settings.winLineAnimation, audio, settings);
        HandleToggleControl(mouse, 395.0f, settings.showCoordinates, audio, settings);
    }

    if (IsMouseClickedRect(mouse, BACK_BUTTON))
    {
        PlayMenuClick(audio, settings);
        currentScreen = SCREEN_MAIN_MENU;
    }
}

void DrawSettingsUI(Font fontTitle, Font fontSmall, const AppSettings& settings, const MouseState& mouse)
{
    DrawBackgroundScene();

    const char* title = "SETTINGS";
    Vector2 titleSize = MeasureTextEx(fontTitle, title, 52.0f, 2.0f);

    DrawTextEx(
        fontTitle,
        title,
        Vector2{ SCREEN_WIDTH * 0.5f - titleSize.x * 0.5f, TITLE_Y },
        52.0f,
        2.0f,
        COLOR_TEXT_MAIN
    );

    DrawNeonPanelFrame(SETTINGS_OUTER, SETTINGS_INNER, COLOR_NEON_BLUE, COLOR_PANEL_LINE);

    DrawTabButton(fontSmall, mouse, TAB_GRAPHICS_BTN, "GRAPHICS", gCurrentTab == TAB_GRAPHICS);
    DrawTabButton(fontSmall, mouse, TAB_AUDIO_BTN, "AUDIO", gCurrentTab == TAB_AUDIO);
    DrawTabButton(fontSmall, mouse, TAB_GAME_UI_BTN, "GAME UI", gCurrentTab == TAB_GAME_UI);

    if (gCurrentTab == TAB_GRAPHICS)
    {
        DrawSectionTitle(fontSmall, "GRAPHICS", Vector2{ LABEL_X, 240.0f });
        DrawSliderRow(fontSmall, mouse, "Neon Glow Intensity", settings.neonGlow, 285.0f, gActiveSlider == DRAG_NEON_GLOW);
        DrawToggleRow(fontSmall, mouse, "Grid Animation", settings.gridAnimation, 340.0f);
        DrawToggleRow(fontSmall, mouse, "Background Grid", settings.backgroundGrid, 395.0f);
        DrawSliderRow(fontSmall, mouse, "UI Brightness", settings.uiBrightness, 450.0f, gActiveSlider == DRAG_UI_BRIGHTNESS);
    }
    else if (gCurrentTab == TAB_AUDIO)
    {
        DrawSectionTitle(fontSmall, "AUDIO", Vector2{ LABEL_X, 240.0f });
        DrawSliderRow(fontSmall, mouse, "Music Volume", settings.musicVolume, 285.0f, gActiveSlider == DRAG_MUSIC_VOLUME);
        DrawSliderRow(fontSmall, mouse, "SFX Volume", settings.sfxVolume, 340.0f, gActiveSlider == DRAG_SFX_VOLUME);
        DrawToggleRow(fontSmall, mouse, "Menu Click Sound", settings.menuClickSound, 395.0f);
    }
    else if (gCurrentTab == TAB_GAME_UI)
    {
        DrawSectionTitle(fontSmall, "GAME UI", Vector2{ LABEL_X, 240.0f });
        DrawToggleRow(fontSmall, mouse, "Highlight Last Move", settings.highlightLastMove, 285.0f);
        DrawToggleRow(fontSmall, mouse, "Win Line Animation", settings.winLineAnimation, 340.0f);
        DrawToggleRow(fontSmall, mouse, "Show Coordinates", settings.showCoordinates, 395.0f);
    }

    bool backHover = IsMouseOverRect(mouse, BACK_BUTTON);

    DrawGlowRect(BACK_BUTTON, COLOR_NEON_PINK, backHover ? 7 : 5, 0.02f, 2.6f);
    DrawRectangleRounded(BACK_BUTTON, 0.18f, 10, FadeColorEx(Color{ 10, 18, 36, 255 }, 0.95f));
    DrawCutCornerFrame(BACK_BUTTON, 10.0f, 1.6f, COLOR_NEON_PINK, backHover ? 0.92f : 0.78f);

    Vector2 backSize = MeasureTextEx(fontTitle, "BACK", 26.0f, 1.2f);
    DrawTextEx(
        fontTitle,
        "BACK",
        Vector2{
            BACK_BUTTON.x + BACK_BUTTON.width * 0.5f - backSize.x * 0.5f,
            BACK_BUTTON.y + BACK_BUTTON.height * 0.5f - backSize.y * 0.5f
        },
        26.0f,
        1.2f,
        COLOR_TEXT_MAIN
    );
}