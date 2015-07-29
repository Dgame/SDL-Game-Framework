#ifndef SDL_TTF_FONT_HPP
#define SDL_TTF_FONT_HPP

#include <string>
#include <SDL_ttf.h>

#include "types.hpp"

namespace sdl {
    class Surface;
    struct Color;

    class Font {
    public:
        enum Style {
            /*
            * Used to indicate regular, normal, plain rendering style.
            */
            Normal = TTF_STYLE_NORMAL,
            /*
            * Used to indicate bold rendering style.This is used in a bitmask along with other styles.
            */
            Bold = TTF_STYLE_BOLD,
            /*
            * Used to indicate italicized rendering style.This is used in a bitmask along with other styles.
            */
            Italic = TTF_STYLE_ITALIC,
            /*
            * Used to indicate underlined rendering style.This is used in a bitmask along with other styles.
            */
            Underline = TTF_STYLE_UNDERLINE,
            /*
            * Used to indicate strikethrough rendering style.This is used in a bitmask along with other styles.
            */
            StrikeThrough = TTF_STYLE_STRIKETHROUGH
        };

        enum Mode {
            Solid,
            Shaded,
            Blended
        };

        explicit Font(const std::string&, u8_t);
        Font(const Font&) = delete;
        virtual ~Font();

        void loadFromFile(const std::string&, u8_t);

        void setStyle(Style);
        Style getStyle() const;

        Surface render(const std::string&, const Color&, const Color* bg = nullptr, Mode mode = Mode::Solid) const;

    private:
        TTF_Font* _ttf;
        u8_t _fontSize;
    };
}

#endif
