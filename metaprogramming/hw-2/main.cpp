#include "furniture.h"
#include "factory.h"

#include "../library/TL/size.h"


using MyFactoryHierarchy = GetAbstractFactory<3, 5,
	Typelist<Chair, Table, Sofa>,
	Typelist<WoodenChair, WoodenTable, WoodenSofa>,
	Typelist<MetalChair, MetalSofa, MetalTable>,
	Typelist<MetalRichChair, MetalRichTable, MetalRichSofa>,
	Typelist<MetalPoorChair, MetalPoorTable>
>;

int main() {
	std::cout << TL::IsBaseOf<TypeList<MetalChair, MetalSofa, MetalTable>, TypeList<MetalPoorChair, MetalPoorTable>>::result << std::endl;
	Factory MyFactory = MyFactoryHierarchy::GetConcreteFactory<MetalPoorChair>::result();
	Sofa* a = MyFactory.Get<Sofa>();
	return 0;
}