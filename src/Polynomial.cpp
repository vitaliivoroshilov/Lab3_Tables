#include <iostream>
#include <string>

#include "Polynomial.h"

Polynomial::Polynomial() {}

Polynomial::Polynomial(const Polynomial& polynom) {
	monomsList = polynom.monomsList;
}

Polynomial::Polynomial(const std::string& strPolynom) {
	ParsePolynom(strPolynom);
}

void Polynomial::DeleteZero() {
	for (size_t i = 0; i < monomsList.Size(); i++)
		if (monomsList[i].IsZero())
			monomsList.PopPos(i);
}

void Polynomial::ParsePolynom(const std::string& strPolynom) {
	monomsList.Clear();
	size_t i = 0;
	std::string strMonom;
	Monomial monom;
	while (i < strPolynom.length()) {
		strMonom = "";
		while ((strPolynom[i] != '+') && (i < strPolynom.length()))
			strMonom += strPolynom[i++];
		i++;
		monom.ParseMonom(strMonom);
		monomsList.PushSort(monom);
	}
	DeleteZero();
}

std::string Polynomial::PolynomToString() {
	DeleteZero();
	if (monomsList.IsEmpty())
		return "0";
	size_t i = 0;
	std::string strPolynom = "";
	while (i < monomsList.Size())
		strPolynom += monomsList[i++].MonomToString() + '+';
	strPolynom.pop_back();
	return strPolynom;
}

void Polynomial::AddMonom(const Monomial& monom) {
	if (monomsList.IsEmpty()) {
		monomsList.PushFront(monom);
		return;
	}
	monomsList.CurrentToPos(0);
	size_t i = 0;
	while ((i < monomsList.Size()) && !(monomsList[i].IsEqual(monom))) {
		monomsList.CurrentNext();
		i++;
	}
	if (i >= monomsList.Size())
		monomsList.PushSort(monom);
	else {
		monomsList[i].Add(monom);
		if (monomsList[i].IsZero())
			monomsList.PopPos(i);
	}
}

void Polynomial::AddMonom(const std::string& strMonom) {
	Monomial monom;
	monom.ParseMonom(strMonom);
	AddMonom(monom);
}

void Polynomial::AddPolynom(const Polynomial& polynom) {
	for (size_t i = 0; i < polynom.monomsList.Size(); i++)
		AddMonom(polynom.monomsList.GetPos(i));
}

void Polynomial::AddPolynom(const std::string& strPolynom) {
	Polynomial polynom;
	polynom.ParsePolynom(strPolynom);
	AddPolynom(polynom);
}

void Polynomial::SubtractMonom(const Monomial& monom) {
	Monomial monomial(monom);
	monomial.MultNumber(-1.0);
	AddMonom(monomial);
}

void Polynomial::SubtractMonom(const std::string& strMonom) {
	Monomial monom;
	monom.ParseMonom(strMonom);
	SubtractMonom(monom);
}

void Polynomial::SubtractPolynom(const Polynomial& polynom) {
	for (size_t i = 0; i < polynom.monomsList.Size(); i++)
		SubtractMonom(polynom.monomsList.GetPos(i));
}

void Polynomial::SubtractPolynom(const std::string& strPolynom) {
	Polynomial polynom;
	polynom.ParsePolynom(strPolynom);
	SubtractPolynom(polynom);
}

void Polynomial::MultNumber(const double k) {
	for (size_t i = 0; i < monomsList.Size(); i++)
		monomsList[i].MultNumber(k);
	DeleteZero();
}

void Polynomial::MultMonom(const Monomial& monom) {
	for (size_t i = 0; i < monomsList.Size(); i++)
		monomsList[i].MultMonom(monom);
	DeleteZero();
}

void Polynomial::MultMonom(const std::string& strMonom) {
	Monomial monom;
	monom.ParseMonom(strMonom);
	MultMonom(monom);
}

void Polynomial::MultPolynom(const Polynomial& polynom) {
	Polynomial res;
	Monomial monom;
	for (size_t i = 0; i < monomsList.Size(); i++)
		for (size_t j = 0; j < polynom.monomsList.Size(); j++) {
			monom = monomsList[i];
			monom.MultMonom(polynom.monomsList.GetPos(j));
			res.AddMonom(monom);
		}
	res.DeleteZero();
	*this = res;
}

void Polynomial::MultPolynom(const std::string& strPolynom) {
	Polynomial polynom;
	polynom.ParsePolynom(strPolynom);
	MultPolynom(polynom);
}

Polynomial Polynomial::Differentiate(const char variable) const {
	Polynomial res(*this);
	for (size_t i = 0; i < res.monomsList.Size(); i++)
		res.monomsList[i].Differentiate(variable);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::Integrate(const char variable) const {
	Polynomial res(*this);
	for (size_t i = 0; i < res.monomsList.Size(); i++)
		res.monomsList[i].Integrate(variable);
	res.DeleteZero();
	return res;
}

double Polynomial::CalculateInPoint(const double x, const double y, const double z) const {
	double res = 0.0;
	for (size_t i = 0; i < monomsList.Size(); i++)
		res += monomsList.GetPos(i).CalculateInPoint(x, y, z);
	return res;
}

Polynomial& Polynomial::operator=(const Polynomial& polynom) {
	if (this == &polynom)
		return *this;
	monomsList = polynom.monomsList;
}

Polynomial Polynomial::operator+(const Monomial& monom) const {
	Polynomial res(*this);
	res.AddMonom(monom);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator+(const Polynomial& polynom) const {
	Polynomial res(*this);
	res.AddPolynom(polynom);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator-(const Monomial& monom) const {
	Polynomial res(*this);
	res.SubtractMonom(monom);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator-(const Polynomial& polynom) const {
	Polynomial res(*this);
	res.SubtractPolynom(polynom);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator*(const double k) const {
	Polynomial res(*this);
	res.MultNumber(k);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator*(const Monomial& monom) const {
	Polynomial res(*this);
	res.MultMonom(monom);
	res.DeleteZero();
	return res;
}

Polynomial Polynomial::operator*(const Polynomial& polynom) const {
	Polynomial res(*this);
	res.MultPolynom(polynom);
	res.DeleteZero();
	return res;
}

bool Polynomial::operator==(const Polynomial& polynom) const {
	return monomsList == polynom.monomsList;
}

std::ostream& operator<<(std::ostream& out, const Polynomial* polynom) {
	if (polynom == nullptr) {
		out << "null";
		return out;
	}
	Polynomial polynomial(*polynom);
	out << polynomial.PolynomToString();
	return out;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& polynom) {
	Polynomial polynomial(polynom);
	out << polynomial.PolynomToString();
	return out;
}