# tui-password-gen
Simple password generator on the terminal, made with ftxui and love :D

Oh FYI I wouldn't use this for any applications. It probably violates all of the security practices and then some more.

The relative lack of features I would like to say is because I wanted to keep it minimalistic. In reality it is me struggling to get the lamba functions to work. All in all, this was a good practice project for learning the ropes of the ever so helpful FTXUI, which allows the TUI aspect of the project.

## Important note

I'd like to appologize for each commit being relatively small changes. I'm still getting a hang of coding in C++ for non competitive stuff. Which means I basically have no clue how the majority of the language works.

## How to build

`git clone https://github.com/mrkingseasheep/tui-password-gen.git`
`cd tui-password-gen/build`
`cmake ..`
`./tui-password-gen`

Die from the uglyness.

## Future TODO
- [ ] Integration with `pass` on the Linux CLI
- [ ] Allow sentence-style passwords (e.g., bashful monkeys eating litchen)
- [ ] Allow the detection of weak passwords and alerting the user
