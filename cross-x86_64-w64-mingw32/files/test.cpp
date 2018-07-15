#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

class base {
public:
	virtual ~base() = default;
};

class derived : public base {
};

int main() {
	std::thread t([] () {
		auto p = std::unique_ptr<base>(new derived());
		std::cerr << "this shouldn't be null: " << dynamic_cast<derived *>(p.get()) << std::endl;
	});

	try {
		throw std::runtime_error("too too roo, motherfuckers");
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	t.join();
	return 0;
}
