#include "chalks/chalks.hpp"
#include <iostream>
using chalks::chalk;
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  cout << chalks::chalk("[红色]").red().bold().italic().underline()
       << "这里不要红颜色" << endl;
  cout << chalk("bold red").bold().red() << "\t"
       << chalk("dim green").dim().green() << "\t"
       << chalk("italic blue").italic().blue() << "\t"
       << chalk("underline yellow").underline().yellow() << "\t"
       << chalk("bold gray").bold().gray24() << "\t"
       << chalk("strike magenta").strike().magenta() << endl
       << chalk("color19").color256(196) << "\t"
       << chalk("color196").color256(19) << "\t"
       << chalk("color26").color256(26) << "\t" << chalk("color88").color256(88)
       << "\t" << chalk("color208").color256(208) << "\t"
       << chalk("color100").color256(100) << "\t"
       << chalk("color50").color256(50) << "\t"
       << chalk("color52").color6x6x6(1, 0, 0) << "\t" << endl
       << chalk("light green").color(chalks::colors::light_green) << "\t"
       << chalk("light blue").color(chalks::colors::light_blue) << "\t"
       << chalk("light yellow").color(chalks::colors::light_yellow) << "\t"
       << chalk("light gray").gray24(4) << "\t"
       << chalk("light magenta").color(chalks::colors::light_magenta) << endl
       << chalk("bg_red").bold().bg_red() << "\t"
       << chalk("bg_green").bold().bg_green() << "\t"
       << chalk("bg_yellow").bold().bg_yellow() << "\t"
       << chalk("bg_blue").bold().bg_blue() << "\t"
       << chalk("bg_magenta").bold().bg_magenta() << "\t"
       << chalk("bg_cyan").bold().bg_cyan() << "\t"
       << chalk("bg_white").bold().bg_white() << endl;
  return 0;
}
