#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i = 0;
	while (i < argc)
	{
		write(1, argv[i], strlen(argv[i]));
		write(1, "\n", 1);
		i++;
	}
	write(2, "end\n", 4);
	return (0);
}
