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
	Sofa* a = MyFactory.Get<Sofa>();
	return 0;
}