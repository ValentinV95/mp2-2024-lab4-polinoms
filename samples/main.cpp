#include "polynom.h"

int main()
{
while(1)
{
	try 
	{
		int option;
		std::cout << "0: F(x, y, z) + Q(x, y, z)" << std::endl;
		std::cout << "1: F(x, y, z) - Q(x, y, z)" << std::endl;
		std::cout << "2: F(x, y, z) * Q(x, y, z)" << std::endl;
		std::cout << "3: alpha * F(x, y, z)" << std::endl;
		std::cout << "4: exit " << std::endl;
		std::cin >> option;

		switch (option)
		{
		case 0:
		{
			std::cout << "F(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom F;
			F.fill();

			std::cout << "Q(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom Q;
			Q.fill();

			std::cout << "F(x, y, z) + Q(x, y, z) =" << std::endl;

			(F + Q).print();

			break;
		}
		case 1:
		{
			std::cout << "F(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom F;
			F.fill();

			std::cout << "Q(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom Q;
			Q.fill();

			std::cout << "F(x, y, z) - Q(x, y, z) =" << std::endl;

			(F - Q).print();

			break;
		}
		case 2:
		{
			std::cout << "F(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom F;
			F.fill();

			std::cout << "Q(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom Q;
			Q.fill();

			std::cout << "F(x, y, z) * Q(x, y, z) =" << std::endl;

			(F * Q).print();

			break;
		}
		case 3:
		{
			std::cout << "F(x, y, z)" << std::endl;
			std::cout << "1-st line: count of monoms, i-th line: i-th monom: 'coefficient' 'deg1' 'deg2' 'deg3'" << std::endl;

			Polynom F;
			F.fill();

			std::cout << "alpha" << std::endl;

			double alpha;

			std::cin >> alpha;

			std::cout << "alpha * F(x, y, z) =" << std::endl;

			(F * alpha).print();

			break;
		}
		case 4: { return 0; }

		default: { exit(3); }

		}
		std::cout << " --------------------------------------------------------------------- " << std::endl;

	}
	catch (std::exception& e) { std::cout << e.what() << std::endl; }
	
}

return 0;
}
