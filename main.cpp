#include <rgui.hpp>
#include <iostream>

void aero_bar(int x, int y, rgba rectbg, rgba gradbg[4], float angle = 165.0f, int w = 50) {
		rgui::rect::rgba(x, y, w, 1920, rectbg, angle);
		rgui::rect::rgba_grad(x-(w/2.0)-15, y, 1920, 25, gradbg, angle + 90.0f);
}

int main(void) {
	rgui::define::init();
	rgui::define::prefer_wayland();
	RGUIwindow window = rgui::window::create(600, 800, "The Future Promised To Us");
	rgui::define::setcontext(window);

	rgba bg{0.2f, 0.2f, 0.2f, 0.2f};
	rgui::window::config::bg::rgba(window, bg);

	rgba rectbg{0.3f, 0.3f, 0.3f, 0.2f};
	rgba gbg{0.0f, 0.0f, 0.0f, 0.2f};
	rgba gradbg[4];
	color::gradient::rectRGBA(bg, gbg, gradbg);

	float angle = 165.0f;

	while (rgui::window::loop(window)) {
		rgui::mainloop(window);

		aero_bar(0, 100, rectbg, gradbg, angle, 150);
		aero_bar(200, 100, rectbg, gradbg, angle);
		aero_bar(400, 100, rectbg, gradbg, angle, 250);
		rgui::rect::rgba_grad(320, 100, 1920, 25, gradbg, angle + 90);
		rgui::rect::rgba_grad(540, 100, 1920, 25, gradbg, angle - 90);
		aero_bar(650, 100, rectbg, gradbg, angle);
		rgui::rect::rgba_grad(815, 100, 1920, 25, gradbg, angle - 90);
		aero_bar(750, 100, rectbg, gradbg, angle, 100);
		aero_bar(950, 100, rectbg, gradbg, angle);
		aero_bar(1020, 100, rectbg, gradbg, angle);
		aero_bar(1200, 100, rectbg, gradbg, angle, 150);
		rgui::rect::rgba_grad(1170, 100, 1920, 25, gradbg, angle + 90);
		rgui::rect::rgba_grad(1190, 100, 1920, 25, gradbg, angle + 90);

	}
	return 0;
}

