#pragma once
#include "stdafx.h"
#include <exception>
#include <iostream>

extern int num;

template<typename type>
class Array_2D {
public:
	Array_2D(const int& row, const int& col);
	Array_2D() { throw std::runtime_error("Array_2D: cannot initialize without two integers!"); }
	~Array_2D();
	type* get(int i, int j);
	void write(type* pos, type val);
	virtual void init() {};

	type** map;
protected:
	type* data;
};


class relations : Array_2D<bool> {
public:
	relations() :Array_2D<bool>() {
		throw std::runtime_error("relations: cannot initialize without two integers!");
	}
	relations(const int& row, const int& col) :Array_2D<bool>(row, col) {}
	bool** map : Array_2D<bool>::map;
};

void print_data(relations&);

void init(relations&);