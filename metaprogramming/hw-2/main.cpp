#include "furniture.h"
#include "factory.h"

using MyFactoryHierarchy = GetAbstractFactory<3, 5,
	TypeList<Chair, Table, Sofa>,
	TypeList<WoodenChair, WoodenTable, WoodenSofa>,
	TypeList<MetalChair, MetalTable, MetalSofa>,
	TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
	TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>
>;

int main() {
	using tl = TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>;
	Factory MyFactory = MyFactoryHierarchy::GetConcreteFactory<MetalRichSofa>::result();
	Sofa* a = MyFactory.Get<Sofa>();
	return 0;
}