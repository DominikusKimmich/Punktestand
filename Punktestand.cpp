#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class AbstrakterBeobachter {
public:
	virtual void aktualisieren(int) = 0;
};

class Anton : public AbstrakterBeobachter {
public:
	void aktualisieren(int wert) {
		std::cout << "Dies ist Beobachter Anton mit dem Wert " << wert
			<< std::endl;
	}
};

class Berta : public AbstrakterBeobachter {
public:
	void aktualisieren(int wert) {
		std::cout << "Dies ist Beobachter Berta mit dem Wert " << wert
			<< std::endl;
	}
};

class AbstraktesSubjekt {
public:
	virtual void registrieren(const std::shared_ptr<AbstrakterBeobachter>&) {}
	virtual void entfernen(const std::shared_ptr<AbstrakterBeobachter>&) {}
	virtual void benachrichtigen() {}
	virtual void setzeWert(int) {}
};

class Subjekt : public AbstraktesSubjekt {
	std::vector<std::shared_ptr<AbstrakterBeobachter>> _beobachter;
	int _wert = 0;

public:
	void registrieren(const std::shared_ptr<AbstrakterBeobachter>& beobachter) {
		_beobachter.push_back(beobachter);
	}

	void entfernen(const std::shared_ptr<AbstrakterBeobachter>& beobachter) {
		_beobachter.erase(std::remove_if(_beobachter.begin(), _beobachter.end(),
			[&](const std::shared_ptr<AbstrakterBeobachter>& vergleich) {
				return vergleich == beobachter;
			}));
	}

	void benachrichtigen() {
		for (auto& b : _beobachter)
			b->aktualisieren(_wert);
	}

	void setzeWert(int wert) {
		_wert = wert;
		benachrichtigen();
	}
};

int main() {
	std::shared_ptr<AbstraktesSubjekt> subjekt = std::make_shared<Subjekt>();
	std::shared_ptr<AbstrakterBeobachter> anton = std::make_shared<Anton>();
	std::shared_ptr<AbstrakterBeobachter> berta = std::make_shared<Berta>();

	subjekt->registrieren(anton);
	subjekt->registrieren(berta);

	subjekt->setzeWert(1);
	subjekt->entfernen(anton);
	subjekt->setzeWert(2);
	subjekt->entfernen(berta);

	return 0;
}