#ifndef RGUI_H
#define RGUI_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

struct rgba {
	float red = 1.0f;
	float green = 1.0f;
	float blue = 1.0f;
	float alpha = 1.0f;
};

struct rgb {
	float red = 1.0f;
	float green = 1.0f;
	float blue = 1.0f;
};

struct RGUIwindow {
	int width = 0;
	int height = 0;
	GLFWwindow* handle;
	int truewidth = 0;
	int trueheight = 0;
	rgba bg{1.0f, 1.0f, 1.0f, 1.0f};
};

namespace color {
	rgb makeRGB(const rgba& input) {
		rgb new_rgb{
			input.red,
			input.green,
			input.blue
		};
		return new_rgb;
	}

	rgba makeRGBA(const rgb& input, float alpha = 1.0f) {
		rgba new_rgba{
			input.red,
			input.green,
			input.blue,
			alpha
		};
		return new_rgba;
	}

	namespace gradient {
		void rectRGBA(const rgba& input1, const rgba& input2, rgba* addr) {
			addr[0] = input1;
			addr[1] = input1;
			addr[2] = input2;
			addr[3] = input2;
		}

		void rectRGBA_45(const rgba& input1, const rgba& input2, rgba* addr) {
			addr[0] = input1;
			rgba midway{
				(input1.red + input2.red) / 2.0f,
				(input1.green + input2.green) / 2.0f,
				(input1.blue + input2.blue) / 2.0f,
				(input1.alpha + input2.alpha) / 2.0f
			};
			addr[1] = midway;
			addr[2] = midway;
			addr[3] = input2;
		}
	}
}

namespace rgui {

	namespace define {
		void init(bool resizable = true) {
			glfwInit();
			if (resizable) glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
			else glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		}

		void prefer_wayland() {
			glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
		}

		void setcontext(RGUIwindow window) {
			glfwMakeContextCurrent(window.handle);
			gladLoadGL();

			glClearColor(1.0, 1.0, 1.0, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_SCISSOR_TEST);
			glDisable(GL_CULL_FACE);

		}
	}

	namespace window {
		RGUIwindow create(int width=600, int height=800, const char* title = "rgui window") {
			GLFWwindow* new_window = glfwCreateWindow(width, height, title, NULL, NULL);
			RGUIwindow window{width, height, new_window};
			return window;
		}

		void resize(RGUIwindow window, unsigned width, unsigned height) {
			glfwSetWindowSize(window.handle, width, height);
		}

		int loop(RGUIwindow window) {
			int ret = glfwWindowShouldClose(window.handle);
			return !(ret);
		}

		namespace config {
			void overridedecoration() {
				glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
			}
			namespace bg {
				void alpha(RGUIwindow window, float alpha) {
					window.bg.alpha = alpha;
					glClearColor(window.bg.red, window.bg.green, window.bg.blue, window.bg.alpha);
				}
				void rgba(RGUIwindow window, rgba color) {
					window.bg = color;
					glClearColor(window.bg.red, window.bg.green, window.bg.blue, window.bg.alpha);
				}
			}
		}
	}

	namespace rect {
		void rgba(float x, float y, float w, float h, rgba color = rgba{}, float angle = 0.0f) {
			glColor4f(color.red, color.green, color.blue, color.alpha);
			glTranslatef(x, y, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			glBegin(GL_QUADS);
			glVertex2f(-w/2.0f, -h/2.0f);
			glVertex2f(w/2.0f, -h/2.0f);
			glVertex2f(w/2.0f, h/2.0f);
			glVertex2f(-w/2.0f, h/2.0f);
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glRotatef(0.0f - angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f - x, 0.0f - y, 0.0f);
		}

		void rgba_grad(float x, float y, float w, float h, ::rgba color[4], float angle = 0.0f) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(color[0].red, color[0].green, color[0].blue, color[0].alpha);
			glTranslatef(x, y, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			glBegin(GL_QUADS);
			glVertex2f(-w/2.0f, -h/2.0f);
			glColor4f(color[1].red, color[1].green, color[1].blue, color[1].alpha);
			glVertex2f(w/2.0f, -h/2.0f);
			glColor4f(color[2].red, color[2].green, color[2].blue, color[2].alpha);
			glVertex2f(w/2.0f, h/2.0f);
			glColor4f(color[3].red, color[3].green, color[3].blue, color[3].alpha);
			glVertex2f(-w/2.0f, h/2.0f);
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glRotatef(0.0f - angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f - x, 0.0f - y, 0.0f);
		}
	}

	// This is a cruel world.

	void mainloop(RGUIwindow window) {
		glfwPollEvents();
		glfwSwapBuffers(window.handle);

		int fbw, fbh;
		int width, height;
		glfwGetFramebufferSize(window.handle, &fbw, &fbh);
		glViewport(0, 0, fbw, fbh);
		glfwGetWindowSize(window.handle, &width, &height);
		window.width = fbw;
		window.height = fbh;
		window.truewidth = width;
		window.trueheight = height;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT);

	}

	void terminate() {
		glfwTerminate();
	}

}

namespace cursor {
	void cursorpos(RGUIwindow window, double* x, double* y) {
		double curx, cury;
		glfwGetCursorPos(window.handle, &curx, &cury);
		*x = curx;
		*y = cury;
	}

	int mousedown(RGUIwindow window) {
		if (glfwGetMouseButton(window.handle, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) return 1;
		else return 0;
	}

	int rightmousedown(RGUIwindow window) {
		if (glfwGetMouseButton(window.handle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) return 1;
		else return 0;
	}

	int clickarea(RGUIwindow window, int x, int y, int width, int height) {
		double curx, cury;
		cursor::cursorpos(window, &curx, &cury);
		if (curx < x - (width / 2.0f)) {
			return 0;
		} else if (curx > x + (width / 2.0f)) {
			return 0;
		} else if (cury < y - (height / 2.0f)) {
			return 0;
		} else if (cury > y + (height / 2.0f)) {
			return 0;
		} else if (cursor::mousedown(window)) {
			return 1;
		} else {
			return 0;
		}
	}

	int rightclickarea(RGUIwindow window, int x, int y, int width, int height) {
		double curx, cury;
		cursor::cursorpos(window, &curx, &cury);
		if (curx < x - (width / 2.0f)) {
			return 0;
		} else if (curx > x + (width / 2.0f)) {
			return 0;
		} else if (cury < y - (height / 2.0f)) {
			return 0;
		} else if (cury > y + (height / 2.0f)) {
			return 0;
		} else if (cursor::rightmousedown(window)) {
			return 1;
		} else {
			return 0;
		}
	}
}

#endif

