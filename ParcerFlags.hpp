#ifndef PARCERFLAGS_HPP
#define PARCERFLAGS_HPP

class ParcerFlags{
	public:
		bool isRegistered();
		bool isOperator();
	private:
		bool _registered;
		bool _operator;
};

#endif