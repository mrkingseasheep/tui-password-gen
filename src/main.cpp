#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>

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
        /*{Slider("Password Length:", &passLenChar, 1, 255, 1)});*/
        {Slider("", &passLenChar, 1, 255, 1)});

    // regenerate password button
    std::string newPassLabel = "New Password!";
    auto newPassButton = Button(&newPassLabel, screen.ExitLoopClosure());

    // close tui button
    std::string closeButLabel = "Exit";
    Component exitButton = Button(&closeButLabel, screen.ExitLoopClosure());

    // finalized layout of the tui
    Component layout = Container::Vertical({
        validCharSelect,
        passLen,
        newPassButton,
        exitButton,
    });

    // render the final layout
    auto component = Renderer(layout, [&] {
        return hbox({
                   vbox({
                       /*separatorCharacter("Valid Char Types:"),*/
                       separator(),
                       validCharSelect->Render(),
                       separator(),
                       passLen->Render(),
                       separator(),
                       hbox({
                           newPassButton->Render(),
                           exitButton->Render(),
                       }) | center,
                       separatorDouble(),
                   }),
                   separator(),
                   vbox({
                       text("Hello world!"),
                   }),
               }) |
               border | flex;
    });

    screen.Loop(component);
}
