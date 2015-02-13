#include "Financial_product.h"

/*	La classe Financial_product est la classe mère de Basic_products et de Option.
	On pourrait complexifier le projet en ajoutant d'autres produits financiers, des produits exotiques par exemple.
	Il faudrait pour cela définir une classe Exotic_products qui hérite de Financial_products.
	Le reste de la structure du programme est conçue pour accueillir autant de produits que souhaité.*/

Financial_product::Financial_product()
{
}


Financial_product::~Financial_product()
{
}
