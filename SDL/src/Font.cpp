#include <iostream>
#include <assert.h>

#include "Font.hpp"
#include "Surface.hpp"
#include "Color.hpp"

#define TTF_DEFAULT_FONT_SIZE 10

namespace sdl {
    Font::Font(const std::string& filename, u8_t fontSize) {
        this->loadFromFile(filename, fontSize);
    }

    Font::~Font() {
        TTF_CloseFont(_ttf);
    }

    void Font::loadFromFile(const std::string& filename, u8_t fontSize) {
        _fontSize = fontSize == 0 ? TTF_DEFAULT_FONT_SIZE : fontSize;
        _ttf = TTF_OpenFont(filename.c_str(), _fontSize);
        if (!_ttf)
            std::cerr << TTF_GetError() << std::endl;
    }

    void Font::setStyle(Font::Style style) {
        if (_ttf)
            TTF_SetFontStyle(_ttf, static_cast<i32_t>(style));
        else
            std::cerr << "Font is null" << std::endl;
    }

    Font::Style Font::getStyle() const {
        if (_ttf)
            return static_cast<Style>(TTF_GetFontStyle(_ttf));

        std::cerr << "Font is null" << std::endl;

        return Style::Normal;
    }

    Surface Font::render(const std::string& text, const Color& fg, const Color* bg, Mode mode) const {
        assert(_ttf);

        SDL_Color a;
        SDL_Color b;

        SDL_Color* sdl_bg = TryCopyInto(bg, &b);

        SDL_Surface* srfc = nullptr;
        switch (mode) {
            case Mode::Solid:
                srfc = TTF_RenderUTF8_Solid(_ttf, text.c_str(), *fg.copyInto(&a));
                break;
            case Mode::Shaded:
                srfc = TTF_RenderUTF8_Shaded(_ttf, text.c_str(), *fg.copyInto(&a), sdl_bg ? *sdl_bg : b);
                break;
            case Mode::Blended:
                srfc = TTF_RenderUTF8_Blended(_ttf, text.c_str(), *fg.copyInto(&a));
                break;
        }

        if (!srfc)
            std::cerr << SDL_GetError() << std::endl;
        else if (srfc->format->BitsPerPixel < 24) {
            Surface temp(srfc);
            Surface result(srfc->w, srfc->h, 32);
            result.blit(temp);

            return result;
        }

        return Surface(srfc);
    }
}
