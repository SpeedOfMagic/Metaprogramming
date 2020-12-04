#include <cassert>

#include "furniture.h"
#include "factory.h"

using MyFactoryHierarchy = GetAbstractFactory<3, 5,
	Typelist<Chair, Table, Sofa>,
	Typelist<WoodenChair, WoodenTable, WoodenSofa>,
	Typelist<MetalChair, MetalSofa, MetalTable>,
	Typelist<MetalRichChair, MetalRichTable, MetalRichSofa>,
	Typelist<MetalPoorChair, MetalPoorTable>
>;

int main() {
	Factory MyFactory = MyFactoryHierarchy::GetConcreteFactory<MetalPoorChair>::result();
	Sofa* sofa = MyFactory.Get<Sofa>();
	Table* table = MyFactory.Get<Table>();
	Chair* chair = MyFactory.Get<Chair>();

	Factory MyFactory2 = MyFactoryHierarchy::GetConcreteFactory<Chair>::result();
	Chair* another_chair = MyFactory2.Get<Chair>();
	WoodenTable* another_table = MyFactory2.Get<WoodenTable>();

	return 0;
}