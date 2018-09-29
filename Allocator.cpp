#include "Product.h"
#include "Perishable.h"

namespace GMS {

	// creates an empty product
	//
	iProduct* CreateProduct() {
		return new Product();
	}

	// creates an empty perishable product
	//
	iProduct* CreatePerishable() {
		return new Perishable();
	}
}