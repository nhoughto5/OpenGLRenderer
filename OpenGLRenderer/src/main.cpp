#include "pch.h"
#include "Application.h"

int main(void)
{
	Application app;

	try {
		app.Run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}