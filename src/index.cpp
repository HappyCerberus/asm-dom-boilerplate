#include <emscripten/val.h>
#include <functional>
#include <string>
using namespace asmdom;

asmdom::VNode* current_view = NULL;

void render() {
  asmdom::VNode* new_node = h("svg", Data(Attrs{{"viewBox", "0 0 1000 1000"}, {"xmlns", "http://www.w3.org/2000/svg"}, {"class", "sudoku"}}),
                              Children{
                                  h("path",
                                    Data(Attrs{{"d","M13.333 9.333V7.746c0-.717.159-1.08 1.271-1.08H16V4h-2.33c-2.853 0-3.795 1.308-3.795 3.554v1.78H8V12h1.875v8h3.458v-8h2.35L16 9.333h-2.667z"}})
                                  )});
  current_view = asmdom::patch(current_view, new_node);
};

int main() {
  asmdom::Config config;
  asmdom::init(config);

  current_view = <svg id="root" xmlns="http://www.w3.org/2000/svg" width="600px" class="sudoku"></svg>;
  asmdom::patch(
    emscripten::val::global("document").call<emscripten::val>(
      "getElementById",
      std::string("root")
    ),
    current_view
  );

  render();

  return 0;
};
