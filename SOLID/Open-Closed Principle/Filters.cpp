#include <iostream>
#include <vector>
#include <string>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
	std::string name;
	Color color;
	Size size;
};

template <typename T> struct AndSpecification;

template <typename T> struct Specification {
	virtual bool is_satisfied(T* item) = 0;

	AndSpecification<T> operator &&(Specification&& other) {
		return AndSpecification<T>(*this, other);
	}
};

template <typename T> struct Filter {
	virtual std::vector<T*> filter(
		std::vector<T*> items,
		Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
	std::vector<Product*> filter(
		std::vector<Product*> items,
		Specification<Product>& spec) override {
		std::vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

struct ColorSpecification : Specification<Product> {
	Color color;

	explicit ColorSpecification(const Color color) : color{color} {}

	bool is_satisfied(Product* item) override {
		return item->color == color;
	}
};

struct SizeSpecification : Specification<Product> {
	Size size;

	explicit SizeSpecification(const Size size) : size{ size } {}

	bool is_satisfied(Product* item) override {
		return item->size == size;
	}
};

template <typename T> struct AndSpecification : Specification<T> {
	Specification<T>& first;
	Specification<T>& second;

	AndSpecification(Specification<T>& first, Specification<T>& second) : first{first}, second{second} {}

	bool is_satisfied(T* item) override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

int main() {
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };
	std::vector<Product*> all{ &apple, &tree, &house };

	BetterFilter bf;

	auto green_and_big = ColorSpecification(Color::Green)
		&& SizeSpecification(Size::Large);
	AndSpecification<Product> green_and_large{ green_and_big };
	auto big_green_things = bf.filter(all, green_and_large);

	for (auto& thing : big_green_things)
		std::cout << thing->name << " is green and big" << std::endl;
	return 0;
}