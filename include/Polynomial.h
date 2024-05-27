#pragma once

#include <iostream>

#include "TList.h"
#include "Monomial.h"


class Polynomial {

private:

	TList<Monomial> monomsList;

public:

	Polynomial();
	Polynomial(const Polynomial& polynom);
	Polynomial(const std::string& strPolynom);

	void DeleteZero();
	void ParsePolynom(const std::string& srtPolynom);
	std::string PolynomToString();

	void AddMonom(const Monomial& monom);
	void AddMonom(const std::string& strMonom);
	void AddPolynom(const Polynomial& polynom);
	void AddPolynom(const std::string& strPolynom);

	void SubtractMonom(const Monomial& monom);
	void SubtractMonom(const std::string& strMonom);
	void SubtractPolynom(const Polynomial& polynom);
	void SubtractPolynom(const std::string& strPolynom);

	void MultNumber(const double k);
	void MultMonom(const Monomial& monom);
	void MultMonom(const std::string& strMonom);
	void MultPolynom(const Polynomial& polynom);
	void MultPolynom(const std::string& strPolynom);

	Polynomial Differentiate(const char variable) const;
	Polynomial Integrate(const char variable) const;

	double CalculateInPoint(const double x, const double y, const double z) const;

	Polynomial& operator=(const Polynomial& polynom);

	Polynomial operator+(const Monomial& monom) const;
	Polynomial operator+(const Polynomial& polynom) const;

	Polynomial operator-(const Monomial& monom) const;
	Polynomial operator-(const Polynomial& polynom) const;

	Polynomial operator*(const double k) const;
	Polynomial operator*(const Monomial& monom) const;
	Polynomial operator*(const Polynomial& polynom) const;

	bool operator==(const Polynomial& polynom) const;
	friend std::ostream& operator<<(std::ostream&, const Polynomial& polynom);
	friend std::ostream& operator<<(std::ostream&, const Polynomial* polynom);
};
