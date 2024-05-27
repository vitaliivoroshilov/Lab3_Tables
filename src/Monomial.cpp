#include <iostream>
#include <string>

#include "Monomial.h"


Monomial::Monomial() {
	kf = 0.0;
	degs = 0;
}

Monomial::Monomial(double _kf, size_t _degs) {
	kf = _kf;
	degs = _degs;
}

Monomial::Monomial(const std::string& strMonom) {
	this->ParseMonom(strMonom);
}

Monomial::~Monomial() {}

void Monomial::ParseMonom(const std::string& strMonom) {
	size_t i = 0;
	std::string strKf = "";
	while (strMonom[i] != 'x')
		strKf += strMonom[i++];
	kf = std::strtod(strKf.c_str(), NULL);

	std::string strDegs = "";
	i += 1;
	strDegs += strMonom[i];
	i += 2;
	strDegs += strMonom[i];
	i += 2;
	strDegs += strMonom[i];
	degs = std::atoi(strDegs.c_str());
}

std::string Monomial::MonomToString() {
	size_t digits = degs % 10;
	size_t hundreds = (degs - degs % 100) / 100;
	size_t tens = (degs - digits - hundreds * 100) / 10;

	std::string strMonom;
	strMonom += std::to_string(kf);
	size_t i = strMonom.length() - 1;
	while ((strMonom[i] == '0') && (strMonom[i - 1] != '.')) {
		strMonom.pop_back();
		i--;
	}
	strMonom += 'x';
	strMonom += std::to_string(hundreds) + 'y';
	strMonom += std::to_string(tens) + 'z';
	strMonom += std::to_string(digits);
	return strMonom;
}

bool Monomial::IsEqual(const Monomial& monom) const {
	return degs == monom.degs;
}

bool Monomial::IsZero() const {
	return kf == 0.0;
}

void Monomial::Add(const Monomial& monom) {
	kf += monom.kf;
}

void Monomial::Subtract(const Monomial& monom) {
	kf -= monom.kf;
}

void Monomial::MultNumber(const double k) {
	kf *= k;
}

void Monomial::MultMonom(const Monomial& monom) {
	size_t digits1 = degs % 10;
	size_t hundreds1 = (degs - degs % 100) / 100;
	size_t tens1 = (degs - digits1 - hundreds1 * 100) / 10;
	size_t digits2 = monom.degs % 10;
	size_t hundreds2 = (monom.degs - monom.degs % 100) / 100;
	size_t tens2 = (monom.degs - digits2 - hundreds2 * 100) / 10;
	if ((digits1 + digits2 > 9) || (tens1 + tens2 > 9) || (hundreds1 + hundreds2 > 9)) {
		std::cout << "Error! Deg > 9!";
		return;
	}
	kf *= monom.kf;
	degs += monom.degs;
}

void Monomial::Differentiate(const char variable) {
	size_t digits = degs % 10;
	size_t hundreds = (degs - degs % 100) / 100;
	size_t tens = (degs - digits - hundreds * 100) / 10;

	if (variable == 'x') {
		kf *= hundreds;
		if (hundreds != 0)
			degs -= 100;
	}
	if (variable == 'y') {
		kf *= tens;
		if (tens != 0)
			degs -= 10;
	}
	if (variable == 'z') {
		kf *= digits;
		if (digits != 0)
			degs -= 1;
	}
}

void Monomial::Integrate(const char variable) {
	size_t digits = degs % 10;
	size_t hundreds = (degs - degs % 100) / 100;
	size_t tens = (degs - digits - hundreds * 100) / 10;

	if (variable == 'x') {
		kf /= hundreds;
		if (hundreds != 9)
			degs += 100;
	}
	if (variable == 'y') {
		kf /= tens;
		if (tens != 9)
			degs += 10;
	}
	if (variable == 'z') {
		kf /= digits;
		if (digits != 9)
			degs += 1;
	}
}

double Monomial::CalculateInPoint(const double x, const double y, const double z) const {
	double res = kf;
	int deg = degs;
	while (deg >= 100) {
		res *= x;
		deg -= 100;
	}
	while (deg >= 10) {
		res *= y;
		deg -= 10;
	}
	while (deg >= 0) {
		res *= z;
		deg -= 1;
	}
	return res;
}

Monomial& Monomial::operator=(const Monomial& monom) {
	kf = monom.kf;
	degs = monom.degs;
	return *this;
}

bool Monomial::operator==(const Monomial& monom) const {
	return IsEqual(monom) && (kf == monom.kf);
}

bool Monomial::operator!=(const Monomial& monom) const {
	return !(*this == monom);
}

bool Monomial::operator<(const Monomial& monom) const {
	return degs < monom.degs;
}

bool Monomial::operator>(const Monomial& monom) const {
	return degs > monom.degs;
}

std::ostream& operator<<(std::ostream& out, const Monomial& monom)
{
	Monomial monomial(monom); 
	out << monomial.MonomToString();
	return out;
}