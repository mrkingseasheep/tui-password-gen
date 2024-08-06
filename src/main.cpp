#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp" // for operator|, Element, size, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/dom/node.hpp"     // for Render
#include "ftxui/screen/color.hpp" // for ftxui
#include <algorithm>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp> // for operator|, size, Element, text, hcenter, Decorator, Fit, WIDTH, hflow, window, EQUAL, GREATER_THAN, HEIGHT, bold, border, dim, LESS_THAN
#include <ftxui/screen/screen.hpp> // for Full, Screen
#include <iostream>
#include <stdio.h> // for getchar
#include <string>  // for allocator, char_traits, operator+, to_string, string
#include <vector>

int main() {
    using namespace ftxui;
    std::string options[5] = {"Alphabit", "Capitals", "Numbers", "@-_",
                              "Other Symbols"};
    bool used[5] = {0, 0, 0, 0, 0};

    Component container = Container::Vertical({});

    auto screen = ScreenInteractive::FitComponent();
    for (int i = 0; i < 5; ++i) {
        container->Add(Checkbox(&options[i], &used[i]));
    }

    screen.Loop(container);
}
