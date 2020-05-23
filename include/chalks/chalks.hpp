#pragma once
#include <array>
#include <cassert>
#include <ostream>
#include <sstream>
#include <string>

namespace chalks {
using std::stoi;
using std::string;

#define STR(x) #x
// SGR - Select Graphic Rendition 属于 CSI 序列
#define SGR(x) "\033[" STR(x) "m"

namespace colors {
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

const string rgb(int r, int g, int b, bool is_bg = false) {
  std::ostringstream buf;
  buf << "\033[" << (is_bg ? 48 : 38) << ";2;" << r << ';' << g << ';' << b
      << 'm';
  return buf.str();
}

const string color_256(int index, bool is_bg = false) {
  assert(index >= 0 && index <= 255);
  std::ostringstream buf;
  buf << "\033[" << (is_bg ? 48 : 38) << ":5:" << index << 'm';
  return buf.str();
}

const string color_6x6x6(int r, int g, int b) {
  assert(r >= 0 && r <= 5);
  assert(g >= 0 && g <= 5);
  assert(b >= 0 && b <= 5);
  return color_256(16 + 36 * r + 6 * g + b);
}

const string bg_rgb(int r, int g, int b) {
  return rgb(r, g, b, true);
}

const string hex_color(const string &hex, bool is_bg = false) {
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

inline const string bg_hex_color(const string &hex) {
  return hex_color(hex, true);
}
} // namespace colors

namespace textStyles {
constexpr auto bold = SGR(1);
constexpr auto dim = SGR(2);
constexpr auto italic = SGR(3);
constexpr auto underline = SGR(4);
constexpr auto inverse = SGR(7);
constexpr auto hidden = SGR(8);
constexpr auto strike = SGR(9);
} // namespace textStyles

namespace resets {
constexpr auto all = SGR(0);
constexpr auto foreground = SGR(39);
constexpr auto fg = SGR(39);
constexpr auto bg = SGR(49);
constexpr auto background = SGR(49);
constexpr auto bold = SGR(22);
constexpr auto dim = SGR(22);
constexpr auto italic = SGR(23);
constexpr auto underline = SGR(24);
constexpr auto inverse = SGR(27);
constexpr auto hidden = SGR(28);
constexpr auto strike = SGR(29);
} // namespace resets

enum class TextStyle : uint16_t {
  bold = 1 << 0,
  dim = 1 << 1,
  italic = 1 << 2,
  underline = 1 << 3,
  inverse = 1 << 4,
  hidden = 1 << 5,
  strike = 1 << 6,
};
/// make enum flags better
uint16_t operator+(TextStyle flag) {
  return static_cast<uint16_t>(flag);
}
TextStyle operator|(TextStyle lhs, TextStyle rhs) {
  return static_cast<TextStyle>((+lhs) | (+rhs));
}
TextStyle &operator|=(TextStyle &lhs, TextStyle rhs) {
  return lhs = lhs | rhs;
}
bool operator&(TextStyle lhs, TextStyle rhs) {
  return ((+lhs) & (+rhs)) != 0;
}

inline string textStyle(string text, TextStyle styles) {
  string res = text;
  if (styles & TextStyle::bold) {
    res = textStyles::bold + res + resets::bold;
  }
  if (styles & TextStyle::dim) {
    res = textStyles::dim + res + resets::dim;
  }
  if (styles & TextStyle::italic) {
    res = textStyles::italic + res + resets::italic;
  }
  if (styles & TextStyle::underline) {
    res = textStyles::underline + res + resets::underline;
  }
  if (styles & TextStyle::inverse) {
    res = textStyles::inverse + res + resets::inverse;
  }
  if (styles & TextStyle::hidden) {
    res = textStyles::inverse + res + resets::inverse;
  }
  if (styles & TextStyle::strike) {
    res = textStyles::strike + res + resets::strike;
  }
  return res;
}

class Chalk {
private:
  string _color;     // 前景色
  string _bg_color;  // 背景色
  TextStyle _styles; // 文本样式
  string _text;      //

public:
  Chalk(string text) : _text(text) {}

  Chalk &color(int r, int g, int b) {
    _color = colors::rgb(r, g, b);
    return *this;
  }
  Chalk &clearColor() {
    _color = "";
    return *this;
  }
  Chalk &color(const string &hex) {
    _color = colors::hex_color(hex);
    return *this;
  }

  Chalk &bgColor(int r, int g, int b) {
    _bg_color = colors::bg_rgb(r, g, b);
    return *this;
  }

