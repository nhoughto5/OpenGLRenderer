#include "pch.h"
#include "Renderer.h"

int main(void)
{
	Renderer app;

	try {
		app.run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}