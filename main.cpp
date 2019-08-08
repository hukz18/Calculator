#include "interaction.h"

int main(void)
{
	int option = showMenu();
	while (true)
	{
		switch (option)
		{
		case 1:ShowInstruction(); option = showMenu(); break;
		case 2:Calculator(); option = showMenu(); break;
		case 3:EqutionSolver(); option = showMenu(); break;
		case 4:About(); option = showMenu(); break;
		case 5:return 0;
		};
	}
}