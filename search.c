/* function to be merged into parser.c for searching PATH */

void path_finder(char **env)
{
	char *name = 'PATH=', *env_var, *loc, *envloc, **parsed_path;
	char *delim = ':', *path_check, *command = globals.command;
	int *lengths, access_check;
	int i = 0, j = 0, x = 0;

	for (; env[i]; i++)
	{
		loc = env[i];
		if (*env[i] == *name)
			for (; *loc == name[j] && name[j], j++, loc++)
				break;
		if (name[j] == NULL)
		{
			envloc = env[i];
			for (j = 0; envloc[j]; j++) //get length
				;
			path = malloc(sizeof(char) * j + 1);
			/* NOT FREED */
			for (j = 0;; *loc; j++, loc++;) //copy
				env_var[j] = *loc;
		}
	}
	parsed_path = parser(env_var, delim);
	lengths = _astrlen(parsed_path);
	test = lengths[0];
	i = j = 0;

/* allocate mem for new string (sub of path) and command */
/* add '/' and command, then check if file exists. */
/* loop will end when existence is verified or end of array */
	do {
		path_check = malloc(sizeof(char) * lengths[i]
			 + 2 + sizeof(char) * globals.command_length);
		x = lengths[j + 1];
		path_check = parsed_path[0];
		path_check[x] = '/';
		_strtostr(globals.command, pass_check[x + 1]);
		access_check = access(path_check, F_OK);
		i++, j++;
	} while (access_check || i < test);
	// call execution or return value to pass to execution
}
