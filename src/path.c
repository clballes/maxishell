
#include "../inc/minishell.h"
#include "../inc/builtins.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	count;

	count = -1;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (0);
	while (s1[++count] != '\0')
		new[count] = s1[count];
	count = -1;
	while (s2[++count] != '\0')
	{
		if (count == 0)
		{
			new[count + i] = '/';
			i++;
		}
		new[count + i] = s2[count];
	}
	new[count + i] = '\0';
	return (new);
}

int	search_path(t_all *all)
{
	char	*res;
	char	**split_path;
	int		i;
	char	*new_path;

	i = 0;
	res = getenv("PATH");
	split_path = ft_split(res, ':'); //mallocs

	while(split_path[i])
	{
		if (all->node->args[0][0] != '/')
			new_path = ft_strjoin_path(split_path[i], all->node->args[0]); //join modificat em passo de lineas
		else
			new_path = ft_strjoin(split_path[i], all->node->args[0]); //join modificat em passo de lineas
		if (access(new_path, F_OK | R_OK) == 0)
		{
			printf("we access it\n");
			printf("existeee %s\n",all->node->args[0] );
			execve(new_path, &all->node->args[0], NULL);
			free(new_path); //free del join
			return (0);
		}
		// if (errno == EACCES) {
        //     printf("%s is not readable: permission denied\n", new_path);
        // } else if (errno == ENOENT) {
        //     printf("%s does not exist\n", new_path);
        // } else {
        //     perror("access");
        // }
		i++;
	}
	free(new_path);
	free_arr(split_path); //free del split
	return (1);
}