  Chalk &bgColor(const string &hex) {
    _bg_color = colors::bg_hex_color(hex);
    return *this;
  }
  Chalk &clearBgColor(int r, int g, int b) {
    _bg_color = "";
    return *this;
  }

  // 24 阶灰色,1-24 从黑到白
  Chalk &gray24(int deep = 12) noexcept {
    assert(deep >= 1 && deep <= 24);
    _color = colors::color_256(255 - deep);
    return *this;
  }
  /// 24 阶灰色,1-24 从黑到白
  Chalk &bg_gray24(int deep = 12) noexcept {
    assert(deep >= 1 && deep <= 24);
    _bg_color = colors::color_256(255 - deep);
    return *this;
  }
  ///  216 色,16-231  6x6x6: 16+36xr+6xg+b
  Chalk &color256(int index) noexcept {
    _color = colors::color_256(index);
    return *this;
  }
  ///  256 色, 除基本色外加 16-231  6x6x6: 16+36xr+6xg+b
  Chalk &bg_color256(int index) noexcept {
    _bg_color = colors::color_256(index);
    return *this;
  }
  ///   6x6x6 立方: 16+36xr+6xg+b (0<=r,g,b<=5)
  Chalk &color6x6x6(int r, int g, int b) noexcept {
    _color = colors::color_6x6x6(r, g, b);
    return *this;
  }
  ///   6x6x6 立方: 16+36xr+6xg+b (0<=r,g,b<=5)
  Chalk &bg_color6x6x6(int r, int g, int b) noexcept {
    _bg_color = colors::color_6x6x6(r, g, b);
    return *this;
  }

  Chalk &red() noexcept {
    this->_color = colors::red;
    return *this;
  }
  Chalk &green() noexcept {
    this->_color = colors::green;
    return *this;
  }
  Chalk &black() noexcept {
    this->_color = colors::black;
    return *this;
  }
  Chalk &yellow() noexcept {
    this->_color = colors::yellow;
    return *this;
  }
  Chalk &blue() noexcept {
    this->_color = colors::blue;
    return *this;
  }
  Chalk &cyan() noexcept {
    this->_color = colors::cyan;
    return *this;
  }
  Chalk &magenta() noexcept {
    this->_color = colors::magenta;
    return *this;
  }
  Chalk &white() noexcept {
    this->_color = colors::white;
    return *this;
  }
  Chalk &bg_red() noexcept {
    _bg_color = colors::bg_red;
    return *this;
  }
  Chalk &bg_green() noexcept {
    _bg_color = colors::bg_green;
    return *this;
  }
  Chalk &bg_blue() noexcept {
    _bg_color = colors::bg_blue;
    return *this;
  }
  Chalk &bg_black() noexcept {
    _bg_color = colors::bg_black;
    return *this;
  }
  Chalk &bg_yellow() noexcept {
    _bg_color = colors::bg_yellow;
    return *this;
  }
  Chalk &bg_cyan() noexcept {
    _bg_color = colors::bg_cyan;
    return *this;
  }
  Chalk &bg_magenta() noexcept {
    _bg_color = colors::bg_magenta;
    return *this;
  }
  Chalk &bg_white() noexcept {
    _bg_color = colors::bg_white;
    return *this;
  }
  Chalk &bold() noexcept {
    this->_styles |= TextStyle::bold;
    return *this;
  }
  Chalk &italic() noexcept {
    this->_styles |= TextStyle::italic;
    return *this;
  }
  Chalk &underline() noexcept {
    this->_styles |= TextStyle::underline;
    return *this;
  }
  Chalk &dim() noexcept {
    this->_styles |= TextStyle::dim;
    return *this;
  }
  Chalk &hidden() noexcept {
    this->_styles |= TextStyle::hidden;
    return *this;
  }
  Chalk &strike() noexcept {
    this->_styles |= TextStyle::strike;
    return *this;
  }

  string build() const noexcept {
    string text = _color.empty() ? _text : _color + _text + resets::fg;
    text = _bg_color.empty() ? text : _bg_color + text + resets::bg;
    return textStyle(text, _styles);
  }

  string styled_text() const noexcept {
    return build();
  }
};

inline Chalk chalk(string text) {
  Chalk c(text);
  return c;
}
std::ostream &operator<<(std::ostream &os, const Chalk &c) {
  os << c.build();
  return os;
}
} // namespace chalks
