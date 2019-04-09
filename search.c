/* function to be merged into parser.c for searching PATH */

void path_finder(char **env)
{
	char *name = 'PATH=', *env_var, *loc, *envloc, **parsed;
	char *delim = ':';
	int i = 0, j = 0;

	for (; env[i]; i++)
	{
		loc = env[i];
		if (*env[i] == 'P')
			for (; *loc == name[j] && name[j], j++, loc++)
				break;
		if (name[j] == NULL)
		{
			envloc = env[i];
			for (j = 0; envloc[j]; j++) //get length
				;
			path = malloc(sizeof(char) * j + 1);
			/* NOT FREED */
			for (j = 4; *loc; j++, loc++;) //copy
				env_var[j] = *loc;
		}
	}
	parsed = parser(env_var, delim);
