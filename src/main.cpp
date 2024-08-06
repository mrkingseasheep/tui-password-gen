#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp" // for operator|, Element, size, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/dom/node.hpp"     // for Render
#include "ftxui/screen/color.hpp" // for ftxui
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp> // for operator|, size, Element, text, hcenter, Decorator, Fit, WIDTH, hflow, window, EQUAL, GREATER_THAN, HEIGHT, bold, border, dim, LESS_THAN
#include <ftxui/screen/screen.hpp> // for Full, Screen
#include <string> // for allocator, char_traits, operator+, to_string, string

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();

    // what chars are allowed to be used
    Component validCharSelect = Container::Vertical({});
    std::string options[5] = {"Alphabit", "Capitals", "Numbers", "@-_",
                              "Other Symbols"};
    bool used[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < 5; ++i) {
        validCharSelect->Add(Checkbox(&options[i], &used[i]));
    }

    // what length the password is
    int passLenChar = 16;
    Component passLen = Container::Vertical(
        {Slider("Password Length:", &passLenChar, 1, 255, 1)});

    // finalized layout of the tui
    Component layout = Container::Vertical({
        validCharSelect,
        passLen,
    });

    // render the final layout
    auto component = Renderer(layout, [&] {
        return vbox({
                   validCharSelect->Render(),
                   separator(),
                   passLen->Render(),
               }) |
               border;
    });

    screen.Loop(component);
}
