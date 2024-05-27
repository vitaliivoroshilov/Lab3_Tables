#pragma once

#include <iostream>

class Monomial {

private:

	double kf;
	size_t degs;

public:

	Monomial();
	Monomial(double _kf, size_t _degs);
	Monomial(const std::string& strMonom);
	~Monomial();

	void ParseMonom(const std::string& strMonom);
	std::string MonomToString();

	bool IsEqual(const Monomial& monom) const;
	bool IsZero() const;

	void Add(const Monomial& monom);
	void Subtract(const Monomial& monom);
	void MultNumber(const double k);
	void MultMonom(const Monomial& monom);
	void Differentiate(const char variable);
	void Integrate(const char variable);
	double CalculateInPoint(const double x, const double y, const double z) const;

	Monomial& operator=(const Monomial& monom);
	bool operator==(const Monomial& monom) const;
	bool operator!=(const Monomial& monom) const;
	bool operator<(const Monomial& monom) const;
	bool operator>(const Monomial& monom) const;
	friend std::ostream& operator<<(std::ostream& out, const Monomial& monom);
};