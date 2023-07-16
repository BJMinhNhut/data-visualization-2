//
// Created by MINH NHUT on 6/8/2023.
//

#ifndef NATUREOFCODE_RESOURCEIDENTIFIERS_HPP
#define NATUREOFCODE_RESOURCEIDENTIFIERS_HPP

namespace sf {
    class Texture;

    class Font;
}  // namespace sf

namespace Textures {
    enum ID {
        Background,
        Title,

        CheckBoxNormal,
        CheckBoxSelected,
        CheckBoxActivated,

        HomeNormal,
        HomeSelected,
        BackNormal,
        BackSelected,
        TitleBar,

        CommandNormal,
        CommandSelected,
        CommandActivated,

        PlayNormal,
        PlaySelected,
        PauseNormal,
        PauseSelected,
        ReplayNormal,
        ReplaySelected,

        ArrowDownNormal,
        ArrowDownSelected,
        ArrowNormal,
        ArrowSelected,
        DoubleArrowNormal,
        DoubleArrowSelected,

        InputNormal,
        InputSelected,

        SmallButtonNormal,
        SmallButtonSelected,
        BigButtonNormal,
        BigButtonSelected,

        MenuHashNormal,
        MenuHashSelected,
        MenuAVLNormal,
        MenuAVLSelected,
//        Menu234Normal,
//        Menu234Selected,
//        MenuHeapNormal,
//        MenuHeapSelected,
//        MenuTrieNormal,
//        MenuTrieSelected,
//        MenuGraphNormal,
//        MenuGraphSelected,

        NumTextures,
    };
}

namespace Fonts {
    enum ID {
        Main,
        Bold,
        Mono,
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif  //NATUREOFCODE_RESOURCEIDENTIFIERS_HPP
