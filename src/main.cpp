#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include <cstdlib>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <string>
#include <vector>

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
        {Slider("", &passLenChar, 1, 128, 4)});

    // regenerate password button
    std::string newPassLabel = "New Password!";
    Event nullEvent;
    auto newPassButton = Button(&newPassLabel, [&] { ; });

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

    // NOTE THIS IS PROB NOT GOOD FOR GENERATING PASSWORDS
    auto genPassword = [&] {
        Elements password;
        std::vector<char> avaliableChars;
        std::vector<char> lowercaseAlpha = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        std::vector<char> uppercaseAlpha = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        std::vector<char> numbers = {'0', '1', '2', '3', '4',
                                     '5', '6', '7', '8', '9'};
        std::vector<char> commonSymbols = {'@', '.', ',', '-', '_'};
        std::vector<char> uncommonSymbols = {'(', ')', '}', '{', '[',
                                             ']', '!', '"', '~', '$'};

        // most inefficient code ever ik but I'm too lazy to think right now
        // also it would be hard cuz the symbols aren't even next to each other
        // although looking back I could've made this into a loop for the first
        // two, whopos #TODO
        int chars = 0;
        if (used[0]) {
            avaliableChars.insert(avaliableChars.end(), lowercaseAlpha.begin(),
                                  lowercaseAlpha.end());
            chars += 26;
        }
        if (used[1]) {
            avaliableChars.insert(avaliableChars.end(), uppercaseAlpha.begin(),
                                  uppercaseAlpha.end());
            chars += 26;
        }
        if (used[2]) {
            avaliableChars.insert(avaliableChars.end(), numbers.begin(),
                                  numbers.end());
            chars += 10;
        }
        if (used[3]) {
            avaliableChars.insert(avaliableChars.end(), commonSymbols.begin(),
                                  commonSymbols.end());
            chars += 5;
        }
        if (used[4]) {
            avaliableChars.insert(avaliableChars.end(), uncommonSymbols.begin(),
                                  uncommonSymbols.end());
            chars += 10;
        }

        std::string newPassword;
        for (int i = 0; i < passLenChar; ++i) {
            if (chars == 0) {
                password.push_back(text("Chose some allowed char types"));
                break;
            }
            int charUsed = std::rand() % chars;
            char nextCharInPass = avaliableChars[charUsed];
            newPassword.push_back(nextCharInPass);
        }
        password.push_back(text(newPassword));
        return password;
    };

    auto security = [&] {
        int charactersAvail = 0;
        if (used[0]) {
            charactersAvail += 26;
        }
        if (used[1]) {
            charactersAvail += 26;
        }
        if (used[2]) {
            charactersAvail += 10;
        }
        if (used[3]) {
            charactersAvail += 5;
        }
        if (used[4]) {
            charactersAvail += 10;
        }

        return charactersAvail * passLenChar / 19635;
    };

    auto introPara = Renderer([&] {
        std::string msg = "Terminals are cool. Linux pass is cool. But have "
                          "you ever needed a way to generate passwords in "
                          "the terminal? Fear not, because tui-password-gen "
                          "is here to help. With a range of configurable "
                          "options and character sets that you may or may "
                          "not use, it allows you to make your online "
                          "prescene much more secure! Who am I kidding. "
                          "You're probably better off using something like "
                          "keepassxc instead of this.";
        std::string bannerArt1 =
            "  __        .__                                   "
            "                           .___                   "
            "           ";
        std::string bannerArt2 =
            "_/  |_ __ __|__|         ___________    ______ "
            "________  _  _____________  __| _/          ____  "
            " ____   ____  ";
        std::string bannerArt3 =
            "\\   __\\  |  \\  |  ______ \\____ \\__  \\  /  "
            "___//  ___/\\ \\/ \\/ /  _ \\_  __ \\/ __ |  "
            "______  / ___\\_/ __ \\ /    \\ ";
        std::string bannerArt4 =
            " |  | |  |  /  | /_____/ |  |_> > __ \\_\\___ \\ "
            "\\___ \\  \\     (  <_> )  | \\/ /_/ | /_____/ / "
            "/_/  >  ___/|   |  \\";
        std::string bannerArt5 =
            " |__| |____/|__|         |   __(____  /____  "
            ">____  >  \\/\\_/ \\____/|__|  \\____ |         "
            "\\___  / \\___  >___|  /";
        std::string bannerArt6 =
            "                         |__|       \\/     \\/   "
            "  \\/                          \\/        /_____/ "
            "     \\/     \\/ ";
        return vbox({
            paragraphAlignLeft(bannerArt1),
            paragraphAlignLeft(bannerArt2),
            paragraphAlignLeft(bannerArt3),
            paragraphAlignLeft(bannerArt4),
            paragraphAlignLeft(bannerArt5),
            paragraphAlignLeft(bannerArt6),
            text(""),
            paragraphAlignLeft(msg),
        });
    });

    // render the final layout
    auto component = Renderer(layout, [&] {
        return vbox({
                   hbox({
                       introPara->Render(),
                   }),
                   separator(),
                   hbox({
                       vbox({
                           /*separatorCharacter("Valid Char Types:"),*/
                           /*separator(),*/
                           text("Valid Char Types:") | bold |
                               bgcolor(Color::Blue),
                           validCharSelect->Render(),
                           separator(),
                           text("Select Password Length:") | bold |
                               bgcolor(Color::Blue),
                           passLen->Render(),
                           separator(),
                           hbox({
                               newPassButton->Render(),
                               exitButton->Render(),
                           }) | center,
                       }),
                       separator(),
                       vbox({
                           hflow(genPassword()),
                           /*separator(),*/
                           /*gauge(security()),*/
                           /*hflow(security()),*/
                       }),
                   }) | flex,
               }) |
               border;
    });

    screen.Loop(component);
}
