#include <rgui.hpp>
#include <iostream>

int main(void) {
	rgui::define::init();
	rgui::define::prefer_wayland();
	RGUIwindow window = rgui::window::create();
	rgui::define::setcontext(window);

	rgba bg{0.2f, 0.2f, 0.2f, 0.2f};
	rgui::window::config::bg::rgba(window, bg);

	rgba rectbg{0.3f, 0.3f, 0.3f, 0.2f};
	rgba gbg{0.0f, 0.0f, 0.0f, 0.3f};
	rgba gradbg[4];
	color::gradient::rectRGBA(bg, gbg, gradbg);

	while (rgui::window::loop(window)) {
		rgui::mainloop(window);

		rgui::rect::rgba(100, 100, 50, 1920, rectbg, 165.0f);
		rgui::rect::rgba(250, 100, 50, 1920, rectbg, 165.0f);
		rgui::rect::rgba(400, 100, 50, 1920, rectbg, 165.0f);

		rgui::rect::rgba_grad(60, 100, 1920, 25, gradbg, 255.0f);
		rgui::rect::rgba_grad(210, 100, 1920, 25, gradbg, 255.0f);
		rgui::rect::rgba_grad(360, 100, 1920, 25, gradbg, 255.0f);

	}
	return 0;
}

