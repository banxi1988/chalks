#pragma once
#include <array>
#include <cassert>
#include <sstream>
#include <string>

using std::stoi;
using std::string;

namespace chalks {

#define STR(x) #x
// SGR - Select Graphic Rendition 属于 CSI 序列
#define SGR(x) "\033[" STR(x) "m"

static const string rgb(int r, int g, int b, bool is_bg = false) {
  std::ostringstream buf;
  buf << "\033[" << (is_bg ? 48 : 38) << ";2;" << r << ';' << g << ';' << b
      << 'm';
  return buf.str();
}

static const string color_256(int index, bool is_bg = false) {
  assert(index >= 0 && index <= 255);
  std::ostringstream buf;
  buf << "\033[" << (is_bg ? 48 : 38) << ":5:" << index << 'm';
  return buf.str();
}

static const string color_6x6x6(int r, int g, int b) {
  assert(r >= 0 && r <= 5);
  assert(g >= 0 && g <= 5);
  assert(b >= 0 && b <= 5);
  return color_256(16 + 36 * r + 6 * g + b);
}

static const string bg_rgb(int r, int g, int b) {
  return rgb(r, g, b, true);
}

static const string hex_color(const string &hex, bool is_bg = false) {
  auto color = (hex[0] == '#') ? hex.substr(1) : hex;
  int r, g, b;
  if (color.size() == 3) {
    r = stoi("0x" + color.substr(0, 1), 0, 16);
    g = stoi("0x" + color.substr(1, 1), 0, 16);
    b = stoi("0x" + color.substr(2, 1), 0, 16);
    return rgb(r * 16 + r, g * 16 + g, b * 16 + b, is_bg);
  } else if (color.size() == 6) {
    r = stoi("0x" + color.substr(0, 2), 0, 16);
    g = stoi("0x" + color.substr(2, 2), 0, 16);
    b = stoi("0x" + color.substr(4, 2), 0, 16);
    return rgb(r, g, b, is_bg);
  }
  return "";
}

static inline const string bg_hex_color(const string &hex) {
  return hex_color(hex, true);
}

namespace Colors {
constexpr auto black = SGR(30);
constexpr auto red = SGR(31);
constexpr auto green = SGR(32);
constexpr auto yellow = SGR(33);
constexpr auto blue = SGR(34);
constexpr auto magenta = SGR(35);
constexpr auto cyan = SGR(36);
constexpr auto white = SGR(37);
constexpr auto light_black = SGR(90);
constexpr auto light_red = SGR(91);
constexpr auto light_green = SGR(92);
constexpr auto light_yellow = SGR(93);
constexpr auto light_blue = SGR(94);
constexpr auto light_magenta = SGR(95);
constexpr auto light_cyan = SGR(96);
constexpr auto light_white = SGR(97);

constexpr auto bg_black = SGR(40);
constexpr auto bg_red = SGR(41);
constexpr auto bg_green = SGR(42);
constexpr auto bg_yellow = SGR(43);
constexpr auto bg_blue = SGR(44);
constexpr auto bg_magenta = SGR(45);
constexpr auto bg_cyan = SGR(46);
constexpr auto bg_white = SGR(47);
constexpr auto bg_light_black = SGR(100);
constexpr auto bg_light_red = SGR(101);
constexpr auto bg_light_green = SGR(102);
constexpr auto bg_light_yellow = SGR(103);
constexpr auto bg_light_blue = SGR(104);
constexpr auto bg_light_magenta = SGR(105);
constexpr auto bg_light_cyan = SGR(106);
constexpr auto bg_light_white = SGR(107);
}; // namespace Colors

// 二维数组 [char *set,char *reset]
using _StylePair = std::array<const char *, 2>;

namespace StylePairs {
constexpr _StylePair bold{SGR(1), SGR(22)};
constexpr _StylePair dim{SGR(2), SGR(22)};
constexpr _StylePair italic{SGR(3), SGR(23)};
constexpr _StylePair underline{SGR(4), SGR(24)};
constexpr _StylePair inverse{SGR(7), SGR(27)};
constexpr _StylePair hidden{SGR(8), SGR(28)};
constexpr _StylePair strike{SGR(9), SGR(29)};
} // namespace StylePairs

class Style {
private:
  // 前景色
  string _color;
  // 背景色
  string _bg_color;
  bool _underline;
  bool _dim;
  bool _strong;
  bool _bold;
  bool _strike;
  bool _inverse;
  bool _italic;

public:
  const string color() const noexcept {
    return _color;
  }
  const string bgColor() const noexcept {
    return _bg_color;
  }

  Style &color(int r, int g, int b) {
    _color = rgb(r, g, b);
    return *this;
  }
  Style &clearColor() {
    _color = "";
    return *this;
  }
  Style &color(const string &hex) {
    _color = hex_color(hex);
    return *this;
  }

  Style &bgColor(int r, int g, int b) {
    _bg_color = bg_rgb(r, g, b);
    return *this;
  }

  Style &bgColor(const string &hex) {
    _bg_color = bg_hex_color(hex);
    return *this;
  }
  Style &clearBgColor(int r, int g, int b) {
    _bg_color = "";
    return *this;
  }

