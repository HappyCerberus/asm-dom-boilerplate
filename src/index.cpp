#include <emscripten/val.h>
#include <functional>
#include <string>
using namespace asmdom;

asmdom::VNode* current_view = NULL;

void render() {
  asmdom::VNode* new_node = h("g", Data(Attrs{{"id", "playground"}}),
                              Children{
                                  h("path",
                                    Data(Attrs{{"d","M13.333 9.333V7.746c0-.717.159-1.08 1.271-1.08H16V4h-2.33c-2.853 0-3.795 1.308-3.795 3.554v1.78H8V12h1.875v8h3.458v-8h2.35L16 9.333h-2.667z"}})
                                  )});
  current_view = asmdom::patch(current_view, new_node);
};

asmdom::VNode* generate_block(int id) {
  int x = 50 + (id%3)*300;
  int y = 50 + (id/3)*300;
  int width = 300;
  int height = 300;
  return h("rect",
            Data(Attrs{{"class", "line-thick"}, {"fill", "transparent"},
                       {"x", std::to_string(x)}, {"y", std::to_string(y)},
                       {"width", std::to_string(width)}, {"height", std::to_string(height)}}));
}

asmdom::VNode* draw_blocks(asmdom::VNode* block_view) {
  asmdom::VNode* new_blocks = h("g", Data(Attrs{{"id", "blocks"}, {"class", "whatever"}}),
                                Children{
                                    generate_block(0), generate_block(1), generate_block(2),
                                    generate_block(3), generate_block(4), generate_block(5),
                                    generate_block(6), generate_block(7), generate_block(8),
                                });
  return asmdom::patch(block_view, new_blocks);
}

int main() {
  asmdom::Config config;
  asmdom::init(config);
/*
  current_view = <g id="playground"></g>;
  asmdom::patch(
    emscripten::val::global("document").call<emscripten::val>(
      "getElementById",
      std::string("playground")
    ),
    current_view
  );
*/

  asmdom::VNode* block_view = toVNode(emscripten::val::global("document").call<emscripten::val>("getElementById", emscripten::val("blocks")));
/*  asmdom::VNode* block_view = <g id="blocks" class="testing"></g>;
  asmdom::patch(
      emscripten::val::global("document").call<emscripten::val>(
          "getElementById",
          std::string("blocks")
      ),
      block_view
  );*/


  block_view = draw_blocks(block_view);
/*
  render();
*/
  return 0;
};
