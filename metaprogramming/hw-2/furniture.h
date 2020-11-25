#pragma once

#include <iostream>

/*===============================================*/

struct Furniture { Furniture() { std::cout << "Furniture" << std::endl; } };

/*===============================================*/

struct Chair : public Furniture { Chair() { std::cout << "Chair" << std::endl; } };

struct Table : public Furniture { Table() { std::cout << "Table" << std::endl; } };

struct Sofa  : public Furniture { Sofa()  { std::cout << "Sofa"  << std::endl; } };

/*===============================================*/

struct WoodenChair : public Chair { WoodenChair() { std::cout << "WoodenChair" << std::endl; } };

struct WoodenTable : public Table { WoodenTable() { std::cout << "WoodenTable" << std::endl; } };

struct WoodenSofa  : public Sofa  { WoodenSofa()  { std::cout << "WoodenSofa"  << std::endl; } };

/*===============================================*/

struct MetalChair : public Chair { MetalChair() { std::cout << "MetalChair" << std::endl; } };

struct MetalTable : public Table { MetalTable() { std::cout << "MetalTable" << std::endl; } };

struct MetalSofa  : public Sofa  { MetalSofa()  { std::cout << "MetalSofa" <<  std::endl; } };

/*===============================================*/

struct MetalRichChair : public MetalChair { MetalRichChair() { std::cout << "MetalRichChair" << std::endl; } };

struct MetalRichTable : public MetalTable { MetalRichTable() { std::cout << "MetalRichTable" << std::endl; } };

struct MetalRichSofa  : public MetalSofa  { MetalRichSofa()  { std::cout << "MetalRichSofa"  << std::endl; } };

/*===============================================*/

struct MetalPoorChair : public MetalChair { MetalPoorChair() { std::cout << "MetalPoorChair" << std::endl; } };

struct MetalPoorTable : public MetalTable { MetalPoorTable() { std::cout << "MetalPoorTable" << std::endl; } };

struct MetalPoorSofa : public MetalSofa { MetalPoorSofa() { std::cout << "MetalPoorSofa" << std::endl; } };

/*===============================================*/