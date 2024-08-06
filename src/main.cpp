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
    std::string options[5] = {"Alphabit", "Capitals", "Numbers", "@-_",
                              "Other Symbols"};
    bool used[5] = {0, 0, 0, 0, 0};

    Component choice = Container::Vertical({});

    auto screen = ScreenInteractive::Fullscreen();
    for (int i = 0; i < 5; ++i) {
        choice->Add(Checkbox(&options[i], &used[i]));
    }

    auto left = Renderer([&] {
        return vbox({
            text("Options:") | bold,
            choice->Render(),
            separator(),
            text("Password Length:") | bold,

            separator(),
            text("Password Strength:") | bold,
            gauge(0.5),
        });
    });
    int leftSize = 30;

    auto right = Renderer([&] {
        return vbox({
            text("Password:") | bold,
        });
    });
    int rightSize = 50;

    /*Component title = Container::({});*/

    Component container = choice;
    container = ResizableSplitRight(right, container, &rightSize);
    container = ResizableSplitLeft(left, container, &leftSize);

    auto renderer = Renderer(container, [&] {
        return vbox({
                   text("Welcome to tui-password-gen V1"),
                   separator(),
                   left->Render(),
               }) |
               border;
    });
    screen.Loop(renderer);
}
