#include "ShapeList.h"

namespace ShapeSpace {
	ShapeList::ShapeList() {
		std::cout << "ShapeList has been created!" << std::endl;
	}

	ShapeList::~ShapeList() {
		std::cout << "ShapeList has been destroyed!" << std::endl;
	}

	void ShapeList::add(std::unique_ptr<Shape> objP) {
		inList.push_back(move(objP));
	}

	void ShapeList::clear() {
		inList.clear();
	}
}