  Style &underline(bool flag = true) noexcept {
    _underline = flag;
    return *this;
  }
  Style &dim(bool flag = true) noexcept {
    _dim = flag;
    return *this;
  }
  Style &strong(bool flag = true) noexcept {
    _strong = flag;
    return *this;
  }
  Style &bold(bool flag = true) noexcept {
    _bold = flag;
    return *this;
  }
  Style &strike(bool flag = true) noexcept {
    _strike = flag;
    return *this;
  }
  Style &inverse(bool flag = true) noexcept {
    _inverse = flag;
    return *this;
  }
  Style &italic(bool flag = true) noexcept {
    _italic = flag;
    return *this;
  }
  // 24 阶灰色,1-24 从黑到白
  Style &gray24(int deep = 12) noexcept {
    assert(deep >= 1 && deep <= 24);
    _color = color_256(255 - deep);
    return *this;
  }
  // 24 阶灰色,1-24 从黑到白
  Style &bg_gray24(int deep = 12) noexcept {
    assert(deep >= 1 && deep <= 24);
    _bg_color = color_256(255 - deep);
    return *this;
  }
  //  216 色,16-231  6x6x6: 16+36xr+6xg+b
  Style &color256(int index) noexcept {
    _color = color_256(index);
    return *this;
  }
  //  256 色, 除基本色外加 16-231  6x6x6: 16+36xr+6xg+b
  Style &bg_color256(int index) noexcept {
    _bg_color = color_256(index);
    return *this;
  }
  //   6x6x6 立方: 16+36xr+6xg+b (0<=r,g,b<=5)
  Style &color6x6x6(int r, int g, int b) noexcept {
    _color = color_6x6x6(r, g, b);
    return *this;
  }
  //   6x6x6 立方: 16+36xr+6xg+b (0<=r,g,b<=5)
  Style &bg_color6x6x6(int r, int g, int b) noexcept {
    _bg_color = color_6x6x6(r, g, b);
    return *this;
  }

  Style &red(bool light = false) noexcept {
    _color = light ? Colors::light_red : Colors::red;
    return *this;
  }
  Style &bg_red(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_red : Colors::bg_red;
    return *this;
  }
  Style &green(bool light = false) noexcept {
    _color = light ? Colors::light_green : Colors::green;
    return *this;
  }
  Style &bg_green(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_green : Colors::bg_green;
    return *this;
  }
  Style &yellow(bool light = false) noexcept {
    _color = light ? Colors::light_yellow : Colors::yellow;
    return *this;
  }
  Style &bg_yellow(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_yellow : Colors::bg_yellow;
    return *this;
  }
  Style &blue(bool light = false) noexcept {
    _color = light ? Colors::light_blue : Colors::blue;
    return *this;
  }
  Style &bg_blue(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_blue : Colors::bg_blue;
    return *this;
  }
  Style &magenta(bool light = false) noexcept {
    _color = light ? Colors::light_magenta : Colors::magenta;
    return *this;
  }
  Style &bg_magenta(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_magenta : Colors::bg_magenta;
    return *this;
  }
  Style &cyan(bool light = false) noexcept {
    _color = light ? Colors::light_cyan : Colors::cyan;
    return *this;
  }
  Style &bg_cyan(bool light = false) noexcept {
    _bg_color = light ? Colors::light_cyan : Colors::bg_cyan;
    return *this;
  }
  Style &white(bool light = false) noexcept {
    _color = light ? Colors::light_white : Colors::white;
    return *this;
  }
  Style &bg_white(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_white : Colors::bg_white;
    return *this;
  }
  Style &black(bool light = false) noexcept {
    _color = light ? Colors::light_black : Colors::black;
    return *this;
  }
  Style &bg_black(bool light = false) noexcept {
    _bg_color = light ? Colors::bg_light_black : Colors::bg_black;
    return *this;
  }

  bool bold() const noexcept {
    return _bold;
  }
  bool strong() const noexcept {
    return _strong;
  }
  bool strike() const noexcept {
    return _strike;
  }
  bool inverse() const noexcept {
    return _inverse;
  }
  bool italic() const noexcept {
    return _italic;
  }
  bool dim() const noexcept {
    return _dim;
  }
  bool underline() const noexcept {
    return _underline;
  }

  /**
   * reset strs
   */
  static constexpr auto style_reset_all = SGR(0);
  static constexpr auto style_reset_fg = SGR(39);
  static constexpr auto style_reset_bg = SGR(49);
};

Style chalk_style() noexcept {
  Style s;
  return s;
}

const string chalk(const string &str, const Style &style) noexcept {
  string res = str;
  if (!style.color().empty()) {
    res = style.color() + res + Style::style_reset_fg;
  }
  if (!style.bgColor().empty()) {
    res = style.bgColor() + res + Style::style_reset_bg;
  }
  if (style.bold() || style.strong()) {
    auto style = StylePairs::bold;
    res = style[0] + res + style[1];
  }
  if (style.dim()) {
    auto style = StylePairs::dim;
    res = style[0] + res + style[1];
  }
  if (style.italic()) {
    auto style = StylePairs::italic;
    res = style[0] + res + style[1];
  }
  if (style.underline()) {
    auto style = StylePairs::underline;
    res = style[0] + res + style[1];
  }
  if (style.inverse()) {
    auto style = StylePairs::inverse;
    res = style[0] + res + style[1];
  }
  if (style.strike()) {
    auto style = StylePairs::strike;
    res = style[0] + res + style[1];
  }
  return res;
}

} // namespace chalks
