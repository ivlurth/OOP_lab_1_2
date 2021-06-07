#pragma once
#include <list>
#include <memory>
#include <iostream>

#include "Shape.h"

namespace ShapeSpace {
	class ShapeList {
	private:
		std::list<std::unique_ptr<Shape>> inList;

	public:
		ShapeList();
		void add(std::unique_ptr<Shape>);
		void clear();
		~ShapeList();

		auto begin() const {
			return inList.begin();
		}

		auto end() const {
			return inList.end();
		}

		auto back() {
			return &inList.back();
		}
	};
}