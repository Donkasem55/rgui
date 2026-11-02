#include <rgui.hpp>

int main(void) {
	rgui::define::init();
	rgui::define::prefer_wayland();
	RGUIwindow window = rgui::window::create();
	rgui::define::setcontext(window);

	rgba bg{0.5f, 0.5f, 0.5f, 0.5f};
	rgui::window::config::bg::rgba(window, bg);

	while (rgui::window::loop(window)) {
		rgui::mainloop(window);
		rgui::rect::rgba(100, 100, 100, 100);
	}
	return 0;
}

