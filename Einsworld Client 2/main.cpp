#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Rendering/window.cpp"


int main() {
	Window window;
	while (!window.shouldClose()) {
		window.update();
		//std::cout << "tick" << std::endl;
	}
	system("pause");
	return 0;
}